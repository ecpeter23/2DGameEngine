#include "Scene.h"
#include "../object/GameObject.h"

Scene::Scene(SDL_Renderer *renderer_, i32 sceneID)
        : renderer_(renderer_), sceneID(sceneID) {
}

void Scene::addGameObject(const std::shared_ptr<GameObject>& gameObject) {
    gameObjects.push_back(gameObject);
}

void Scene::loadResources() {
    for (auto& gameObject : gameObjects) {
        gameObject->load(renderer_);
    }
}

void Scene::freeResources() {
    for (auto& gameObject : gameObjects) {
        SDL_DestroyTexture(gameObject->texture);
        gameObject->texture = nullptr;
    }
}

void Scene::loadSceneData() {
    // Clear existing game objects
    gameObjects.clear();

    // Load scene-specific data
}

void Scene::update() {
    // Update game objects
    for (const auto& gameObject : gameObjects) {
        gameObject->update();
    }
}

void Scene::render() {
    // Render game objects
    for (const auto& gameObject : gameObjects) {
        gameObject->render(renderer_);
    }
}
