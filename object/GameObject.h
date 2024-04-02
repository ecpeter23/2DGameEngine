#pragma once

#include "../util/datatypes.h"
#include <memory>
#include <string>
#include <SDL.h>

class GameObject {
public:
    virtual ~GameObject() = default;

    enum class Type{
        SQUARE,
        CIRCLE,
        MESH
    };

    static std::shared_ptr<GameObject> create(const std::string& name, v2_s position, v2_s dimensions, Type type) {
        return std::make_shared<GameObject>(name, position, dimensions, type);
    }

    static std::shared_ptr<GameObject> create(const std::string& name, v2_s position, std::string textureFile) {
        return std::make_shared<GameObject>(name, position, std::move(textureFile));
    }

    GameObject(std::string name, v2_s position, v2_s dimensions, Type type);
    GameObject(std::string name, v2_s position, std::string  textureFile);

    v2_s position;
    v2_s dimensions{};
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
    virtual void update();

    [[nodiscard]] size_t getID() const;
private:
    std::string textureFile;
    static size_t nextID;
    size_t id;

    bool hasCollision{};
};
