// MenuScene.h
#pragma once
#include "box2d/box2d.h"
#include "../../scene/SceneBase.h"
#include "../../util/VerifiableRandom.h"
#include "../../object/PhysicsComponent.h"
#include "../../object/GameObject.h"
#include "../../input/InputHandler.h"


class MenuScene : public SceneBase {
public:
    explicit MenuScene(SDL_Renderer* renderer);
    ~MenuScene() override;

    void loadResources() override;
    void update() override;
    void updateInput(const SDL_Event& e) override;
    void render() override;

private:
    //TextEngine textEngine;
    b2World world;
    InputHandler inputHandler;
    std::string randomNumber;
    std::string randomNumberHash;
    std::unique_ptr<GameObject> player;
    std::unique_ptr<GameObject> ground;


    std::string verifyRandomNumber() {
        bool result = VerifiableRandom::verifyRandomNumber(randomNumber, randomNumberHash);
        return result ? "Verification: Passed" : "Verification: Failed";
    }

    void createPhysicsObject(std::unique_ptr<GameObject> &object, const v2_s &position, const v2_s &scale,
                        b2BodyType bodyType,
                        float shapeWidth, float shapeHeight);

    void applyForceToPlayer(const b2Vec2 &force);

    void setupActionHandlers();

    void setupInputBindings();
};
