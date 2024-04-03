#pragma once

#include <SDL.h>
#include "GameObject.h"
#include "box2d/box2d.h"

class GameObject;

class Component {
public:
    enum ComponentType {
        ComponentNone,
        ComponentTransform,
        ComponentAnimation,
        ComponentPhysics,
        ComponentSprite,
        ComponentController,
        ComponentCollider,
        ComponentLabel,
        ComponentButton,
        ComponentTextbox,
        ComponentQuadtree,
        ComponentCount
    };


    virtual ~Component() = default;
    virtual void update() {}
    virtual void render(SDL_Renderer* renderer) {}
    [[nodiscard]] virtual ComponentType getType() const = 0;

    void setGameObject(GameObject* gameObject) {
        this->gameObject = gameObject;
    }

protected:
    GameObject* gameObject = nullptr;
};
