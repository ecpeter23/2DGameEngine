#pragma once
#include "SceneBase.h"
#include <memory>

class SceneManager {
public:
    SceneManager();
    void switchScene(std::unique_ptr<SceneBase> newScene);
    void update();
    void render();

private:
    std::unique_ptr<SceneBase> currentScene;
};