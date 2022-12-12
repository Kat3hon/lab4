#include <SFML/Window/Event.hpp>
#include <unordered_map>

class EventStorage {

    /// Hash-table for events with its type, we need to save elements order
    std::unordered_map<sf::Event::EventType, sf::Event> events_map;

public:

    /// Adds an event to the storage
    void add(sf::Event::EventType eventType, sf::Event newEvent);

    /// Checks if an event of special type is already in storage
    bool inStock(sf::Event::EventType eventType);

    /// Gets an event of special type that may have happened on this frame
    sf::Event *at(sf::Event::EventType eventType);

    /// Clears the storage. is being called once a frame
    void clear();

    /// Gets an event of special type and erase it from storage
    sf::Event *pop(sf::Event::EventType eventType);
};
