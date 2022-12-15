#include "Scene.h"
#include "Game.h"

void Scene::update(Game *game, EventStorage *events) {

    auto event = events->at(sf::Event::EventType::MouseButtonReleased);

    if (event == nullptr) return;
    if (event->mouseButton.button != sf::Mouse::Button::Left) return;

    gui_manager.checkClick({event->mouseButton.x, event->mouseButton.y});

}

void Scene::pushElement(GUI_Element *element) {
    gui_manager.push_back(element);
}

