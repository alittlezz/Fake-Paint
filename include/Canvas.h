#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>

#include <Brush.h>
#include <Button.h>
#include <Geometry.h>

#include <stack>
#include <vector>

class Canvas{
    public:
        Canvas(const int &_width, const int &_height, const int &_widthPixels, const int &_heightPixels);
        ~Canvas();

        void draw       (sf::RenderWindow &window) const;
        void drawCurrent(sf::RenderWindow &window) const;

        void addCorner(const Geom::Point &newPoint);
        void setPixel (const Geom::Point &pixel, const sf::Color &newColor);
        void addPixel (const Geom::Point &newPoint, const sf::Color &newColor);
        void addPixels(const Geom::Point &newPoint, const sf::Color &newColor);

        void clearScreen           ();
        void deleteLastMove        ();
        void eraseCurrentMove      ();
        void finishCurrentMove     ();
        void finishCurrentCircle   ();
        void finishCurrentRectangle();

        int       getWidth      () const;
        int       getHeight     () const;
        bool      getBrushState () const;
        sf::Color getColor      (const Geom::Point &mouse) const;

        void setBrush       (Brush *_brush);
        void switchFill     ();
        void turnBrushOn    ();
        void turnBrushOff   ();

        sf::CircleShape    getCircle   (const Geom::Point &A, const Geom::Point &B) const;
        sf::RectangleShape getRectangle(const Geom::Point &A, const Geom::Point &B) const;

        bool        isInbounds (const Geom::Point &point) const;
        bool        isInbounds (const int &x, const int &y) const;
        bool        isInbounds (const std::pair <double, double> &pixel) const;
    private:
        int    width, height;
        int    widthPixels, heightPixels;
        double delimiterWidth, delimiterHeight;

        sf::RenderWindow *window;

        Brush *brush;
        bool isFillOn = true;
        bool isBrushOn = false;

        std::vector <Geom::Point> currentMove;
        std::vector <sf::CircleShape> circles;
        std::vector <sf::RectangleShape> rectangles;
        std::vector <int> lastShape;
        std::vector <std::pair<std::vector <Geom::Point >, Brush>> moves;
};

#endif // CANVAS_H
