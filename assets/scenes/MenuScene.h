// MenuScene.h
#pragma once
#include "../../scene/SceneBase.h"

class MenuScene : public SceneBase {
public:
    explicit MenuScene(SDL_Renderer* renderer);
    ~MenuScene() override;

    void loadResources() override;
    void update() override;
    void render() override;

private:
    TextEngine textEngine;
    std::shared_ptr<GameObject> testObject;
};
