#include "SecondaryColorPalette.h"

#include <math.h>

SecondaryColorPalette::SecondaryColorPalette(const double &x, const double &y, const double &width, const double &height){
    sf::Color invisible = sf::Color::White;
    invisible.a = 0;
    slider = new Slider(x, y, width, height, invisible, sf::Color::Red, false);

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(invisible);
    box.setOutlineThickness(1);

    changeColor(sf::Color::Red);
}

SecondaryColorPalette::~SecondaryColorPalette(){
    delete slider;
}

void SecondaryColorPalette::draw(sf::RenderWindow &window) const{
    for(auto &vect : secondaryColors){
        for(auto &rect : vect){
            window.draw(rect);
        }
    }
    window.draw(box);
    slider->draw(window);
}

void SecondaryColorPalette::changeColor(const sf::Color &newColor){
    if(newColor == primaryColor){
        return;
    }
    primaryColor = newColor;
    box.setOutlineColor(primaryColor);
    secondaryColors.clear();

    Geom::Point3D leftPoint(255, 255, 255);
    Geom::Point3D leftRatio = (leftPoint * -1) / STEPS;
    Geom::Point3D rightPoint(newColor);
    Geom::Point3D rightRatio = (rightPoint * -1) / STEPS;
    for(int i = 0;i <= STEPS;i++){
        Geom::Point3D currentPoint = leftPoint;
        Geom::Point3D currentRatio = (rightPoint - leftPoint) / STEPS;
        std::vector < sf::RectangleShape > aux;
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(slider->getSize().getX() / STEPS, slider->getSize().getY() / STEPS));
        for(int j = 0;j <= STEPS;j++){
            rect.setPosition(sf::Vector2f(slider->getPosition().getX() + (double)j * slider->getSize().getX() / STEPS, slider->getPosition().getY() + (double) i * slider->getSize().getY() / STEPS));
            rect.setFillColor(sf::Color(currentPoint.getX(), currentPoint.getY(), currentPoint.getZ()));
            aux.push_back(rect);
            currentPoint = currentPoint + currentRatio;
        }
        secondaryColors.push_back(aux);
        leftPoint = leftPoint + leftRatio;
        rightPoint = rightPoint + rightRatio;
    }
    changeColor();
}

void SecondaryColorPalette::changeColor(){
    Geom::Point percentage = slider->getRatio();
    int x = percentage.getY() * (secondaryColors.size() - 1);
    int y = percentage.getX() * (secondaryColors[x].size() - 1);
    slider->setColor(secondaryColors[x][y].getFillColor());
}

sf::Color SecondaryColorPalette::getColor() const{
    return slider->getColor();
}
