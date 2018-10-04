#include "Rectangle.h"

namespace Geom{

Rectangle::Rectangle(const Point &_A, const Point &_B){
    A = _A;
    B = _B;
}

Rectangle::Rectangle(const sf::RectangleShape &rect){
	A = Point(rect.getPosition());
	B = A + Point(rect.getSize());
}

Rectangle::Rectangle(const sf::Sprite &sprite){
	A = Point(sprite.getPosition());
	B = A + Point(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

Point Rectangle::getA() const{
	return A;
}

Point Rectangle::getB() const{
	return B;
}

double Rectangle::getWidth() const{
	return B.getX() - A.getX();
}

double Rectangle::getHeight() const{
	return B.getY() - A.getY();
}


bool Rectangle::isInbounds(const Point &point) const{
	return A.getX() <= point.getX() && point.getX() <= B.getX() &&
		   A.getY() <= point.getY() && point.getY() <= B.getY();
}

}
