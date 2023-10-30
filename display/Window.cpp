#include "Window.h"

Window::Window(const std::string& title, int width, int height, bool fullscreen, bool borderless)
        : title(title), width(width), height(height), fs(fullscreen), bl(borderless), hidden(false)
{
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
}

void Window::setDimensions(int width, int height) {
    this->width = width;
    this->height = height;
    SDL_SetWindowSize(window, width, height);
}

void Window::setTitle(const std::string& title) {
    this->title = title;
    SDL_SetWindowTitle(window, title.c_str());
}

void Window::fullScreen(bool fullscreen) {
    this->fs = fullscreen;
    SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

void Window::borderless(bool borderless) {
    this->bl = borderless;
    SDL_SetWindowBordered(window, borderless ? SDL_TRUE : SDL_FALSE);
}

void Window::setBrightness(float brightness) {
    this->brightness = brightness;
    SDL_SetWindowBrightness(window, brightness);
}


void Window::show() {
    hidden = false;
    SDL_ShowWindow(window);
}

void Window::hide() {
    hidden = true;
    SDL_HideWindow(window);
}


