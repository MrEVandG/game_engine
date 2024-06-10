#pragma once
#include <iostream>

// A 2-dimensional vector that stores an X and Y, in floats.
struct Vector2f {
    // The X and Y flaots stored within this vector.
    float x, y;
    // Instantiate a Vector2f with the default coordinates of 0, 0.
    Vector2f() : x(0.0f), y(0.0f) {};
    // Instantiate a Vector2f with custom coordinates.
    Vector2f(float p_x, float p_y): x(p_x), y(p_y) {};

    // Debug: Print out the X and Y of this Vector.
    void print(float p_scalex = 1.0f, float p_scaley = 1.0f) {
        printf("(%f, %f)\n", x*p_scalex, y*p_scaley);
    }
};