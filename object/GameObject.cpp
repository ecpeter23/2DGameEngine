#include "GameObject.h"
#include <utility>
#include "../util/Camera.h"
#include<SDL_render.h>

size_t GameObject::nextID = 0;

GameObject::GameObject(std::string name, v2_s position, v2_s dimension, Type type) : name(std::move(name)), position(position), dimensions(dimension), type(type) {
    id = nextID++;
}

GameObject::GameObject(std::string name, v2_s position, std::string  textureFile) : name(std::move(name)), position(position), type(GameObject::Type::MESH), textureFile(std::move(textureFile))  {
    id = nextID++;
}

void GameObject::addTexture(std::string filepath, bool remove) {
    if (remove){
        SDL_DestroyTexture(texture);
        texture = nullptr;
        textureFile.clear();
        return;
    }

    textureFile = std::move(filepath);
}

void GameObject::load(SDL_Renderer *renderer_) {
    if (textureFile.empty()){ return; }

    SDL_Surface* surface = SDL_LoadBMP((SOURCE_DIR + textureFile).c_str());
    ASSERT(surface, "Failed to load texture: %s\n", SDL_GetError());

    texture = SDL_CreateTextureFromSurface(renderer_, surface);
    ASSERT(texture, "Failed to create texture: %s\n", SDL_GetError());

    SDL_FreeSurface(surface);
}

void GameObject::render(SDL_Renderer *renderer_) const{
    f32 cx, cy, zoom;
    Camera::get_position(cx, cy);
    Camera::get_zoom(zoom);
    SDL_Rect dstRect = {(int)((position.x - cx) * zoom), (int)(position.y - cy), (int)(dimensions.x * zoom), (int)(dimensions.y * zoom)};

    if (texture){
        SDL_RenderCopy(renderer_, texture, nullptr, &dstRect);
        return;
    }

    SDL_RenderDrawRect(renderer_, &dstRect);
}

void GameObject::addMeshCollider(bool remove) {

}

void GameObject::addSquareCollider(bool remove) {

}

void GameObject::addCircleCollider(bool remove) {

}

void GameObject::addStaticBody(bool remove) {

}

void GameObject::addKinematicBody(bool remove) {

}

void GameObject::addRigidBody(bool remove) {

}

void GameObject::addSoftBody(bool remove) {

}

// Add the getID() function definition
size_t GameObject::getID() const {
    return id;
}



