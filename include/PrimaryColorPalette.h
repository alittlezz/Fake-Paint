#ifndef PRIMARYCOLORPALETTE_H
#define PRIMARYCOLORPALETTE_H

#include <SFML/Graphics.hpp>

#include <Slider.h>
#include <Geometry.h>

#include <vector>

class PrimaryColorPalette{
    public:
        PrimaryColorPalette(const double &x, const double &y, const double &width, const double &height);
        ~PrimaryColorPalette();

        void draw     (sf::RenderWindow &window) const;

        sf::Color getColor   () const;

        void      changeColor();

        Slider *slider;
    private:
        std::vector < sf::RectangleShape > primaryColors;

        const double STEPS      = 1.0;
};

#endif // PRIMARYCOLORPALETTE_H
