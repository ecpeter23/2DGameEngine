#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(SDL_Renderer* renderer)
        : SceneBase(renderer), world(b2Vec2(0.0f, 9.8f)) {
    inputHandler = InputHandler();
    player = std::make_unique<GameObject>("Player");
    ground = std::make_unique<GameObject>("Ground");

    setupInputBindings();
    setupActionHandlers();
}

MenuScene::~MenuScene() {
    player->clearComponents();
    ground->clearComponents();
}

void MenuScene::loadResources() {
    createPhysicsObject(player, {100, 100}, {10, 10}, b2_dynamicBody, 0.5f, 0.5f);
    createPhysicsObject(ground, {75, 200}, {100, 20}, b2_staticBody, 50, 10);
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
    player->render(renderer_);
    ground->render(renderer_);
}

void MenuScene::setupInputBindings() {
    inputHandler.bindKey(SDL_SCANCODE_SPACE, InputHandler::ActionType::MoveUp);
    inputHandler.bindKey(SDL_SCANCODE_S, InputHandler::ActionType::MoveDown);
    inputHandler.bindKey(SDL_SCANCODE_A, InputHandler::ActionType::MoveLeft);
    inputHandler.bindKey(SDL_SCANCODE_D, InputHandler::ActionType::MoveRight);
}

void MenuScene::setupActionHandlers() {
    inputHandler.setActionHandler(InputHandler::ActionType::MoveUp, [this]() { applyForceToPlayer({0, -1000}); });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveDown, [this]() { applyForceToPlayer({0, 100}); });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveLeft, [this]() { applyForceToPlayer({-100, 0}); });
    inputHandler.setActionHandler(InputHandler::ActionType::MoveRight, [this]() { applyForceToPlayer({100, 0}); });
}

void MenuScene::applyForceToPlayer(const b2Vec2& force) {
    auto* component = dynamic_cast<PhysicsComponent*>(player->getComponent(Component::ComponentPhysics));
    if (component) {
        component->applyForce(force);
    }
}

void MenuScene::createPhysicsObject(std::unique_ptr<GameObject>& object, const v2_s& position, const v2_s& scale, b2BodyType bodyType, float shapeWidth, float shapeHeight) {
    object->addComponent(std::make_unique<TransformComponent>(position, 0.0f, scale));

    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(position.x, position.y);

    b2PolygonShape shape;
    shape.SetAsBox(shapeWidth, shapeHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    object->addComponent(std::make_unique<PhysicsComponent>(&world, bodyDef, fixtureDef));
}

static void tellPositionOfPlayer(GameObject &player) {
    auto* transform = dynamic_cast<TransformComponent*>(player.getComponent(Component::ComponentTransform));
    if (transform) {
        std::cout << "Player position: " << transform->position.x << ", " << transform->position.y << std::endl;
    }
}
