#pragma once
#include <SDL2/SDL.h>

// General SDL, rendering, and other utilities.
namespace utils {
    // Returns how much time it has been since SDL instantiated.
    inline float totalTimeMS() {
        return SDL_GetTicks64();
    }
}