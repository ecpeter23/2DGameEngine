#pragma once

#include <SDL.h>
#include "Scene.h"

class SceneManager {
public:
    Scene* currentScene;

    SceneManager();

    void loadScene(Scene* newScene);
};
