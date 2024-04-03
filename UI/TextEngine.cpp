#include "TextEngine.h"

TextEngine::TextEngine(SDL_Renderer *renderer)
        : renderer_(renderer) {
    // Initialize SDL_ttf
    ASSERT(TTF_Init() == 0, "Failed to initialize SDL_ttf");
    ASSERT(renderer_, "Renderer is null");
    setFont(DEFAULT_FONT);
}

TextEngine::~TextEngine() {
    fontCache.clear();
    TTF_Quit();
}

void TextEngine::renderText(const std::string &text, int x, int y, SDL_Color color, TextAlign align, TextRenderStyle style) {
    SDL_Surface *surface = nullptr;

    switch (style) {
        case TextRenderStyle::Solid:
            surface = TTF_RenderText_Solid(font, text.c_str(), color);
            break;
        case TextRenderStyle::Shaded:
            surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0});
            break;
        case TextRenderStyle::Blended:
            surface = TTF_RenderText_Blended(font, text.c_str(), color);
            break;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_Rect destRect = {x, y, surface->w, surface->h};

    // Adjust text alignment
    switch (align) {
        case TextAlign::Center:
            destRect.x -= surface->w / 2;
            break;
        case TextAlign::Right:
            destRect.x -= surface->w;
            break;
        case TextAlign::Left:
        default:
            break;
    }

    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

TTF_Font *TextEngine::getFont(const std::string &fontPath) {
    auto it = fontCache.find(fontPath);
    if (it != fontCache.end()) {
        return it->second.get();
    } else {
        TTF_Font *newFont = TTF_OpenFont(fontPath.c_str(), 24); // Default font size
        ASSERT(newFont != nullptr, "Failed to load font: %s\n", TTF_GetError());
        fontCache[fontPath] = std::unique_ptr<TTF_Font, FontDeleter>(newFont);
        return newFont;
    }
}

void TextEngine::setFont(const std::string &fontPath) {
    font = getFont(fontPath);
}

void TextEngine::setFontStyle(int style) {
    TTF_SetFontStyle(font, style);
}

void TextEngine::setFontOutline(int outlineWidth) {
    TTF_SetFontOutline(font, outlineWidth);
}

void TextEngine::setFontSize(int size) {
    TTF_SetFontSize(font, size);
}