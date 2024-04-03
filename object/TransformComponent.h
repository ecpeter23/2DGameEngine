#pragma once

#include "Component.h"
#include "../util/datatypes.h"
#include "../util/Camera.h"

class TransformComponent : public Component {
public:
    v2_s position;
    float rotation;
    v2_s scale;

    explicit TransformComponent(v2_s pos = {0, 0}, float rot = 0.0f, v2_s scl = {1, 1})
            : position(pos), rotation(rot), scale(scl) {}

    void update() override {
        // Update logic for the transform component
    }

    void render(SDL_Renderer* renderer) override {
        // Rendering logic for the transform component, if any
        // Test Render
        f32 cx, cy, zoom;
        Camera::get_position(cx, cy);
        Camera::get_zoom(zoom);
        SDL_Rect dstRect = {(int)((this->position.x - cx) * zoom), (int)(this->position.y - cy), (int)(this->scale.x * zoom), (int)(this->scale.y * zoom)};

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &dstRect);
    }

    [[nodiscard]] ComponentType getType() const override {
        return ComponentType::ComponentTransform;
    }

    void move(v2_s delta) {
        position.x += delta.x;
        position.y += delta.y;
    }

    void rotate(float delta) {
        rotation += delta;
    }

    void scaleBy(v2_s delta) {
        scale.x *= delta.x;
        scale.y *= delta.y;
    }

    void setScale(v2_s scl) {
        scale = scl;
    }

    void setPosition(v2_s pos) {
        position = pos;
    }

    void setRotation(float rot) {
        rotation = rot;
    }
};