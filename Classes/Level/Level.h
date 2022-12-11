#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Storage/tinyxml/tinyxml2.h"

//считывает xml карту

// В картах TMX объект - это область на карте, имеющая имя, тип,
//  границы, набор пользовательских свойств (в формате ключ-значение)
//  и текстурные координаты.
// Текстурные координаты позволяют связать с объектом спрайт,
//  использующий основную текстуру карты как источник данных.
struct Object {
    int GetPropertyInt(const std::string &propertyName);
    float GetPropertyFloat(const std::string &propertyName);
    std::string GetPropertyString(const std::string &propertyName);

    void MoveBy(const sf::Vector2f &movement);
    void MoveTo(const sf::Vector2f &position);

    std::string name;
    std::string type;
    sf::FloatRect rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

// В картах TMX слой - это набор тайлов (спрайтов),
//  из которых складывается ландшафт карты.
struct Layer {
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles;
};

class Level {
public:
    // Загружает данные из TMX в память объекта.
    bool LoadFromFile(const std::string &filepath);

    Object GetFirstObject(const std::string &name) const;
    std::vector<Object> GetAllObjects(const std::string &name) const;
    sf::Vector2i GetTileSize() const;
    float GetTilemapWidth() const;
    float GetTilemapHeight() const;
    sf::Vector2f GetTilemapSize() const;

    // Рисует все слои тайлов один за другим,
    //  но не рисует объекты (рисованием которых должна заниматься игра).
    void Draw(sf::RenderTarget & window) const;

private:
    int m_width = 0;
    int m_height = 0;
    int m_tileWidth = 0;
    int m_tileHeight = 0;
    int m_firstTileID = 0;
    sf::Texture m_tilesetImage;
    std::vector<Object> m_objects;
    std::vector<Layer> m_layers;
};