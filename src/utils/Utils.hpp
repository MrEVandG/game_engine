#pragma once
#include <SDL2/SDL.h>

namespace utils {
    inline float totalTimeMS() {
        return SDL_GetTicks64();
    }
}