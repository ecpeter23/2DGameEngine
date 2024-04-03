#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "TransformComponent.h"

class GameObject {
public:
    explicit GameObject(std::string name);
    virtual ~GameObject() = default;

    void addComponent(std::unique_ptr<Component> component);
    [[nodiscard]] Component* getComponent(Component::ComponentType type) const;
    void update();
    void render(SDL_Renderer* renderer);
    void clearComponents();

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] size_t getID() const;

private:
    std::string name;
    size_t id;
    std::vector<std::unique_ptr<Component>> components;
    static size_t nextID;
};
