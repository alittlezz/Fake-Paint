#include "PreviewScreen.h"

PreviewScreen::PreviewScreen(double x, double y, double width, double height, const sf::Color &color){
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(width, height));
    rect.setFillColor(color);
}

void PreviewScreen::draw(sf::RenderWindow &window) const{
    window.draw(rect);
}

void PreviewScreen::changeColor(const sf::Color &newColor){
    rect.setFillColor(newColor);
}
