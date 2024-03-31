#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/Math.hpp"

class DrawnTexture {
    public:
        DrawnTexture(Vector2f p_pos, Vector2f p_size, SDL_Texture* p_tex)
         : pos(p_pos), size(p_size), tex(p_tex)
        {
            currentFrame.x = 0;
            currentFrame.y = 0;
            currentFrame.w = 1;
            currentFrame.h = 1;
        }
        SDL_Texture* getTex() {
            return tex;
        }
        void setTex(SDL_Texture* p_newtex) {
            tex = p_newtex;
        };
        Vector2f size;
        Vector2f pos;
        SDL_Rect currentFrame;
    private:
        SDL_Texture* tex;
};