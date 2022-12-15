#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class GameObject : public sf::Transformable, public sf::Drawable {

    float width;
    float height;

public:
    GameObject() = default;

    /// Checks if current Objects collides with gameObject variable or not.
    bool collidesWith(GameObject *gameObject);

    /// Sets object's height.
    void setHeight(float height);

    /// Sets object's width.
    void setWidth(float width);

    //Gets object's height.
    float getHeight() const;

    //Gets object's width.
    float getWidth() const;
};
