#include "InputHandler.h"
#include <iostream>
#include <utility>

InputHandler::InputHandler() = default;

void InputHandler::update(const SDL_Event& e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        {
            // std::cout << "Key press detected: " << e.key.keysym.sym << std::endl;
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
    // std::cout << "Processing action: " << static_cast<int>(action) << std::endl;
    auto handler = actionHandlers.find(action);
    if (handler != actionHandlers.end()) {
        handler->second();
    }
}

void InputHandler::setActionHandler(ActionType action, std::function<void()> handler) {
    actionHandlers[action] = std::move(handler);
}