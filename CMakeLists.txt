cmake_minimum_required(VERSION 3.23)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES startup.cpp
        Classes/Game/Game.cpp
        Classes/FPS/FPS.cpp
        Classes/MainMenu/MainMenu.cpp
        Classes/MenuOption/MenuOption.cpp
        Classes/LevelMenu/LevelMenu.cpp
        Classes/MainGame/MainGame.cpp
        Classes/Level/Level.cpp
        Classes/Animation/Animation.cpp
        Classes/AnimationManager/AnimationManager.cpp
        Classes/DynamicEntity/Entity.cpp
        Classes/Enemy/Enemy.cpp
        Classes/Projectile/Projectile.cpp
        Storage/tinyxml/tinyxml2.cpp
        Classes/Wallet/Wallet.cpp
        Classes/Wave/Wave.cpp
        Classes/Wave/Wave.h
        Classes/Tower/Tower.cpp
        Classes/Tower/Tower.h
        Classes/Weapon/Weapon.cpp
        Classes/Weapon/Weapon.h
        Classes/HydroTower/HydroTower.cpp
        Classes/HydroTower/HydroTower.h
        Classes/HydroTrap/HydroTrap.cpp
        Classes/HydroTrap/HydroTrap.h
        Classes/PyroTower/PyroTower.cpp
        Classes/PyroTower/PyroTower.h
        Classes/PyroTrap/PyroTrap.cpp
        Classes/PyroTrap/PyroTrap.h
        Classes/Trap/Trap.cpp
        Classes/Trap/Trap.h Classes/Vector/Vector.cpp Classes/Vector/Vector.h Classes/GUI/SceneManager.cpp Classes/GUI/SceneManager.h Classes/GUI/EventManager.cpp Classes/GUI/EventManager.h Classes/GUI/EventBag.cpp Classes/GUI/EventBag.h Classes/GUI/GUI_Manager.cpp Classes/GUI/GUI_Manager.h Classes/GUI/Scene.cpp Classes/GUI/Scene.h Classes/GUI/GUI_Element.cpp Classes/GUI/GUI_Element.h Classes/GUI/ShopElement.cpp Classes/GUI/ShopElement.h Classes/GUI/cantBeDrawnException.h Classes/GUI/noSceneSetException.h Classes/GameLogic/MainGame.cpp Classes/GameLogic/MainGame.h Classes/GameLogic/GameObject.cpp Classes/GameLogic/GameObject.h Classes/GameLogic/Wave.cpp Classes/GameLogic/Wave.h Classes/GameLogic/WaveManager.cpp Classes/GameLogic/WaveManager.h Classes/GameLogic/Tower.cpp Classes/GameLogic/Tower.h Classes/GameLogic/TowerManager.cpp Classes/GameLogic/TowerManager.h Classes/GameLogic/TowerType.h Classes/GameLogic/ITower.cpp Classes/GameLogic/ITower.h Classes/GameLogic/Enemy.cpp Classes/GameLogic/Enemy.h Classes/GameLogic/EnemyManager.cpp Classes/GameLogic/EnemyManager.h Classes/GameLogic/EnemyType.h)


#сделать проверку на добавление нужной библиотеки
set(SFML_DIR C:/SFML)
set(SFML_ROOT ${SFML_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR} Storage)
add_executable(lab4 ${SOURCE_FILES})
target_link_libraries(lab4 ${SFML_LIBRARIES})

#перед запуском проекта надо скопировать все .dll файлы из c:/SFML/bin в cmake-build-debug
#сделать это в cmake

#создать папку cmake-modules, куда кинуть скрипт FindSFML.cmake