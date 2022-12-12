#include "EventManager.h"
#include <SFML/Window/Event.hpp>

EventStorage *EventManager::checkForEvents(sf::RenderWindow &window) {
    sf::Event currentEvent{};

    // Pop the event on top of the event queue, if any, and return it;
    // False if queue is empty
    while (window.pollEvent(currentEvent))
        storage.add(currentEvent.type, currentEvent);

    // We need to return a reference just because EventStorage is a big object
    return &storage;
}

void EventManager::clear() {
    storage.clear();
}