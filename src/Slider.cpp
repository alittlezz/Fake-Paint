#include "Slider.h"
#include <Utilities.h>
#include <Resources.h>

Slider::Slider(const int &x, const int &y, const int &width, const int &height, const sf::Color &boxColor, const sf::Color &circleColor, const bool &_isOrizontal, const bool &haveText){
    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(boxColor);

    circle.setFillColor(circleColor);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1);
    circle.setRadius(std::min(15.0, height * 0.75));
    circle.setPosition(sf::Vector2f(x - circle.getRadius(), y + height / 2 - circle.getRadius()));

    if(haveText == true){
        text = new sf::Text();
        text->setString("1");
        text->setPosition(sf::Vector2f(x + width / 2 - 15, y + height));
        text->setFont(Resources::resourceManager.getFont("arial.ttf"));
        text->setCharacterSize(25);
        text->setFillColor(sf::Color::Black);
    }
    isOrizontal = _isOrizontal;
}

void Slider::switchState(){
    isOn = !isOn;
}

void Slider::turnOn(){
    isOn = true;
}

void Slider::turnOff(){
    isOn = false;
}

void Slider::setColor(const sf::Color &color){
    circle.setFillColor(color);
}

bool Slider::isInbounds(const Geom::Point &point) const{
    return Geom::distance(Geom::Point(circle.getPosition()) + Geom::Point(circle.getRadius()), point) <= circle.getRadius();
}

bool Slider::getState() const{
    return isOn;
}

Geom::Point Slider::getPosition() const{
    return Geom::Point(box.getPosition());
}

Geom::Point Slider::getSize() const{
    return Geom::Point(box.getSize());
}

Geom::Point Slider::getRatio() const{
    return (Geom::Point(circle.getPosition()) + Geom::Point(circle.getRadius()) - Geom::Point(box.getPosition())) / Geom::Point(box.getSize());
}

sf::Color Slider::getColor() const{
    return circle.getFillColor();
}

void Slider::draw(sf::RenderWindow &window) const{
    window.draw(box);
    window.draw(circle);
    if(text != NULL){
        window.draw(*text);
    }
}

void Slider::update(Geom::Point mouse){
    if(mouse.getX() < box.getPosition().x){
        mouse.setX(box.getPosition().x);
    }else if(mouse.getX() > box.getPosition().x + box.getSize().x){
        mouse.setX(box.getPosition().x + box.getSize().x);
    }
    if(isOrizontal){
        mouse.setY(box.getPosition().y + box.getSize().y / 2);
    }else{
        if(mouse.getY() < box.getPosition().y){
            mouse.setY(box.getPosition().y);
        }else if(mouse.getY() > box.getPosition().y + box.getSize().y){
            mouse.setY(box.getPosition().y + box.getSize().y);
        }
    }
    circle.setPosition((mouse - Geom::Point(circle.getRadius())).getVector2f());
    if(text != NULL){
        double percentage = getRatio().getX();
        text->setString(Utilities::toString(1 + percentage * 99));
    }
}
