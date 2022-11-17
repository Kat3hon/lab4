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
        Classes/Wallet/Wallet.cpp Classes/Wave/Wave.cpp Classes/Wave/Wave.h Classes/Tower/Tower.cpp Classes/Tower/Tower.h)


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