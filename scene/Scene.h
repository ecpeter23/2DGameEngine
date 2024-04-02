#pragma once

#include <SDL.h>
#include <memory>
#include <vector>
#include "../util/datatypes.h"

class GameObject; // Forward declaration

class Scene {
public:
    Scene(SDL_Renderer *renderer_, int sceneID);
    virtual ~Scene() = default;;

    void addGameObject(const std::shared_ptr<GameObject>& gameObject);
    virtual void loadResources();
    virtual void freeResources();
    virtual void loadSceneData();
    virtual void update();
    virtual void render();

protected:
    int sceneID;
    SDL_Renderer* renderer_;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};
