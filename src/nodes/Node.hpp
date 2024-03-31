#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../render/RenderWindow.hpp"
#include "../render/Font.hpp"
#include "../utils/Math.hpp"

namespace Node {

    struct NodeRect {
        NodeRect(Vector2f p_pos, Vector2f p_size, SDL_Color p_color = { 255,255,255,255 }, Alignment p_align = Alignment::TopLeft)
         : pos(p_pos), size(p_size), color(p_color), alignment(p_align)
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
            switch (alignment) {
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
        Alignment alignment;
        Vector2f pos;
        Vector2f size;
        SDL_Color color;
    };

    typedef std::variant<NodeRect*> NodeVariant;

    struct NodeScene {
        NodeScene() {};
        std::vector<NodeVariant> children;
        void render(RenderWindow& p_window) {
            for (auto child : children) {
                struct NodeVisitor {
                    RenderWindow& window;
                    void operator()(NodeRect* rect) {
                        rect->render(window);
                    }
                };
                
                std::visit(NodeVisitor({.window=p_window}),child);   
            }
        };
        void appendChild(NodeVariant p_child) {
            children.emplace_back(p_child);
        }
    };
};