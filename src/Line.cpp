#include "Line.h"

namespace Geom{

Line::Line(const sf::Vector2f &A, const sf::Vector2f &B){
	a = A.y - B.y;
	b = B.x - A.x;
	c = A.x * B.y - A.y * B.x;
}

Line::Line(const sf::Vector2i &A, const sf::Vector2i &B){
	a = A.y - B.y;
	b = B.x - A.x;
	c = A.x * B.y - A.y * B.x;
}

Line::Line(const sf::Vector2u &A, const sf::Vector2u &B){
	a = A.y - B.y;
	b = B.x - A.x;
	c = A.x * B.y - A.y * B.x;
}

Line::Line(const double &_a, const double &_b, const double &_c){
	a = _a;
	b = _b;
	c = _c;
}

Line::Line(const double &x1, const double &y1, const double &x2, const double &y2){
	a = y1 - y2;
	b = x2 - x1;
	c = x1 * y2 - x2 * y1;
}

Line::Line(const std::pair <double, double> &A, const std::pair <double, double> &B){
	a = A.second - B.second;
	b = B.first - A.first;
	c = A.first * B.second - A.second * B.first;
}

Line::Line(const Point &A, const Point &B){
    a = A.getY() - B.getY();
    b = B.getX() - A.getX();
    c = A.getX() * B.getY() - A.getY() * B.getX();
}

double Line::getA() const{
	return a;
}

double Line::getB() const{
	return b;
}

double Line::getC() const{
	return c;
}

double Line::getValue(const Point &point) const{
    return a * point.getX() + b * point.getY() + c;
}

bool Line::contains(const Point &point) const{
    return getValue(point) == 0;
}

}
