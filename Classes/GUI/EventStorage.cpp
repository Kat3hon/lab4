#include "EventStorage.h"

void EventStorage::add(sf::Event::EventType eventType, sf::Event newEvent) {
    events_map[eventType] = newEvent;
}

bool EventStorage::inStock(sf::Event::EventType eventType) {
    // A place of that event, equals map's end,
    // If there is no that type of event in storage
    auto it = events_map.find(eventType);

    return it != events_map.end();
}

sf::Event *EventStorage::at(sf::Event::EventType eventType) {
    return &events_map[eventType];
}

void EventStorage::clear() {
    events_map.clear();
}

sf::Event *EventStorage::pop(sf::Event::EventType eventType) {
    auto event = at(eventType);
    events_map.erase(eventType);

    return event;
}