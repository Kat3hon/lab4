#pragma once

#include "EventStorage.h"
#include <SFML/Graphics/RenderWindow.hpp>

class EventManager {

    /// Storage for events
    EventStorage storage;

public:
    /// Clears all previous events from the bag, should be used before all other methods
    void clear();

    /// Checks for new events, is being called once a frame
    EventStorage *checkForEvents(sf::RenderWindow &window);
};

