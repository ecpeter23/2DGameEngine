#pragma once
#include "SceneBase.h"
#include <memory>

class SceneManager {
public:
    SceneManager();
    void switchScene(std::unique_ptr<SceneBase> newScene);
    void update();
    void updateInput(const SDL_Event& e);
    void render();

private:
    std::unique_ptr<SceneBase> currentScene;


};