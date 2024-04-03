#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* renderer)
        : SceneBase(renderer), textEngine(renderer) {}

MenuScene::~MenuScene() = default;

void MenuScene::loadResources() {
    // Load resources specific to the menu scene
    testObject = GameObject::create("Square", {0, 0}, {100, 100}, GameObject::Type::SQUARE);
    testObject->load(renderer_);

    randomNumber = VerifiableRandom::generateRandomNumber(0, 1000, randomNumberHash);
}

void MenuScene::update() {
    // Update logic for the menu scene
}

void MenuScene::render() {
    // Render the menu scene
    textEngine.renderText("Welcome to the Menu", 100, 50, 24, {255, 255, 255, 255});
    textEngine.renderText("Random Number: " + randomNumber, 100, 100, 12, {255, 255, 255, 255});
    textEngine.renderText(verifyRandomNumber(), 100, 150, 24, {255, 255, 255, 255});
    testObject->render(renderer_);
}