#include "GUI_Manager.h"
#include "GUI_Element.h"
#include "EventStorage.h"

#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Game;

class Scene {

    using event = sf::Event;
    using eventType = event::EventType;

    /// Handle the buttons on the screen.
    GUI_Manager gui_manager;

protected:

    /// Font, that will be used in the application (e.g. names of buttons).
    sf::Font font;

public:

    explicit Scene() {
        // Set font
        if (!font.loadFromFile("assets/Comfortaa.ttf"))
            MessageBox(nullptr, "Can not load a font Comfortaa.ttf", "Error!", MB_OK);
    }

    //todo: do this "needed to be..." methods pure virtual or not?

    /// This method is always called 60 times a second. Needed to be described by inheritors.
    virtual void fixedUpdate(Game *game, EventStorage *events) {};

    /// This method should always be called, if inherited. Since this will listen to events and UI states.
    virtual void update(Game *game, EventStorage *events);

    /// Callback for making drawings to the screen. Needed to be described by inheritors.
    virtual void draw(sf::RenderWindow &window) const;

    /// Callback before an actual update or draw startLoop will happen. Needed to be described by inheritors.
    virtual void cbEnter(Game *game) {};

    /// Callback just before this scene will get destroyed by the manager. Needed to be described by inheritors.
    virtual void cbLeave(Game *game) {};

    /// Callback whenever the window loses focus or user presses a button. Needed to be described by inheritors.
    virtual void cbPause(Game *game) {};

    /// Callback used for setting up the GUI, always gets called before `cbEnter`. Needed to be described by inheritors.
    virtual void cbGUI(Game *game) {};

    // This is just a fancy, totally unnecessary ctor
    // But it is used to make instantiating UI elements look standard.
    template<class T, class ...Args>
    T createElement(Args... args) {
        return T(args...);
    }

    /// Registers the element to the GUI manager.
    void registerElement(GUI_Element *element);

};
