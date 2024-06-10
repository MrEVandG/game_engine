#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../render/DrawnTexture.hpp"
#include "../render/Font.hpp"
#include "../render/RenderWindow.hpp"
#include "../utils/Math.hpp"
// Stores every type of Node and Node-related utils.
namespace Node {

    // NodeRect: A node that stores a color, X, Y, Width, Height, and Anchor point for rendering a solid-colored rectangle.
    struct NodeRect {
        // Instantiate a NodeRect class.
        NodeRect(Vector2f p_pos, Vector2f p_size, SDL_Color p_color = { 255,255,255,255 }, Alignment p_align = Alignment::TopLeft)
         : pos(p_pos), size(p_size), color(p_color), anchorPoint(p_align)
        {
            
        };

        // The built-in render function that displays the data of this Node to the screen every frame.
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
        // Where the positioning of this NodeRect is centered on.
        Alignment anchorPoint;
        // The X and Y of the rectangle getting displayed. Influenced by the anchorPoint member.
        Vector2f pos;
        // The width and height of the rectangle getting displayed.
        Vector2f size;
        // The solid color of the rectangle getting displayed.
        SDL_Color color;
    };

    // NodeImage: A node that stores a location to a static image file, X, Y, width, height, and alignment.
    // By default, stretches the image and takes up all space in the screen.
    struct NodeImage {
        // Instantiate the NodeImage class
        NodeImage(const char* p_loc, RenderWindow& p_window, Vector2f p_pos = Vector2f(0,0), Vector2f p_size = Vector2f(1,1),Alignment p_align=Alignment::TopLeft) 
         : loc(p_loc), pos(p_pos), size(p_size), tex(DrawnTexture(p_window.loadTexture(p_loc))) // This line is awful. I hate using C++.
        {
            // Set the texture stored lower-level.
            updateTexture(p_window);
        };

        // Refresh the data of the texture stored in this class.
        void updateTexture(RenderWindow& p_window) {
            sdl_tex = p_window.loadTexture(loc);
            tex = DrawnTexture(sdl_tex, pos, size);
        };

        // The built-in render function that displays the data of this Node to the screen every frame.
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
        // The point in which this NodeImage is displayed.
        Alignment alignment;
        // The location of the image file being displayed.
        const char* loc;
        // The X and Y of this NodeImage getting displayed. Influenced by the alignment member.
        Vector2f pos;
        // The width and height of this NodeImage.
        Vector2f size;
        private:
        // You're not supposed to see this! The lowest-level SDL_Texture, stored in the DrawnTexture.
        SDL_Texture* sdl_tex;
        // You're not supposed to see this! The low-level DrawnTexture, stored in the NodeImage.
        DrawnTexture tex;
    };

    // The type of the different types of nodes, to be used by "renderAllChildren" function.
    typedef std::variant<NodeRect, NodeImage> NodeVariant;

    // Render all children of a node, with a window and the children of the node as input.
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

    // NodeStruct: The highest-level Node that all nodes derive from. This is a struct, not a class.
    struct NodeScene {
        // Instantiate a NodeScene
        NodeScene() {};
        // A vector of children.
        std::vector<NodeVariant> children;
        // The built-in render function that displays the data of this Node to the screen every frame.
        // This just runs the "renderAllChildren" function that is used to render all nodes under this one.
        void render(RenderWindow& p_window) {
            renderAllChildren(p_window, children);
        };
        // Add a Node to this scene's children.
        void appendChild(NodeVariant p_child) {
            children.emplace_back(p_child);
        }
    };
};