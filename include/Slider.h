#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Graphics.hpp>

#include <Geometry.h>

class Slider{
    public:
        Slider(const int &x, const int &y, const int &width, const int &height, const sf::Color &boxColor, const sf::Color &circleColor, const bool &_isOrizontal, const bool &haveText = false);

        void update     (Geom::Point mouse);
        void turnOn     ();
        void turnOff    ();
        void setColor   (const sf::Color &color);
        void switchState();

        bool        isInbounds (const Geom::Point &point) const;
        bool        getState   () const;
        sf::Color   getColor   () const;
        Geom::Point getPosition() const;
        Geom::Point getSize    () const;
        Geom::Point getRatio   () const;

        void draw  (sf::RenderWindow &window) const;

    private:
        sf::CircleShape circle;
        sf::RectangleShape box;
        sf::Text *text = NULL;
        bool isOrizontal;
        bool isOn = false;
};

#endif // SLIDER_H
