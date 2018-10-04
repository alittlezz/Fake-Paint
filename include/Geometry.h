#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <SFML/Graphics.hpp>

#include <line.h>
#include <Point.h>
#include <Point3D.h>
#include <Rectangle.h>

namespace Geom{
    double distance(const Point &A, const Point &B);
    double distance(const Point &A, const Line &line);
    bool inCircle(const Point &A, const sf::CircleShape &circle);
    bool inCircleOutline(const Point &A, const sf::CircleShape &circle);
    bool inRectangle(const Point &A, const sf::RectangleShape &rectangle);
    bool inRectangleOutline(const Point &A, const sf::RectangleShape &rectangle);
};

#endif // GEOMETRY_H
