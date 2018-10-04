#include <Point.h>

#include <iostream>

namespace Geom{

Point::Point(){
    x = y = 0;
}

Point::Point(const double &val){
    x = val;
    y = val;
}

Point::Point(const sf::Vector2f &point){
    x = point.x;
    y = point.y;
}

Point::Point(const sf::Vector2i &point){
    x = point.x;
    y = point.y;
}

Point::Point(const sf::Vector2u &point){
    x = point.x;
    y = point.y;
}

Point::Point(const std::pair < double, double > &point){
    x = point.first;
    y = point.second;
}

Point::Point(const double &_x, const double &_y){
    x = _x;
    y = _y;
}

void Point::setX(const double &_x){
    x = _x;
}

void Point::setY(const double &_y){
    y = _y;
}

void Point::toInt(){
    x = (int)x;
    y = (int)y;
}

double Point::getX() const{
    return x;
}

double Point::getY() const{
    return y;
}

sf::Vector2f Point::getVector2f() const{
    return sf::Vector2f(x, y);
}

Point Point::operator + (const Point &point) const{
    return {this->x + point.getX(), this->y + point.getY()};
}

Point Point::operator - (const Point &point) const{
    return {this->x - point.getX(), this->y - point.getY()};
}

Point Point::operator * (const Point &point) const{
    return {this->x * point.getX(), this->y * point.getY()};
}

Point Point::operator / (const Point &point) const{
    if(point.getX() == 0 || point.getY() == 0){
        std::cout << "Can't divide by 0!";
        exit(0);
    }
    return {this->x / point.getX(), this->y / point.getY()};
}

Point Point::operator + (const double &val) const{
    return {this->x + val, this->y + val};
}

Point Point::operator - (const double &val) const{
    return {this->x - val, this->y - val};
}

Point Point::operator * (const double &val) const{
    return {this->x * val, this->y * val};
}

Point Point::operator / (const double &val) const{
    if(val == 0){
        std::cout << "Can't divide by 0!";
        exit(0);
    }
    return {this->x / val, this->y / val};
}


bool Point::operator == (const Point &point) const{
    return this->x == point.getX() && this->y == point.getY();
}

bool Point::operator != (const Point &point) const{
    return !((*this) == point);
}


}
