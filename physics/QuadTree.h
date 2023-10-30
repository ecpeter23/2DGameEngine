#pragma once

#include <memory>
#include <vector>
#include <SDL.h>
#include <array>
#include "../object/GameObject.h"
#include "../util/Camera.h"

class QuadTree {
public:
    QuadTree(int level, const SDL_Rect& bounds);
    void clear();
    void insert(const GameObject& object);
    std::vector<GameObject> retrieve(const GameObject& object);
    void drawSections(SDL_Renderer *renderer) const;

private:
    int level;
    int maxObjects;
    int maxLevels;

    SDL_Rect bounds;
    std::vector<GameObject> objects;
    std::array<std::unique_ptr<QuadTree>, 4> children;

    void split();
    [[nodiscard]] int getIndex(const GameObject& object) const;
};