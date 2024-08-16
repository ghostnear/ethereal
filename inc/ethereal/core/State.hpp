#pragma once

#include "ECS.hpp"

namespace Ethereal::Core
{
    class State
    {
    protected:
        ECS::EntityDB entities;

    public:
        virtual ~State() = default;
        virtual void update() = 0;
    };
}
