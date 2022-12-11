#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class GameObject : public sf::Transformable, public sf::Drawable {
public:
    GameObject();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool collidesWith(GameObject *gameObject);

    void setHeight(float height);

    void setWidth(float width);

    float getHeight();

    float getWidth();

private:
    float m_width;
    float m_height;
};
