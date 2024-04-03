#include "QuadTree.h"


QuadTree::QuadTree(int level, const SDL_Rect& bounds)
        : level(level), maxObjects(13), maxLevels(5), bounds(bounds) {
    for (auto& child : children) {
        child = nullptr;
    }
}

/*void QuadTree::insert(const GameObject& object) {
    if (children[0] != nullptr) {
        int index = getIndex(object);
        if (index != -1) {
            children[index]->insert(object);
            return;
        }
    }

    objects.push_back(object);

    if (objects.size() > maxObjects && level < maxLevels) {
        if (children[0] == nullptr) {
            split();
        }

        auto it = objects.begin();
        while (it != objects.end()) {
            int index = getIndex(*it);
            if (index != -1) {
                children[index]->insert(*it);
                it = objects.erase(it);
            } else {
                ++it;
            }
        }
    }
}*/

void QuadTree::clear() {
    objects.clear();

    for (auto& child : children) {
        if (child != nullptr) {
            child->clear();
            child.reset();
        }
    }
}

/*std::vector<GameObject> QuadTree::retrieve(const GameObject& object) {
    std::vector<GameObject> potentialColliders;
    int index = getIndex(object);
    if (index != -1 && children[0] != nullptr) {
        potentialColliders = children[index]->retrieve(object);
    } else {
        for (auto& child : children) {
            if (child != nullptr) {
                std::vector<GameObject> childColliders = child->retrieve(object);
                potentialColliders.insert(potentialColliders.end(), childColliders.begin(), childColliders.end());
            }
        }
    }

    potentialColliders.insert(potentialColliders.end(), objects.begin(), objects.end());

    return potentialColliders;
}*/


void QuadTree::split() {
    int childWidth = bounds.w / 2;
    int childHeight = bounds.h / 2;

    children[0] = std::make_unique<QuadTree>(level + 1, SDL_Rect{bounds.x + childWidth, bounds.y, childWidth, childHeight});
    children[1] = std::make_unique<QuadTree>(level + 1, SDL_Rect{bounds.x, bounds.y, childWidth, childHeight});
    children[2] = std::make_unique<QuadTree>(level + 1, SDL_Rect{bounds.x, bounds.y + childHeight, childWidth, childHeight});
    children[3] = std::make_unique<QuadTree>(level + 1, SDL_Rect{bounds.x + childWidth, bounds.y + childHeight, childWidth, childHeight});
}

/*int QuadTree::getIndex(const GameObject& object) const {
    int index = -1;
    double verticalMidpoint = bounds.x + (bounds.w / 2);
    double horizontalMidpoint = bounds.y + (bounds.h / 2);

    bool topQuadrant = (object.position.y < horizontalMidpoint && object.position.y + object.dimensions.y < horizontalMidpoint);
    bool bottomQuadrant = (object.position.y + object.dimensions.y > horizontalMidpoint);

    if (object.position.x < verticalMidpoint && object.position.x + object.dimensions.x < verticalMidpoint) {
        if (topQuadrant) {
            index = 1;
        } else if (bottomQuadrant) {
            index = 2;
        }
    } else if (object.position.x + object.dimensions.x > verticalMidpoint) {
        if (topQuadrant) {
            index = 0;
        } else if (bottomQuadrant) {
            index = 3;
        }
    }

    return index;
}*/

void QuadTree::drawSections(SDL_Renderer *renderer) const {
    float cx, cy;
    Camera::get_position(cx, cy);
    SDL_Rect rect = {bounds.x - static_cast<int>(cx), bounds.y - static_cast<int>(cy), bounds.w, bounds.h};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    for (const auto &child : children) {
        if (child) {
            child->drawSections(renderer);
        }
    }
}
