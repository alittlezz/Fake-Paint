#include "PrimaryColorPalette.h"

#include <math.h>

PrimaryColorPalette::PrimaryColorPalette(const double &x, const double &y, const double &width, const double &height){
    Geom::Point3D currentPoint(255, 0, 0);
    std::vector <Geom::Point3D> direction = {Geom::Point3D(0, 1, 0), Geom::Point3D(-1, 0, 0), Geom::Point3D(0, 0, 1), Geom::Point3D(0, -1, 0), Geom::Point3D(1, 0, 0), Geom::Point3D(0, 0, -1)};
    double lineWidth = (double) width / (direction.size() * 255 / STEPS);
    for(int i = 0;i < direction.size();i++){
        for(int j = 0;j < 255 / STEPS;j++){
            sf::RectangleShape rect;
            rect.setFillColor(sf::Color(currentPoint.getX(), currentPoint.getY(), currentPoint.getZ()));
            rect.setPosition(sf::Vector2f(x + (double)(i * (255 / STEPS) + j) * lineWidth, y));
            rect.setSize(sf::Vector2f(lineWidth , height));
            primaryColors.push_back(rect);
            currentPoint = currentPoint + (direction[i] * STEPS);
        }
        currentPoint = currentPoint - (direction[i] * STEPS);
    }

    sf::Color invisible = sf::Color::White;
    invisible.a = 0;
    slider = new Slider(x, y, width, height, invisible, sf::Color::Red, true);
}

PrimaryColorPalette::~PrimaryColorPalette(){
    delete slider;
}

void PrimaryColorPalette::draw(sf::RenderWindow &window) const{
    for(auto &rect : primaryColors){
        window.draw(rect);
    }
    slider->draw(window);
}

sf::Color PrimaryColorPalette::getColor() const{
    return slider->getColor();
}

void PrimaryColorPalette::changeColor(){
    double percentage = slider->getRatio().getX();
    slider->setColor(primaryColors[percentage * (primaryColors.size() - 1)].getFillColor());
}
