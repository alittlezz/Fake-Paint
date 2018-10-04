#ifndef SECONDARYCOLORPALETTE_H
#define SECONDARYCOLORPALETTE_H

#include <SFML/Graphics.hpp>

#include <Slider.h>
#include <Geometry.h>

#include <vector>

class SecondaryColorPalette{
    public:
        SecondaryColorPalette(const double &x, const double &y, const double &width, const double &height);
        ~SecondaryColorPalette();

        void draw       (sf::RenderWindow &window) const;

        void changeColor();
        void changeColor(const sf::Color &newColor);

        sf::Color getColor() const;

        Slider *slider;
    private:
        sf::Color          primaryColor = sf::Color::White;
        sf::RectangleShape box;

        std::vector < std::vector < sf::RectangleShape > > secondaryColors;

        const double STEPS      = 50.0;
};

#endif // SECONDARYCOLORPALETTE_H
