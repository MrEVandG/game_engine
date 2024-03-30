#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../utils/Math.hpp"

class DrawnTexture {
    public:
        DrawnTexture(Vector2f p_pos, Vector2f p_size, SDL_Texture* p_tex) : pos(p_pos), size(p_size), tex(p_tex) {
            currentFrame.x = 0;
            currentFrame.y = 0;
            currentFrame.w = 1;
            currentFrame.h = 1;
        }
        Vector2f& getPos() {
            return pos;
        };
        SDL_Texture* getTex() {
            return tex;
        };
        Vector2f& getSize() {
            return size;
        };
        SDL_Rect& getCurrentFrame() {
            return currentFrame;
        };
        void setPos(Vector2f p_newpos) {
            pos = p_newpos; // easy lmao
        }
    private:
        Vector2f size;
        Vector2f pos;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};