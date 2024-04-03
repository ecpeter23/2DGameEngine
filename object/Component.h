#pragma once

#include <SDL.h>

class Component {
public:
    enum ComponentType {
        ComponentNone,
        ComponentTransform,
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
};
