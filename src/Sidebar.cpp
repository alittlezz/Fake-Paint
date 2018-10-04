#include "Sidebar.h"

#include <map>
#include <string>
#include <Resources.h>
#include <Checkbox.h>

Sidebar::Sidebar(const int &_x, const int &_y, const int &_width, const int &_height){
    x = _x;
    y = _y;
    width = _width;
    height = _height;

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    sf::Color background = sf::Color(192, 192, 192);
    box.setFillColor(background);

    addButton(new Button(  x + width / 10, y + 0.1 * height / 5, Resources::resourceManager.getTexture("brush.png") , Types::drawPixel, sf::Vector2f(64.0 / 512.0, 64.0 / 512.0)));
    addButton(new Button(  x + width / 10, y + 1 * height / 5, Resources::resourceManager.getTexture("eraser.png") , Types::eraser, sf::Vector2f(64.0 / 512.0, 64.0 / 512.0)));
    addButton(new Button(  x + width / 10, y + 2 * height / 5, Resources::resourceManager.getTexture("circle.png") , Types::drawCircle, sf::Vector2f(64.0 / 2000.0, 64.0 / 2000.0)));
    addButton(new Button(  x + width / 10, y + 3 * height / 5, Resources::resourceManager.getTexture("rectangle.png") , Types::drawRectangle, sf::Vector2f(64.0 / 600.0, 64.0 / 222.0)));
    addButton(new Button(  x + width / 10, y + 3.75 * height / 5, Resources::resourceManager.getTexture("colorPicker.png"), Types::pickColor, sf::Vector2f(64.0 / 300.0, 64.0 / 300.0)));
    addButton(new Checkbox(x + width / 10, y + 4.5 * height / 5, Types::switchFill, "Umplere", 64.0 / 128.0));
}

void Sidebar::draw(sf::RenderWindow &window) const{
    window.draw(box);
    for(auto button : buttons){
        button->draw(window);
    }
}

void Sidebar::addButton(Button *button){
    buttons.push_back(button);
}

int Sidebar::getWidth() const{
    return width;
}

int Sidebar::getHeight() const{
    return height;
}

Types Sidebar::handleEvents(const Geom::Point &mouse){
    for(auto &button : buttons){
        if(button->isInbounds(mouse) == true){
            if(button->getType() == Types::switchFill){
                static_cast <Checkbox*>(button)->switchFill();
            }
            return button->getType();
        }
    }
    return Types::DEFAULT_ACTION;
}

bool Sidebar::isInbounds(const Geom::Point &point) const{
    return Geom::Rectangle(box).isInbounds(point);
}
