//
// Created by kklim on 02.11.2022.
//

#pragma once
#include "..\Base\Base.h"

struct Vertex {
    sf::Time lifeTime;
    sf::Vector2f velocity;

    static sf::Vector2f getRandomVelocity();

    void slowVelocity();
};

class ParticleMenu:public sf::Drawable, public sf::Transformable {
private:
    const int bVertexesCount = 700;
    sf::VertexArray backgroundVertexes;
    std::vector <Vertex> bckgVertexes;

    const int cVertexesCount = 1200;
    sf::VertexArray cursorVertexes;
    std::vector <Vertex> crsVertexes;


public:
    ParticleMenu();
    ~ParticleMenu();

    void resetBackgroundParticle(int index);
    void resetCursorParticle(int index);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void update();
};
