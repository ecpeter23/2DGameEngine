#pragma once

#include <string>
#include <memory>
#include "../util/datatypes.h"
#include "GameObject.h"

class GameObject;

class CreateGameObject {
public:
    static std::shared_ptr<GameObject> createSquareGameObject(const std::string& name, const v2 & position, const v2 & size){
        return std::make_shared<GameObject>(name, position, size, GameObject::Type::SQUARE);
    }
    static std::shared_ptr<GameObject> createCircleGameObject(const std::string& name, const v2 & position, const v2 & dimensions){
        return std::make_shared<GameObject>(name, position, dimensions, GameObject::Type::CIRCLE);
    }

    static std::shared_ptr<GameObject> createMeshGameObject(const std::string& name, const v2 & position, const std::string& meshFile){
        return std::make_shared<GameObject>(name, position, meshFile);
    }
};

