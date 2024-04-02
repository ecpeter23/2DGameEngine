#pragma once

#include <memory>
#include <vector>
#include "../object/GameObject.h"
#include "../UI/TextEngine.h"
#include <SDL.h>

class SceneBase {
public:
    SceneBase(SDL_Renderer* renderer) : renderer_(renderer) {}
    virtual ~SceneBase() = default;

    virtual void loadResources() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    SDL_Renderer* renderer_;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};
