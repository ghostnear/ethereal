#include "core/Window.hpp"

#include <format>
#include <stdexcept>

using namespace Ethereal::Core;

Window* Window::m_activeWindow = nullptr;

void Window::set_active_window(Window* window)
{
    m_activeWindow = window;
}

Window::Window(WindowConfig& config)
{
    background_color = config.background_color;
    m_window = SDL_CreateWindow(
        config.title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config.size.x,
        config.size.y,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    if(m_window == nullptr)
        throw std::runtime_error(std::format("(SDL): Window creation failed. ({})", SDL_GetError()));
    size = config.size;

    // Create OpenGL context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    m_context = SDL_GL_CreateContext(m_window);
    if(m_context == nullptr)
        throw std::runtime_error(std::format("(GL): Context creation failed. ({})", SDL_GetError()));

    // Enable GLEW.
    glewExperimental = GL_TRUE; 
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
        throw std::runtime_error(std::format("(GLEW): OpenGL initialization failed. ({})", (char*)glewGetErrorString(glewError)));

    // Enable VSync for current window.
    SDL_GL_MakeCurrent(m_window, m_context);
    if(SDL_GL_SetSwapInterval( 1 ) < 0)
    {
        // TODO: log info here.
    }
}

Window::~Window()
{
    if(m_context != nullptr)
        SDL_GL_DeleteContext(m_context);
    if(m_window != nullptr)
        SDL_DestroyWindow(m_window);
}

Window& Window::set_state(State* state)
{
    delete m_state;
    m_state = state;
    return *this;
}

int Window::get_ID()
{
    return SDL_GetWindowID(m_window);
}

void Window::clear()
{
    SDL_GL_MakeCurrent(m_window, m_context);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
}

void Window::execute()
{
    m_state->update();
}

void Window::update()
{
    SDL_GL_SwapWindow(m_window);
}