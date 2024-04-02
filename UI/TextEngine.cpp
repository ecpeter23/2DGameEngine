#include "TextEngine.h"

TextEngine::TextEngine(SDL_Renderer *renderer) {
    // Initialize SDL_ttf
    ASSERT(TTF_Init() == 0, "Failed to initialize SDL_ttf");

    this->renderer_ = renderer;
    ASSERT(renderer_, "Renderer is null");

    font = loadFont(DEFAULT_FONT, 24);
}

TextEngine::~TextEngine() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void TextEngine::renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

TTF_Font* TextEngine::loadFont(const std::string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    ASSERT(font != nullptr, "Failed to load font: %s\n", TTF_GetError());
    return font;
}

void TextEngine::setFont(const std::string &fontPath, int fontSize) {
    TTF_CloseFont(font);
    font = loadFont(fontPath, fontSize);
}

