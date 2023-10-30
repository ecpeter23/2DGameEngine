#pragma once

#include <SDL.h>
#include <string>
#include "util.h"

class Window {
public:
    explicit Window(const std::string& title, int width = 1080, int height = 720, bool fullscreen = false, bool borderless = false);

    void setDimensions(int width, int height);
    void setTitle(const std::string& title);
    void setBrightness(float brightness);
    void fullScreen(bool fullscreen);
    void borderless(bool borderless);
    void show();
    void hide();


private:
    SDL_Window* window;
    std::string title;
    int width;
    int height;
    float brightness{};
    bool hidden;
    bool fs;
    bool bl;
};
