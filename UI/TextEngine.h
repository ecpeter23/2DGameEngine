#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "../util/datatypes.h"

#define DEFAULT_FONT "assets/fonts/Roboto-Regular.ttf"

class TextEngine {
public:
    explicit TextEngine(SDL_Renderer *renderer);
    ~TextEngine();

    void renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color);
    void setFont(const std::string& fontPath, int fontSize);

private:
    TTF_Font* loadFont(const std::string& fontPath, int fontSize);
    TTF_Font* font{};
    SDL_Renderer *renderer_{};



};