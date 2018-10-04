#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Point.h>

namespace Geom{

class Rectangle{
    public:
        Rectangle(const Point &_A, const Point &_B);
        Rectangle(const sf::RectangleShape &rect);
        Rectangle(const sf::Sprite &sprite);

        Point getA() const;
        Point getB() const;

        double getWidth() const;
        double getHeight() const;

        bool isInbounds(const Point &point) const;
    private:
        Point A, B;
};

}

#endif // RECTANGLE_H
