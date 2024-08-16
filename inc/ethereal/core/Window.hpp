#pragma once

#include <string>
#include <cstdint>

#include <gl\glew.h>
#include <gl\glu.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "State.hpp"
#include "Color.hpp"
#include "Vector2.hpp"

using namespace Ethereal::Core;

namespace Ethereal::Core
{
    struct WindowConfig
    {
        Color background_color;
        Vector2<intmax_t> size;
        std::string title;
    };

    class Window
    {
    private:
        static Window* m_activeWindow;
        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context = nullptr;
        State* m_state = nullptr;
        Vector2<intmax_t> size;
        Color background_color;

        static void set_active_window(Window*);

    public:
        Window(WindowConfig&);
        ~Window();

        static Window* get_active_window();

        Window& set_state(State*);

        int get_ID();
        void clear();
        void execute();
        void update();

        friend class App;
    };
}
