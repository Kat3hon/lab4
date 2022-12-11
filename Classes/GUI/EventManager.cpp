#include "EventManager.h"
#include <SFML/Window/Event.hpp>

EventBag *EventManager::checkForEvents(sf::RenderWindow &window) {
    sf::Event theEvent{};

    while (window.pollEvent(theEvent)) {
        bag.add(theEvent.type, theEvent);
    }

    return &bag;
}

void EventManager::clear() {
    bag.clear();
}