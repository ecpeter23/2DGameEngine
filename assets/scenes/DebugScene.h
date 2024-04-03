// DebugScene.h
#pragma once
#include "box2d/box2d.h"
#include "../../scene/SceneBase.h"
#include "../../util/VerifiableRandom.h"
#include "../../object/PhysicsComponent.h"
#include "../../object/GameObject.h"
#include "../../input/InputHandler.h"


class DebugScene : public SceneBase {
public:
    explicit DebugScene(SDL_Renderer* renderer);
    ~DebugScene() override;

    void loadResources() override;
    void update() override;
    void updateInput(const SDL_Event& e) override;
    void render() override;

private:
    TextEngine textEngine;
    std::unique_ptr<GameObject> player;
    InputHandler inputHandler;
};
