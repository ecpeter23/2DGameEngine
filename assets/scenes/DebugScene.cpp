//
// Created by Eli Peter on 4/3/24.
//

#include "DebugScene.h"
#include <iostream>

DebugScene::DebugScene(SDL_Renderer *renderer) : SceneBase(renderer),  textEngine(renderer)  {
     // Create a new input handler
     inputHandler = InputHandler();
     player = std::make_unique<GameObject>("Player");

    // Test binding keys
    inputHandler.bindKey(SDL_SCANCODE_W, InputHandler::ActionType::MoveUp);
    inputHandler.bindKey(SDL_SCANCODE_S, InputHandler::ActionType::MoveDown);
    inputHandler.bindKey(SDL_SCANCODE_A, InputHandler::ActionType::MoveLeft);
    inputHandler.bindKey(SDL_SCANCODE_D, InputHandler::ActionType::MoveRight);

    // Test binding mouse buttons
    // inputHandler.bindMouseButton(SDL_BUTTON_LEFT, InputHandler::ActionType::MoveUp);
    // inputHandler.bindMouseButton(SDL_BUTTON_RIGHT, InputHandler::ActionType::MoveDown);

    // Test Input
    inputHandler.setActionHandler(InputHandler::ActionType::MoveUp, [this]() {
        std::cout << "Move Up" << std::endl;
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveDown, [this]() {
        std::cout << "Move Down" << std::endl;
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveLeft, [this]() {
        std::cout << "Move Left" << std::endl;
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveRight, [this]() {
        std::cout << "Move Right" << std::endl;
    });
}

DebugScene::~DebugScene() = default;

void DebugScene::loadResources() {
    player->addComponent(std::make_unique<TransformComponent>(v2_s{100, 100}, 0.0f, v2_s{10, 10}));
}

void DebugScene::update() {
    player->update();
}

void DebugScene::updateInput(const SDL_Event& e) {
    inputHandler.update(e);
}

void DebugScene::render() {
    textEngine.renderText("DEBUG -- TEST", 100, 50, {255, 255, 255, 255});
    player->render(renderer_);
}
