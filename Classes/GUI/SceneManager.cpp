#include "SceneManager.h"
#include <iostream>

void SceneManager::update(EventBag *events) {
    if (m_scene == nullptr) {
        throw NoSceneSetException();
    }

    m_scene->update(game, events);
}

void SceneManager::draw(sf::RenderWindow &window) const {
    if (m_scene == nullptr) {
        throw NoSceneSetException();
    }

    m_scene->draw(window);
}

void SceneManager::fixedUpdate(EventBag *events) {

    if (m_scene == nullptr) {
        throw NoSceneSetException();
    }

    m_scene->fixedUpdate(game, events);
}

void SceneManager::setEngineContext(Game *game_var) {
    game = game_var;
}