#include "core/App.hpp"

#include <format>
#include <cstdlib>
#include <stdexcept>

using namespace Ethereal::Core;

App::App()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(std::format("(SDL): SDL initialization failed. ({})", SDL_GetError()));
    atexit(SDL_Quit);

    m_running = true;
}

App& App::add_window(Window* window)
{
    auto window_result = std::find_if(m_windows.begin(), m_windows.end(), [&](Window* w) {
        return w->get_ID() == window->get_ID();
    });
    if(window_result == m_windows.end())
        m_windows.push_back(window);
    return *this;
}

void App::poll_events()
{
    static SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;

        case SDL_WINDOWEVENT:
            auto window = std::find_if(m_windows.begin(), m_windows.end(), [&](Window* w) {
                return w->get_ID() == event.window.windowID;
            });
            if(window != m_windows.end())   // This shouldn't ever be false let's hope.
            {
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        delete *window;
                        m_windows.erase(window);
                        if(m_windows.size() == 0)
                            m_running = false;
                        break;
                }
            }
            break;
        }
    }
}

void App::update_windows()
{
    for(auto window : m_windows)
    {
        Window::set_active_window(window);
        window->clear();
        window->execute();
        window->update();
    }
}

int App::run()
{
    while(m_running)
    {
        poll_events();
        update_windows();
    }
    return EXIT_SUCCESS;
}