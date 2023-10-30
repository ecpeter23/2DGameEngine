#pragma once

#include <SDL.h>
#include <unordered_map>
#include <functional>

class InputHandler {
public:
    InputHandler();

    enum class ActionType{};

    void update();
    void bindKey(SDL_Scancode key, ActionType action);
    void processAction(ActionType action);
private:
    std::unordered_map<SDL_Scancode, ActionType> keyBindings;
    std::unordered_map<ActionType, std::function<void()>> actionHandlers;
};