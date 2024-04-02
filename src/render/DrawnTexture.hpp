#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/Math.hpp"

class DrawnTexture {
    public:
        DrawnTexture(SDL_Texture* p_tex, Vector2f p_pos = Vector2f(0,0), Vector2f p_size = Vector2f(1,1))
         : pos(p_pos), size(p_size), tex(p_tex)
        {
        }
        SDL_Texture* getTex() {
            return tex;
        }
        void setTex(SDL_Texture* p_newtex) {
            tex = p_newtex;
        };
        Vector2f size;
        Vector2f pos;
    private:
        SDL_Texture* tex;
};