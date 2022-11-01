cmake_minimum_required(VERSION 3.23)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp Classes/Landscape/Landscape.h Classes/Landscape/Landscape.cpp Classes/Lain/Lain.cpp Classes/Lain/Lain.h Classes/Enemy/Enemy.cpp Classes/Enemy/Enemy.h Classes/Effect/Effect.cpp Classes/Effect/Effect.h Classes/Cell/Cell.cpp Classes/Cell/Cell.h Classes/Castle/Castle.cpp Classes/Castle/Castle.h Classes/Building/Building.cpp Classes/Building/Building.h Classes/Tower/Tower.cpp Classes/Tower/Tower.h Classes/Trap/Trap.cpp Classes/Trap/Trap.h Classes/Weapon/Weapon.cpp Classes/Weapon/Weapon.h)


#сделать проверку на добавление нужной библиотеки
set(SFML_DIR C:/SFML)
set(SFML_ROOT ${SFML_DIR})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(lab4 ${SOURCE_FILES})
target_link_libraries(lab4 ${SFML_LIBRARIES})

#перед запуском проекта надо скопировать все .dll файлы из c:/SFML/bin в cmake-build-debug
#сделать это в cmake

#создать папку cmake-modules, куда кинуть скрипт FindSFML.cmake