#include "SceneManager.h"

SceneManager::SceneManager() : currentScene(nullptr) {}

void SceneManager::switchScene(std::unique_ptr<SceneBase> newScene) {
    currentScene = std::move(newScene);
    currentScene->loadResources();
}

void SceneManager::update() {
    if (currentScene) {
        currentScene->update();
    }
}

void SceneManager::updateInput(const SDL_Event& e) {
    if (currentScene) {
        currentScene->updateInput(e);
    }
}

void SceneManager::render() {
    if (currentScene) {
        currentScene->render();
    }
}