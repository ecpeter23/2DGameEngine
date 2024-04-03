#pragma once

#include "Component.h"
#include "../util/datatypes.h"
#include <vector>
#include <SDL.h>

struct Frame {
    SDL_Rect rect;
    float duration; // Duration of the frame in seconds
};

class AnimationComponent : public Component {
public:
    AnimationComponent() = default;

    // Adds a texture to the animation sequence
    void addTexture(SDL_Texture* texture) {
        textures.push_back(texture);
    }

    void addTextures(const std::vector<SDL_Texture*>& textures) {
        this->textures.insert(this->textures.end(), textures.begin(), textures.end());
    }

    [[nodiscard]] ComponentType getType() const override {
        return ComponentType::ComponentAnimation;
    }

    // Update the animation based on the time elapsed
    void update(float deltaTime) {
        if (textures.empty()) return;

        currentFrameDuration += deltaTime;
        if (currentFrameDuration >= frameDurations[currentFrame]) {
            currentFrameDuration = 0.0f;
            currentFrame = (currentFrame + 1) % textures.size();
        }
    }

    // Render the current frame
    void render(SDL_Renderer* renderer, const SDL_Rect& dstRect) {
        if (!textures.empty() && currentFrame < textures.size()) {
            SDL_RenderCopy(renderer, textures[currentFrame], nullptr, &dstRect);
        }
    }

    // Sets frame durations for each texture
    void setFrameDurations(const std::vector<float>& durations) {
        frameDurations = durations;
    }

private:
    std::vector<SDL_Texture*> textures;
    std::vector<float> frameDurations; // Seconds per frame
    size_t currentFrame = 0;
    float currentFrameDuration = 0.0f; // Elapsed time in the current frame
};
