#include "GUI_Element.h"

#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class GUI_Manager {
public:
    void registerElement(GUI_Element *element);

    void resolveClick(sf::Vector2i position);

private:
    std::vector<GUI_Element *> m_elements;
};