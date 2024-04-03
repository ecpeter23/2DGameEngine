#pragma once

#include <SDL.h>
#include <unordered_map>
#include <functional>

class InputHandler {
public:
    InputHandler();

    enum class ActionType {
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight
    };

    void update(const SDL_Event& e);
    void bindKey(SDL_Scancode key, ActionType action);
    void bindMouseButton(Uint8 button, ActionType action);
    void bindTouch(SDL_FingerID fingerId, ActionType action);
    void processAction(ActionType action);
    void setActionHandler(ActionType action, std::function<void()> handler);

private:
    std::unordered_map<SDL_Scancode, ActionType> keyBindings;
    std::unordered_map<Uint8, ActionType> mouseButtonBindings;
    std::unordered_map<SDL_FingerID, ActionType> touchBindings;
    std::unordered_map<ActionType, std::function<void()>> actionHandlers;


};