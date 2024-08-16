#pragma once

#include <vector>

#include "../system/Window.hpp"

class App
{
private:
    bool m_running;
    std::vector<Window*> m_windows;

    void poll_events();
    void update_windows();

public:
    App();

    App& add_window(Window* window);

    int run();
};