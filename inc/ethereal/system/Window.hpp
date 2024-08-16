#pragma once

#include <string>
#include <cstdint>

#include <gl\glew.h>
#include <gl\glu.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../core/Color.hpp"
#include "../core/Vector2.hpp"

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
    Vector2<intmax_t> size;
    Color background_color;

    static void set_active_window(Window*);

public:
    Window(WindowConfig&);
    ~Window();

    static Window* get_active_window();

    int get_ID();
    void clear();
    void update();

    friend class App;
};