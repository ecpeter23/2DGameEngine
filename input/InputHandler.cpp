#include "InputHandler.h"

InputHandler::InputHandler() = default;

void InputHandler::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            auto action = keyBindings.find(e.key.keysym.scancode);
            if (action != keyBindings.end()) {
                processAction(action->second);
            }
        }
    }
}

void InputHandler::bindKey(SDL_Scancode key, ActionType action) {
    keyBindings[key] = action;
}

void InputHandler::processAction(ActionType action) {
    auto handler = actionHandlers.find(action);
    if (handler != actionHandlers.end()) {
        handler->second();
    }
}