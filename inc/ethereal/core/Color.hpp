#pragma once

struct Color
{
    float r;
    float g;
    float b;
    float a = 1.0f;

    Color()
    {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    Color(float r, float g, float b, float a = 1.0f)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

typedef Color Colour; // Alias for Color