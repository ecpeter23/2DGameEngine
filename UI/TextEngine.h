#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <memory>
#include "../util/datatypes.h"

#define DEFAULT_FONT "/Users/elipeter/Downloads/2DGameEngine/assets/fonts/open-sans/OpenSans-Regular.ttf"

enum class TextAlign {
    Left,
    Center,
    Right
};

enum class TextRenderStyle {
    Solid,
    Shaded,
    Blended
};

struct FontDeleter {
    void operator()(TTF_Font* font) {
        TTF_CloseFont(font);
    }
};

class TextEngine {
public:
    explicit TextEngine(SDL_Renderer *renderer);
    ~TextEngine();

    void renderText(const std::string& text, int x, int y, SDL_Color color, TextAlign align = TextAlign::Left, TextRenderStyle style = TextRenderStyle::Solid);
    void setFont(const std::string& fontPath);
    void setFontStyle(int style);
    void setFontOutline(int outlineWidth);
    void setFontSize(int size);

private:
    TTF_Font* getFont(const std::string& fontPath);
    TTF_Font* font{};
    SDL_Renderer *renderer_{};
    std::map<std::string, std::unique_ptr<TTF_Font, FontDeleter>> fontCache;

};
