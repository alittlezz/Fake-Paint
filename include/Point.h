#ifndef POINT_H
#define POINT_H

#include <SFML/Graphics.hpp>

namespace Geom{

class Point{
    public:
        Point();
        Point(const double &val);
        Point(const sf::Vector2f &point);
        Point(const sf::Vector2i &point);
        Point(const sf::Vector2u &point);

        Point(const std::pair < double, double > &point);
        Point(const double &_x, const double &_y);

        void setX (const double &_x);
        void setY (const double &_y);
        void toInt();

        double       getX() const;
        double       getY() const;
        sf::Vector2f getVector2f() const;

        Point operator + (const Point &point) const;
        Point operator - (const Point &point) const;
        Point operator * (const Point &point) const;
        Point operator / (const Point &point) const;

        Point operator + (const double &val) const;
        Point operator - (const double &val) const;
        Point operator * (const double &val) const;
        Point operator / (const double &val) const;

        bool operator == (const Point &point) const;
        bool operator != (const Point &point) const;
    private:
        double x, y;
};

}

#endif // POINT_H
