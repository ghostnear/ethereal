#pragma once

#include <vector>

#include "Window.hpp"

namespace Ethereal::Core
{
    class App
    {
    private:
        bool m_running;
        std::vector<Window*> m_windows;

        void poll_events();
        void update_windows();

    public:
        App();

        App& add_window(Window*);

        int run();
    };
}