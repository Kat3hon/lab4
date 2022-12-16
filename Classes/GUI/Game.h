#pragma once

#include "../baseHeaders.h"

#include "SceneManager.h"
#include "EventManager.h"
#define DELTA_TICKS 60

class Game: sf::NonCopyable {

    /// Main window of GUI
    sf::RenderWindow window;

    /// Handler for various scenes, needed to draw and update them
    SceneManager scene_manager;

    /// Handler for various events, needed to process them in right order and their function
    EventManager event_manager;

    /// Some cosmetic for the main game
    sf::Image icon;
    sf::Music music;

public:

    /// Sets the game icon, font, music, scene, frame limit
    Game();

    ~Game() = default;

    /// Returns the game main window
    sf::RenderWindow *getWindow();

    /// Returns the game scene_manager
    SceneManager *getSceneManager();

    /// Starts the main loop of the game
    void run();

    ///Quits the game and the main window
    void exit();


};