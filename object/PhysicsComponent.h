#pragma once

#include <box2d/box2d.h>
#include "Component.h"
#include "TransformComponent.h"
#include "GameObject.h"


class PhysicsComponent : public Component {
public:
    PhysicsComponent(b2World* world, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef) {
        body = world->CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);
    }

    ~PhysicsComponent() override {
        body->GetWorld()->DestroyBody(body);
    }

    void update() override {
        auto* transform = dynamic_cast<TransformComponent*>(gameObject->getComponent(ComponentType::ComponentTransform));
        if (transform) {
            b2Vec2 position = body->GetPosition();
            transform->position.x = position.x;
            transform->position.y = position.y;
            transform->rotation = body->GetAngle();
        }
    }

    void applyForce(const b2Vec2& force) {
        body->ApplyForceToCenter(force, true);
    }

    [[nodiscard]] b2Body* getBody() const {
        return body;
    }

    [[nodiscard]] ComponentType getType() const override {
        return ComponentType::ComponentPhysics;
    }

private:
    b2Body* body;
};
