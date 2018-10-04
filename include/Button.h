#ifndef Button_H
#define Button_H

#include <SFML/Graphics.hpp>

#include <Geometry.h>

enum Types{
    pickColor,
    eraser,
    drawPixel,
    drawCircle,
    drawRectangle,
    switchFill,
    clearScreen,
    copyColor,
    activatedSlider,
    DEFAULT_ACTION
};

class Button{
    public:
        Button() {};
        Button(const int &x, const int &y, const sf::Texture &iconTexture, const Types &_type, const sf::Vector2f &scale = sf::Vector2f(1, 1));

        Types getType() const;

        virtual void draw(sf::RenderWindow &window) const;

        bool isInbounds(const Geom::Point &point) const;
    protected:
        Types        type;
        sf::Sprite 	 icon;
};

#endif // Button_H
