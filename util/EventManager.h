#pragma once

#include <functional>
#include <vector>
#include <map>

enum class EventType {
    // TODO: Add more event types as needed
    PlayerJump,
    PlayerShoot
};

class Event {
public:
    EventType type;
    // TODO: Add event data as needed
};

class EventManager {
public:
    void subscribe(EventType type, const std::function<void(Event&)>& listener) {
        listeners[type].push_back(listener);
    }

    void dispatch(Event& event) {
        for (auto& listener : listeners[event.type]) {
            listener(event);
        }
    }

private:
    std::map<EventType, std::vector<std::function<void(Event&)>>> listeners;
};
