#pragma once

#include "../util/datatypes.h"
#include "CreateGameObject.h"
#include <string>
#include <SDL.h>

class GameObject {
public:
    enum class Type{
        SQUARE,
        CIRCLE,
        MESH
    };

    GameObject(std::string name, v2 position, v2 dimensions, Type type);
    GameObject(std::string name, v2 position, std::string  textureFile);

    v2 position;
    v2 dimensions{};
    std::string name;
    SDL_Texture* texture{};
    Type type;


    void addTexture(std::string filepath, bool remove = false);
    void addMeshCollider(bool remove = false);
    void addSquareCollider(bool remove = false);
    void addCircleCollider(bool remove = false);

    void addStaticBody(bool remove = false);
    void addKinematicBody(bool remove = false);
    void addRigidBody(bool remove = false);
    void addSoftBody(bool remove = false);

    void load(SDL_Renderer *renderer_);
    void render(SDL_Renderer *renderer_) const;

    [[nodiscard]] size_t getID() const;
private:
    std::string textureFile;
    static size_t nextID;
    size_t id;

    bool hasCollision{};
};
