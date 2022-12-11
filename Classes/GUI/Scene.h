#include "GUI_Manager.h"
#include "GUI_Element.h"
#include "EventBag.h"

#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Game;

class Scene {
    using event = sf::Event;
    using eventType = event::EventType;

    GUI_Manager guiManager;

public:
    explicit Scene() {
        // This is the generic font being used in every scene.
        m_font.loadFromFile("asset/font/Arial.ttf");
    }

    // This method is always called 60 times a second.
    virtual void fixedUpdate(Game *game, EventBag *events);

    // This method should always be called, if inherited. Since this will listen to events and UI states.
    virtual void update(Game *game, EventBag *events);

    // Callback for making drawings to the screen.
    virtual void draw(sf::RenderWindow &window) const;

    // Callback before an actual update or draw startLoop will happen.
    virtual void onEnter(Game *game);

    // Callback just before this scene will get destroyed by the manager.
    virtual void onLeave(Game *game);

    // Callback whenever the window loses focus or user presses a button.
    virtual void onPause(Game *game);

    // Callback used for setting up the UI, gets called before `onEnter`
    virtual void onGUI(Game *game);

    // This is just a fancy, totally unnecessary ctor
    // But it is used to make instantiating UI elements look standard.
    template<class T, class ...Args>
    T createElement(Args... args) {
        return T(args...);
    }

    // Registers the element to the UI manager. So it can handle basic click events.
    void registerElement(GUI_Element *element);
protected:
    sf::Font m_font;
};
