#pragma once

namespace Ethereal::Core
{
    template<typename T>
    struct Vector2
    {
        T x;
        T y;

    public:
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
}
