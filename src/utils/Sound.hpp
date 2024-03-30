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

    // MIX_MAX_VOLUME = 128, so volume is a range of 0 to 128.
    void play(int p_loops = 0, int p_vol = MIX_MAX_VOLUME, int p_channel = -1) {
        if (p_vol == 0)
            std::cout << "Why even bother playing the sound if it's volume is 0? I'm not gonna stop you, but you should consider reeveluating your choices." << std::endl;
        channel = Mix_PlayChannel(channel, sound, p_loops);
        Mix_Volume(channel, p_vol);
    };

    void change_volume(int p_vol = MIX_MAX_VOLUME) {
        volume = p_vol;
    }

    int get_channel() {
        return channel;
    }

    Mix_Chunk* get_chunk() {
        return sound;
    };
    private:
    int channel = -1;
    int volume = MIX_MAX_VOLUME;
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

    void play(int p_loops = -1, int p_vol = MIX_MAX_VOLUME) { // -1 = loops infinitely
        Mix_PlayMusic(music, p_loops); // -1 = find first channel
        Mix_VolumeMusic(p_vol); // music is its own dedicated chnanel, so I don't need to pass that in. :)
    };

    void change_volume(int p_vol = MIX_MAX_VOLUME) {
        volume = p_vol;
        Mix_VolumeMusic(p_vol);
    }

    void stop() {
        Mix_HaltMusic();
    };

    private:
    int volume = MIX_MAX_VOLUME;
    const char* loc;
    Mix_Music* music;
};