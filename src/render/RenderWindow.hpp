#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "DrawnTexture.hpp"
#include "Font.hpp"

#define FULLSCREEN_WIDTH 1920
#define FULLSCREEN_HEIGHT 1080

#define WINDOWED_WIDTH 1280
#define WINDOWED_HEIGHT 720

class RenderWindow {
    public:
        RenderWindow(const char* p_title, bool p_fullscreen) : isFullScreen(p_fullscreen), window(NULL), renderer(NULL) {
            window = SDL_CreateWindow(p_title,
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                p_fullscreen ? FULLSCREEN_WIDTH : WINDOWED_WIDTH,
                p_fullscreen ? FULLSCREEN_HEIGHT : WINDOWED_HEIGHT,
                SDL_WINDOW_SHOWN | (p_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
            if (window == NULL) {
                std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        };
        bool getIsFullScreen() {
            return isFullScreen;
        }
        Vector2f getSize() {
            return Vector2f(isFullScreen ? FULLSCREEN_WIDTH : WINDOWED_WIDTH, isFullScreen ? FULLSCREEN_HEIGHT : WINDOWED_HEIGHT);
        }
        void toggleFullScreen() { // why sdl... why
            isFullScreen = !isFullScreen;
            SDL_SetWindowFullscreen(window, isFullScreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
            SDL_ShowCursor(true); // i mean this should happen anyway right??
            SDL_SetWindowBordered(window, (SDL_bool)!isFullScreen); // C++ why do I have to cast a boolean to a boolean it's literally just a 0 or a 1 😭
            if (isFullScreen) {
                SDL_SetWindowSize(window, FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT);
            } else {
                SDL_SetWindowSize(window, WINDOWED_WIDTH, WINDOWED_HEIGHT);
                SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            }
        }
        int getRefreshRate() {
            int displayIndex = SDL_GetWindowDisplayIndex(window);
            SDL_DisplayMode mode;
            SDL_GetDisplayMode(displayIndex, 0, &mode);
            return mode.refresh_rate;
        }
        SDL_Texture* loadTexture(const char* p_filePath) {
            SDL_Texture* texture = NULL;
            texture = IMG_LoadTexture(renderer, p_filePath);
            if (texture == NULL) {
                std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
            }
            return texture;
        }

        void cleanup() {
            SDL_DestroyWindow(window);
        };

        void clear() {
            SDL_RenderClear(renderer);
        }

        void renderTexture(DrawnTexture& p_entity) {
            int windowWidth = getSize().x;
            int windowHeight = getSize().y;
            SDL_Rect dest;
            dest.x = p_entity.getPos().x * windowWidth;
            dest.y = p_entity.getPos().y * windowHeight;
            dest.w = p_entity.getSize().x * windowWidth;
            dest.h = p_entity.getSize().y * windowHeight;

            SDL_RenderCopy(renderer, p_entity.getTex(), NULL, &dest);
        }

        void renderText(Font& p_font, const char* p_text, Vector2f pos, Alignment alignment, SDL_Color p_color = { 0, 0, 0}) { // this function is such a waste lmao
            SDL_Surface* text = TTF_RenderText_Solid(p_font.get_font(), p_text, p_color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
            int texW = 0;
            int texH = 0;
            SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
            int x = pos.x * getSize().x;
            switch (alignment) {
                case Alignment::Left:
                    break;
                case Alignment::Center:
                    x = x - (texW / 2); // center the text :)
                    break;
                case Alignment::Right:
                    x = getSize().x - x - texW;
                    break;
            }
            int y = pos.y * getSize().y;
            SDL_Rect dest = { x, y, texW, texH };
            SDL_RenderCopy(renderer, texture, NULL, &dest);
            SDL_FreeSurface(text);
            SDL_DestroyTexture(texture);
        }

        void display() {
            SDL_RenderPresent(renderer);
        }
    private:
        bool isFullScreen;
        SDL_Window* window;
        SDL_Renderer* renderer;
};