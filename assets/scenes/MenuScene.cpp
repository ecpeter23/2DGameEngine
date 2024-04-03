#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(SDL_Renderer* renderer)
        : SceneBase(renderer), textEngine(renderer) {
    player = std::make_unique<GameObject>("Player");
}

MenuScene::~MenuScene() = default;

void MenuScene::loadResources() {
    // Load resources specific to the menu scene
    player->addComponent(std::make_unique<TransformComponent>(v2_s{100, 100}, 0.0f, v2_s{10, 10}));
    //testObject = GameObject::create("Square", {0, 0}, {100, 100}, GameObject::Type::SQUARE);
    //testObject->load(renderer_);

    randomNumber = VerifiableRandom::generateRandomNumber(0, 1000, randomNumberHash);
}

void MenuScene::update() {
    // Update logic for the menu scene
    player->update();
}

void MenuScene::render() {
    // Render the menu scene
    textEngine.setFontSize(24);
    textEngine.renderText("Welcome to the Menu", 100, 50, {255, 255, 255, 255});
    textEngine.setFontStyle(TTF_STYLE_BOLD);
    textEngine.setFontSize(12);
    textEngine.renderText("Random Number: " + randomNumber, 100, 100, {255, 255, 255, 255});
    textEngine.renderText("Hash: " + randomNumberHash, 100, 150, {255, 255, 255, 255});
    //testObject->render(renderer_);
    player->render(renderer_);
}

