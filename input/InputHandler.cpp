#include "InputHandler.h"

InputHandler::InputHandler() = default;

void InputHandler::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_KEYDOWN:
            {
                auto action = keyBindings.find(e.key.keysym.scancode);
                if (action != keyBindings.end()) {
                    processAction(action->second);
                }
            }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                auto action = mouseButtonBindings.find(e.button.button);
                if (action != mouseButtonBindings.end()) {
                    processAction(action->second);
                }
            }
                break;
            case SDL_FINGERDOWN:
            {
                auto action = touchBindings.find(e.tfinger.fingerId);
                if (action != touchBindings.end()) {
                    processAction(action->second);
                }
            }
                break;
            default:
                break;
        }
    }
}

void InputHandler::bindKey(SDL_Scancode key, ActionType action) {
    keyBindings[key] = action;
}

void InputHandler::bindMouseButton(Uint8 button, ActionType action) {
    mouseButtonBindings[button] = action;
}

void InputHandler::bindTouch(SDL_FingerID fingerId, ActionType action) {
    touchBindings[fingerId] = action;
}

void InputHandler::processAction(ActionType action) {
    auto handler = actionHandlers.find(action);
    if (handler != actionHandlers.end()) {
        handler->second();
    }
}