#pragma once

template<typename T>
class Vector2
{
public:
    T x;
    T y;

    Vector2()
    {
        x = 0;
        y = 0;
    }

    Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
};