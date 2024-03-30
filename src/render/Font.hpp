#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


// this file is kinda useless as setting up a font with just SDL 
// isn't that hard and probably saves a lot of memory
// but it's a little nicer to work with and i think it's just better

enum class Alignment {
    Left,
    Center,
    Right
};

class Font {
    public:
    Font(const char* p_loc, const int p_size): loc(p_loc), size(p_size), closed(false), font(TTF_OpenFont(p_loc, p_size)) {
        if (font == NULL) {
            std::cout << "Could not open font" << std::endl;
        }
    }
    TTF_Font* get_font() {
        if (closed)
            std::cout << "Attempted to use a closed font" << std::endl; // this is pointless cmd spam but uhhhhhh
        return font;
    }
    void close(bool p_setclosed=true) {
        TTF_CloseFont(font);
        closed = p_setclosed;
    }
    void resize(const int p_newsize) {
        close(false);
        font = TTF_OpenFont(loc, p_newsize);
    }
    ~Font() {
        if (!closed) {
            close();
            closed = true;
        }
    }
    private:
    int size;
    const char* loc;
    bool closed = false;
    TTF_Font* font;
};