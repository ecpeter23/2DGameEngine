#include "Display.h"

Display::Display(std::string title, int width, int height)
        : title_(std::move(title)), width_(width), height_(height), closed_(false) {
    init();
}

Display::~Display() {
    SDL_DestroyTexture(debug_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    SDL_Quit();
}


bool Display::init() {
    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL failed to initialize: %s", SDL_GetError())

    window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    ASSERT(window_, "failed to create SDL window: %s\n", SDL_GetError())

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    ASSERT(renderer_, "failed to create SDL renderer: %s\n", SDL_GetError())

    debug_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 128, 128);
    ASSERT(debug_, "failed to create SDL debug renderer: %s\n", SDL_GetError())

    return true;
}

void Display::pollEvents(SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        closed_ = true;
    }

    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        width_ = event.window.data1;
        height_ = event.window.data2;
    }

}

bool Display::isClosed() const {
    return closed_;
}

void Display::setFullscreen(bool fullscreen) {
    SDL_SetWindowFullscreen(window_, fullscreen? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void Display::setBorderless(bool borderless) {
    SDL_SetWindowBordered(window_, borderless? SDL_FALSE : SDL_TRUE);
}

void Display::setIcon(const std::string &iconPath) {
    SDL_Surface *icon = SDL_LoadBMP(iconPath.c_str());

    ASSERT(icon, "Failed to load icon: %s\n", SDL_GetError());
    SDL_SetWindowIcon(window_, icon);
    SDL_FreeSurface(icon);
}

void Display::minimize() {
    SDL_MinimizeWindow(window_);
}

void Display::maximize() {
    SDL_MaximizeWindow(window_);
}

void Display::clear() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Display::present() {
    SDL_RenderPresent(renderer_);
}

void Display::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect) {
    SDL_RenderCopy(renderer_, texture, srcRect, dstRect);
}

SDL_Texture *Display::loadTexture(const std::string &filePath) {
    return nullptr;
}

void Display::render() {
    SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
    SDL_Rect test = {100, 100, 100, 100};
    SDL_RenderFillRect(renderer_, &test);

    SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
    SDL_Rect test2 = {200, 200, 100, 100};
    SDL_RenderFillRect(renderer_, &test2);
}

SDL_Renderer* Display::getRenderer() {
    return renderer_;
}

void Display::drawGameObject(const GameObject& gameObject) {
    float cx, cy, zoom;
    Camera::get_position(cx, cy);
    Camera::get_zoom(zoom);
    SDL_Rect dstRect = {(int)((gameObject.position.x - cx) * zoom), (int)(gameObject.position.y - cy), (int)(gameObject.dimensions.x * zoom), (int)(gameObject.dimensions.y * zoom)};
    if (gameObject.texture){
        SDL_RenderCopy(renderer_, gameObject.texture, nullptr, &dstRect);
        return;
    }

    SDL_RenderDrawRect(renderer_, &dstRect);
}


