#pragma once
#include <iostream>

struct Vector2f {
    float x, y;
    Vector2f() : x(0.0f), y(0.0f) {};
    Vector2f(float p_x, float p_y): x(p_x), y(p_y) {};

    void print(float p_scalex = 1.0f, float p_scaley = 1.0f) {
        printf("(%f, %f)\n", x*p_scalex, y*p_scaley);
    }
};