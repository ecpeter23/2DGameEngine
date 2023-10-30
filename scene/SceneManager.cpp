#include "SceneManager.h"
#include "../util/datatypes.h"
#include <iostream>

SceneManager::SceneManager() : currentScene(nullptr) {}

void SceneManager::loadScene(Scene* newScene) {
    if (currentScene) {
        currentScene->freeResources();
    }

    currentScene = newScene;
    ASSERT(currentScene, "failed to load scene: %s\n", SDL_GetError());

    currentScene->loadSceneData();
    currentScene->loadResources();
}

