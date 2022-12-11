#include <functional>
#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

class GUI_Element : public sf::Transformable {

    using ClickHandler = std::function<void()>;
    using HoverHandler = std::function<void()>;

public:

    using Ptr = std::shared_ptr<GUI_Element>;

    explicit GUI_Element(sf::Vector2f vector = {0, 0});

    void bindClick(const ClickHandler &handler);

    void bindHover(const HoverHandler &handler);

    virtual void onClick();

    virtual void onHover();

    float getWidth();

    float getHeight();

    virtual void setWidth(float width);

    virtual void setHeight(float height);

    virtual void update();

private:
    GUI_Element::ClickHandler m_clickHandler;
    GUI_Element::HoverHandler m_hoverHandler;

    sf::Vector2f m_vector;
};