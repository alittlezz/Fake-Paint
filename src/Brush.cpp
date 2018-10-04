#include "Brush.h"

Brush::Brush(const sf::Color &_color, const Types &_type, const int &_size){
    color = _color;
    type = _type;
    size = _size;
}

sf::Color Brush::getColor() const{
    return color;
}

Types Brush::getType() const{
    return type;
}

int Brush::getSize() const{
    return size;
}

void Brush::setColor(const sf::Color &_color){
    color = _color;
}

void Brush::setType(const Types &_type){
    type = _type;
}

void Brush::setSize(const int &_size){
    size = _size;
}
