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
    void addFrame(Frame frame) {
        frames.push_back(frame);
    }

    void update() override {
        currentFrameTime += 1.0f / 60.0f; // Assuming 60 FPS, adjust according to your game's frame rate
        if (currentFrameTime >= frames[currentFrame].duration) {
            currentFrame = (currentFrame + 1) % frames.size();
            currentFrameTime = 0.0f;
        }
    }

    void render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& dstRect) {
        SDL_RenderCopy(renderer, texture, &frames[currentFrame].rect, &dstRect);
    }

private:
    std::vector<Frame> frames;
    int currentFrame = 0;
    float currentFrameTime = 0.0f;
};
