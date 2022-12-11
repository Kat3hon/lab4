#include "EventBag.h"

void EventBag::add(sf::Event::EventType eventType, sf::Event theEvent) {
    m_events[eventType] = theEvent;
}

bool EventBag::has(sf::Event::EventType eventType) {
    auto it = m_events.find(eventType);

    return it != m_events.end();
}

sf::Event *EventBag::get(sf::Event::EventType eventType) {
    return &m_events[eventType];
}

void EventBag::clear() {
    m_events.clear();
}

sf::Event *EventBag::take(sf::Event::EventType eventType) {
    auto event = get(eventType);
    m_events.erase(eventType);

    return event;
}