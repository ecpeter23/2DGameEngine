#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <utility>
#include "../util/datatypes.h"
#include "../util/Camera.h"
#include "../object/GameObject.h"

class Display {
public:
    Display(std::string title, int width, int height);
    ~Display();

    void pollEvents(SDL_Event &event);
    [[nodiscard]] bool isClosed() const;

    void setFullscreen(bool fullscreen);
    void setBorderless(bool borderless);
    void setIcon(const std::string &iconPath);
    void minimize();
    void maximize();

    void clear();
    void present();
    void render();
    void drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect);
    void drawGameObject(const GameObject& gameObject);
    static SDL_Texture *loadTexture(const std::string &filePath);

    SDL_Renderer* getRenderer();

private:
    bool init();

private:
    std::string title_;
    int width_;
    int height_;
    bool closed_;

    SDL_Window *window_{};
    SDL_Renderer *renderer_{};
    SDL_Texture *debug_{};
};
