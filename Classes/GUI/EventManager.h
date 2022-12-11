#include "eventBag.h"
#include <SFML/Graphics/RenderWindow.hpp>

class EventManager {
    EventBag bag;

public:
    void clear();
    EventBag *checkForEvents(sf::RenderWindow &window);
};

