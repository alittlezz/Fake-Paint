#include "Button.h"

Button::Button(const int &x, const int &y, const sf::Texture &iconTexture, const Types &_type, const sf::Vector2f &scale){
    icon.setPosition(sf::Vector2f(x, y));
    icon.setTexture(iconTexture);
    icon.setScale(scale);
    type = _type;
}

void Button::draw(sf::RenderWindow &window) const{
    window.draw(icon);
}

Types Button::getType() const{
    return type;
}

bool Button::isInbounds(const Geom::Point &point) const{
	return Geom::Rectangle(icon).isInbounds(point);
}
