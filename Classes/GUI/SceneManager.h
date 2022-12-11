#pragma once
#include "Scene.h"
#include "noSceneSetException.h"
#include "EventBag.h"
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class SceneManager {

    std::unique_ptr<Scene> m_scene;
    Game *game;
public:
    template<class SceneClass, class ...Args>
    void setScene(Args... args) {
        if (m_scene != nullptr) {
            m_scene->onLeave(game);
        }

        m_scene.reset();
        m_scene = std::make_unique<SceneClass>(args...);
        m_scene->onGUI(game);
        m_scene->onEnter(game);
    }

    void fixedUpdate(EventBag *events);

    void update(EventBag *event);

    void draw(sf::RenderWindow &window) const;

    void setEngineContext(Game *game_var);

};
