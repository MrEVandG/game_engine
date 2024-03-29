#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class SoundEffect {
    public:
    SoundEffect(const char* p_loc): loc(p_loc), sound(Mix_LoadWAV(p_loc)) {
        if (!sound) {
            std::cout << "Sound effect not loaded correctly. error: " << Mix_GetError() << std::endl;
        }
    };

    void play(int loops = 0) {
        Mix_PlayChannel(-1, sound, loops); // -1 = find first channel
    };

    Mix_Chunk* get_Chunk() {
        return sound;
    };
    private:
    const char* loc;
    Mix_Chunk* sound;
};

class Music {
    public:
    Music(const char* p_loc): loc(p_loc), music(Mix_LoadMUS(p_loc)) {
        if (!music) {
            std::cout << "Music track not loaded correctly. error: " << Mix_GetError() << std::endl;
        }
    };

    void play(int loops = -1) { // -1 = loops infinitely
        Mix_PlayMusic(music, loops); // -1 = find first channel
    };

    void stop() {
        Mix_HaltMusic();
    };

    private:
    const char* loc;
    Mix_Music* music;
};