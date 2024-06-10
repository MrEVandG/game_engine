#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <variant>
#include <SDL2/SDL_mixer.h>

#include "utils/Math.hpp"
#include "utils/Utils.hpp"
#include "utils/Sound.hpp"
#include "render/RenderWindow.hpp"
#include "render/DrawnTexture.hpp"
#include "render/Font.hpp"
#include "nodes/Node.hpp"

#define MINIFIED_FONT_SIZE 25 // For Windowed mode text only. Fullscreen text will be 1.5x the size.

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL Init, error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_JPG))
		std::cout << "Image Init failed, error:" << SDL_GetError() << std::endl;

	if (TTF_Init())
		std::cout << "TTF Init failed, error: " << TTF_GetError() << std::endl;

	if (!Mix_Init(MIX_InitFlags::MIX_INIT_MP3))
		std::cout << "Mixer Init failed, error: " << Mix_GetError() << std::endl; // Technically just SDL_GetError() WIth a costume but stfu

	Sound::open();

	{
		const std::vector<const char *> devices = Sound::listDevices();
		for (const char *device : devices)
		{
			std::cout << device << std::endl;
		}
	}

	bool fullscreen = false;
	RenderWindow window("Game Engine v0.1", fullscreen);
	int windowRefreshRate = window.getRefreshRate();
	std::cout << windowRefreshRate << " max fps" << std::endl;
	bool gameRunning = true;

	// TEXTURES AND STUFF
	Font font = Font("res/font/roboto.ttf", MINIFIED_FONT_SIZE * (fullscreen * 0.5 + 1)); // W formula ngl // Bro what kind of comment is this I was actually insane 2 months ago
	Node::NodeScene scene;
	{
		Node::NodeRect rectNode = Node::NodeRect(
			Vector2f(0.5, 0.5),
			Vector2f(0.5, 0.5),
			SDL_Color({.r = 255, .g = 0, .b = 0, .a = 255}),
			Alignment::Center);
		Node::NodeImage imageNode = Node::NodeImage("res/image/test.jpg", window);
		scene.appendChild(imageNode);
		scene.appendChild(rectNode);
	}

	// MUSIC
	// Sound::Music music = Sound::Music("res/mus/main.mp3");
	// music.play(16); // Loops this track indefinitely, at volume 16

	// GAME LOOP
	SDL_Event event;
	const float timeStep = 10; // 10 milliseconds
	float accumulator = 0.0f;
	int idkSomethingIg = 0;
	float currentTime = utils::totalTimeMS();
	while (gameRunning)
	{
		int startTicks = utils::totalTimeMS();
		float newTime = utils::totalTimeMS();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		while (accumulator >= timeStep)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
				if (event.type == SDL_KEYUP)
				{
					if (event.key.keysym.sym == SDLK_f)
					{
						window.toggleFullScreen();
						font.resize(window.getIsFullScreen() ? MINIFIED_FONT_SIZE * 1.5 : MINIFIED_FONT_SIZE);
					}
				}
			}
			accumulator -= timeStep;
		}
		const float alpha = accumulator / timeStep;

		window.clear();

		scene.render(window);

		window.renderText(font, "some random text", Vector2f(0.5, 0.5), Alignment::Center, {255, 255, 255});
		window.display();
		int frameTicks = utils::totalTimeMS() - startTicks;
		if (frameTicks < 1000 / window.getRefreshRate())
		{
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		}
	}
	window.cleanUp();
	font.close();
	Sound::close();
	TTF_Quit();
	SDL_Quit();
	return 0;
}