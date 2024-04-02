#include "TextEngine.h"

TextEngine::TextEngine() noexcept {
    // Initialize SDL_ttf
    ASSERT(TTF_Init() == 0, "Failed to initialize SDL_ttf");

    // Get the renderer from somewhere
    renderer_ = nullptr;
}

TextEngine::~TextEngine() {
    // Quit SDL_ttf
    do {
        TTF_Quit();
    } while (TTF_WasInit());
}

bool TextEngine::init(SDL_Renderer *renderer) {
    // Load your fonts and perform any initialization here
    this->renderer_ = renderer;
    ASSERT(renderer_, "Renderer is null");

    font = loadFont(DEFAULT_FONT, 24);
    return true;
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

void TextEngine::free() {
    TTF_CloseFont(font);
    font = nullptr;
    renderer_ = nullptr;
}

void TextEngine::updateFont(const std::string& fontPath, int fontSize=24) {
    TTF_CloseFont(font);
    font = loadFont(fontPath, fontSize);
}

