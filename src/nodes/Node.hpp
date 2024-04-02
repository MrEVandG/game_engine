#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../render/DrawnTexture.hpp"
#include "../render/Font.hpp"
#include "../render/RenderWindow.hpp"
#include "../utils/Math.hpp"

namespace Node {

    struct NodeRect {
        NodeRect(Vector2f p_pos, Vector2f p_size, SDL_Color p_color = { 255,255,255,255 }, Alignment p_align = Alignment::TopLeft)
         : pos(p_pos), size(p_size), color(p_color), anchorPoint(p_align)
        {
            
        };
        void render(RenderWindow& p_window) {
            SDL_SetRenderDrawColor(p_window.getRenderer(), color.r, color.g, color.b, color.a);
            
            int windowWidth = p_window.getSize().x;
            int windowHeight = p_window.getSize().y;

            SDL_Rect dest;
            dest.x = 0;
            dest.y = 0;
            dest.w = size.x * windowWidth;
            dest.h = size.y * windowHeight;
            switch (anchorPoint) {
                // top row
                case Alignment::TopLeft:
                    dest.x = 0;
                    dest.y = 0;
                    break;
                case Alignment::Top:
                    dest.x = (pos.x - (size.x / 2)) * windowWidth;
                    dest.y = 0;
                    break;
                case Alignment::TopRight:
                    dest.x = p_window.getSize().x - pos.x - size.x;
                    dest.y = 0;
                    break;
                // middle row
                case Alignment::Left:
                    dest.x = 0;
                    dest.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                case Alignment::Center:
                    dest.x = (pos.x - (size.x / 2)) * windowWidth;
                    dest.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                case Alignment::Right:
                    dest.x = p_window.getSize().x - pos.x - size.x;
                    dest.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                // bottom row
                case Alignment::BottomLeft:
                    dest.x = 0;
                    dest.y = p_window.getSize().y - pos.y - size.y;
                    break;
                case Alignment::Bottom:
                    dest.x = (pos.x - (size.x / 2)) * windowWidth;
                    dest.y = p_window.getSize().y - pos.y - size.y;
                    break;
                case Alignment::BottomRight:
                    dest.x = p_window.getSize().x - pos.x - size.x;
                    dest.y = p_window.getSize().y - pos.y - size.y;
                    break;
                default:
                    break;
            }
            
            SDL_RenderFillRect(p_window.getRenderer(), &dest);
            SDL_SetRenderDrawColor(p_window.getRenderer(), 0, 0, 0, 255);
        };
        Alignment anchorPoint;
        Vector2f pos;
        Vector2f size;
        SDL_Color color;
    };

    struct NodeImage {
        NodeImage(const char* p_loc, RenderWindow& p_window, Vector2f p_pos = Vector2f(0,0), Vector2f p_size = Vector2f(1,1),Alignment p_align=Alignment::TopLeft) 
         : loc(p_loc), pos(p_pos), size(p_size), tex(DrawnTexture(p_window.loadTexture(p_loc))) // This line is awful. I hate using C++.
        {
            updateTexture(p_window);
        };
        void updateTexture(RenderWindow& p_window) {
            sdl_tex = p_window.loadTexture(loc);
            tex = DrawnTexture(sdl_tex, pos, size);
        };
        void render(RenderWindow& p_window) {            
            int windowWidth = p_window.getSize().x;
            int windowHeight = p_window.getSize().y;

            switch (alignment) {
                // top row
                case Alignment::TopLeft:
                    tex.pos.x = 0;
                    tex.pos.y = 0;
                    break;
                case Alignment::Top:
                    tex.pos.x = (pos.x - (size.x / 2)) * windowWidth;
                    tex.pos.y = 0;
                    break;
                case Alignment::TopRight:
                    tex.pos.x = p_window.getSize().x - pos.x - size.x;
                    tex.pos.y = 0;
                    break;
                // middle row
                case Alignment::Left:
                    tex.pos.x = 0;
                    tex.pos.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                case Alignment::Center:
                    tex.pos.x = (pos.x - (size.x / 2)) * windowWidth;
                    tex.pos.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                case Alignment::Right:
                    tex.pos.x = p_window.getSize().x - pos.x - size.x;
                    tex.pos.y = (pos.y - (size.y / 2)) * windowHeight;
                    break;
                // bottom row
                case Alignment::BottomLeft:
                    tex.pos.x = 0;
                    tex.pos.y = p_window.getSize().y - pos.y - size.y;
                    break;
                case Alignment::Bottom:
                    tex.pos.x = (pos.x - (size.x / 2)) * windowWidth;
                    tex.pos.y = p_window.getSize().y - pos.y - size.y;
                    break;
                case Alignment::BottomRight:
                    tex.pos.x = p_window.getSize().x - pos.x - size.x;
                    tex.pos.y = p_window.getSize().y - pos.y - size.y;
                    break;
                default:
                    break;
            }
            
            p_window.renderTexture(tex);
        };
        Alignment alignment;
        const char* loc;
        Vector2f pos;
        Vector2f size;
        private:
        SDL_Texture* sdl_tex;
        DrawnTexture tex;
    };

    typedef std::variant<NodeRect, NodeImage> NodeVariant;

    void renderAllChildren(RenderWindow& window, std::vector<NodeVariant> children) {
        for (auto child : children) {
            struct NodeVisitor {
                RenderWindow& window;
                void operator()(NodeRect rect) {
                    rect.render(window);
                }

                void operator()(NodeImage image) {
                    image.render(window);
                }
            };
                
            std::visit(NodeVisitor({.window=window}),child);   
        }
    }

    struct NodeScene {
        NodeScene() {};
        std::vector<NodeVariant> children;
        void render(RenderWindow& p_window) {
            renderAllChildren(p_window, children);
        };
        void appendChild(NodeVariant p_child) {
            children.emplace_back(p_child);
        }
    };
};