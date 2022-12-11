#include <SFML/Window/Event.hpp>
#include <unordered_map>

class EventBag {
    std::unordered_map<sf::Event::EventType, sf::Event> m_events;

public:
    // adds an event to the bag
    void add(sf::Event::EventType eventType, sf::Event theEvent);

    // checks if an event is present.
    bool has(sf::Event::EventType eventType);

    // useful if you only want the event to be happening once.
    sf::Event *take(sf::Event::EventType eventType);

    // tries to get an event that may have happened on this frame
    sf::Event *get(sf::Event::EventType eventType);

    // clears the bag. is being called once a frame
    void clear();
};
