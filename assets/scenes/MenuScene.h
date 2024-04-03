// MenuScene.h
#pragma once
#include "../../scene/SceneBase.h"
#include "../../util/VerifiableRandom.h"

class MenuScene : public SceneBase {
public:
    explicit MenuScene(SDL_Renderer* renderer);
    ~MenuScene() override;

    void loadResources() override;
    void update() override;
    void render() override;

private:
    TextEngine textEngine;
    //std::shared_ptr<GameObject> testObject;
    std::string randomNumber;
    std::string randomNumberHash;
    std::unique_ptr<GameObject> player;

    std::string verifyRandomNumber() {
        bool result = VerifiableRandom::verifyRandomNumber(randomNumber, randomNumberHash);
        return result ? "Verification: Passed" : "Verification: Failed";
    }
};
