// MenuScene.cpp
#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(SDL_Renderer* renderer)
        : SceneBase(renderer), world(b2Vec2(0.0f, 9.8f)) {
    inputHandler = InputHandler();
    player = std::make_unique<GameObject>("Player");
    ground = std::make_unique<GameObject>("Ground");

    // Set up input bindings for player movement
    inputHandler.bindKey(SDL_SCANCODE_W, InputHandler::ActionType::MoveUp);
    inputHandler.bindKey(SDL_SCANCODE_S, InputHandler::ActionType::MoveDown);
    inputHandler.bindKey(SDL_SCANCODE_A, InputHandler::ActionType::MoveLeft);
    inputHandler.bindKey(SDL_SCANCODE_D, InputHandler::ActionType::MoveRight);

    // Set up action handlers for player movement
    inputHandler.setActionHandler(InputHandler::ActionType::MoveUp, [this]() {
        std::cout << "Move Up" << std::endl;
        auto* component = dynamic_cast<PhysicsComponent*>(player->getComponent(Component::ComponentPhysics));
        if (component) {
            component->applyForce({0, -10});
        }
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveDown, [this]() {
        std::cout << "Move Down" << std::endl;
        auto* component = dynamic_cast<PhysicsComponent*>(player->getComponent(Component::ComponentPhysics));
        if (component) {
            component->applyForce({0, 10});
        }
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveLeft, [this]() {
        std::cout << "Move Left" << std::endl;
        auto* component = dynamic_cast<PhysicsComponent*>(player->getComponent(Component::ComponentPhysics));
        if (component) {
            component->applyForce({-10, 0});
        }
    });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveRight, [this]() {
        std::cout << "Move Right" << std::endl;
        auto* component = dynamic_cast<PhysicsComponent*>(player->getComponent(Component::ComponentPhysics));
        if (component) {
            component->applyForce({10, 0});
        }
    });
}

MenuScene::~MenuScene() {
    player->clearComponents();
    ground->clearComponents();
}

void MenuScene::loadResources() {
    // Load resources specific to the menu scene
    player->addComponent(std::make_unique<TransformComponent>(v2_s{100, 100}, 0.0f, v2_s{10, 10}));

    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(100, 100);

    b2PolygonShape playerShape;
    playerShape.SetAsBox(0.5f, 0.5f); // Half-width and half-height of the player

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerShape;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.3f;

    player->addComponent(std::make_unique<PhysicsComponent>(&world, playerBodyDef, playerFixtureDef));

    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(100, 400);
    b2PolygonShape groundShape;
    groundShape.SetAsBox(1, 1);
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 1.0f;
    groundFixtureDef.friction = 0.3f;
    ground->addComponent(std::make_unique<TransformComponent>(v2_s{400, 50}, 0.0f, v2_s{100, 20}));
    ground->addComponent(std::make_unique<PhysicsComponent>(&world, groundBodyDef, groundFixtureDef));
}

void MenuScene::update() {
    world.Step(1.0f / 60.0f, 6, 2);
    player->update();
    ground->update();
}

void MenuScene::updateInput(const SDL_Event& e) {
    inputHandler.update(e);
}

void MenuScene::render() {
    //textEngine.renderText("Basic Scene", 100, 50, {255, 255, 255, 255});
    player->render(renderer_);
    ground->render(renderer_);
}
