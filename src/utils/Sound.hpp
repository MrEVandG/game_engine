#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

namespace Sound {
    // Prepare the SDL_Mixer audio with default frequency, file format, chunk size, and stereo audio
    // To the system's default audio output device.
    static void open() {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    };

    // Prepare the SDL_Mixer with the same parameters as open() for an output device that matches the name given in `p_deviceName`
    static void openDevice(const char* p_devicename) {
        Mix_OpenAudioDevice(44100, MIX_DEFAULT_FORMAT, 2, 1024, p_devicename, SDL_AUDIO_ALLOW_ANY_CHANGE); // default everything
    };

    // Turn off the SDL_Mixer audio.
    static void close() {
        Mix_CloseAudio();
    };

    // Disables and re-enables audio to use a different audio device.
    // WARNING: Does not check if the currently enabled audio device matches the parameter.
    static void changeDevice(const char* deviceName) {
        close();
        openDevice(deviceName);
    };

    // Return a vector of audio output devices' names.
    // @returns std::vector<const char*>
    static std::vector<const char*> listDevices() {
        const int numDevices = SDL_GetNumAudioDevices(0);
        std::vector<const char*> devices;
        for (int i = 0; i < numDevices; i++) {
            devices.push_back(SDL_GetAudioDeviceName(i, 0));
        }
        return devices;
    };

    // Sound effect class
    // Multi-use WAV-format audio chunks to be played at a select volume and channel.
    // See 'Music' for loopable, one-channel, multi-chunked background sounds.
    class SoundEffect {
        public:
        // Instantiate the SoundEffect with the location of the WAV-format audio file.
        SoundEffect(const char* p_loc): loc(p_loc), sound(Mix_LoadWAV(p_loc)) {
            if (!sound) {
                std::cout << "Sound effect not loaded correctly. error: " << Mix_GetError() << std::endl;
            }
        };

        // Start the audio with a specific volume, channel, and number of loops.
        // Set "p_loops" to -1 to loop infinitely. (Check the 'Music' class!)
        // Set "p_channel" to a specific number for more manual control over audio. Will override the currently-playing sound effect if the channels are equivalent.
        // Set "p_channel" to -1 to select a random, unoccupied channel.
        // MIX_MAX_VOLUME = 128, so volume is a range of 0 to 128.
        void play(int p_vol = MIX_MAX_VOLUME, int p_loops = 0, int p_channel = -1) {
            channel = Mix_PlayChannel(channel, sound, p_loops);
            Mix_Volume(channel, p_vol);
        };

        // Change the volume stored in the class.
        // Defaults to max volume, which is 128.
        void change_volume(int p_vol = MIX_MAX_VOLUME) {
            volume = p_vol;
            Mix_Volume(channel, p_vol);
        }

        // Halt the currently-playing sound effect chunk.
        void stop() {
            Mix_HaltChannel(channel);
        }

        // Return which channel this sound effect is playing on.
        int get_channel() {
            return channel;
        }

        // Get the lower-level chunk that represents the audio data of this sound effect.
        Mix_Chunk* get_chunk() {
            return sound;
        };
        private:
        int channel = -1;
        int volume = MIX_MAX_VOLUME;
        const char* loc;
        Mix_Chunk* sound;
    };

    // Music class
    // Single-use, loopable any-format audio chunks to be played at a select volume.
    // Only one Music track can play at one time.
    // See 'SoundEffect' for multi-use, any-channel, one-chunked foreground sounds.
    class Music {
        public:
        // Instantiate the Music with the location of the any-format audio file.
        Music(const char* p_loc): loc(p_loc), music(Mix_LoadMUS(p_loc)) {
            if (!music) {
                std::cout << "Music track not loaded correctly. error: " << Mix_GetError() << std::endl;
            }
        };

        // Plays the Music track at a select volume and number of loops.
        // Set "p_vol" to any positive integer between 0 - 128 (for max volume, use the constant MIX_MAX_VOLUME)
        // Set "p_loops" to -1 to loop infinitely, or 0 to play once. (Check the 'SoundEffect' class!)
        void play(int p_vol = MIX_MAX_VOLUME, int p_loops = -1) { // -1 = loops infinitely
            Mix_PlayMusic(music, p_loops); // -1 = find first channel
            Mix_VolumeMusic(p_vol); // music is its own dedicated chnanel, so I don't need to pass that in. :)
        };

        // Change the volume of the currently-playing or about-to-play music track.
        // Set "p_vol" to any positive integer between 0 - 128 (for max volume, use the constant MIX_MAX_VOLUME)
        void change_volume(int p_vol = MIX_MAX_VOLUME) {
            volume = p_vol;
            Mix_VolumeMusic(p_vol);
        }

        // Halt the currently-playing track.
        void stop() {
            Mix_HaltMusic();
        };

        // Return the lower-level music chunks that represents the data of this music track.
        Mix_Music* get_music() {
            return music;
        }

        private:
        int volume = MIX_MAX_VOLUME;
        const char* loc;
        Mix_Music* music;
    };
};