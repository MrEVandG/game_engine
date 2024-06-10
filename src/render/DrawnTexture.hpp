#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/Math.hpp"

class DrawnTexture {
    public:
        // Blankly instantiate a DrawnTexture class
        DrawnTexture(SDL_Texture* p_tex, Vector2f p_pos = Vector2f(0,0), Vector2f p_size = Vector2f(1,1))
         : pos(p_pos), size(p_size), tex(p_tex)
        {
        }
        
        // Return the lower-level SDL_Texture associated with this class.
        SDL_Texture* getTex() {
            return tex;
        }

        // Replace the texture stored in this class.
        void setTex(SDL_Texture* p_newtex) {
            tex = p_newtex;
        };
        // The width and height of the texture.
        Vector2f size;
        // The X and Y position of the texture.
        Vector2f pos;
    private:
        SDL_Texture* tex;
};