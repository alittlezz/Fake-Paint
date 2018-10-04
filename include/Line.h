#ifndef LINE_H
#define LINE_H

#include <Point.h>

namespace Geom{

class Line{
    public:
        Line(){};
        Line(const sf::Vector2f &A, const sf::Vector2f &B);
        Line(const sf::Vector2i &A, const sf::Vector2i &B);
        Line(const sf::Vector2u &A, const sf::Vector2u &B);

        Line(const double &_a, const double &_b, const double &_c);
        Line(const double &x1, const double &y1, const double &x2, const double &y2);
        Line(const std::pair <double, double> &A, const std::pair <double, double> &B);
        Line(const Point &A, const Point &B);

        double getA    () const;
        double getB    () const;
        double getC    () const;

        bool   contains(const Point &A) const;
        double getValue(const Point &A) const;
    private:
        double a, b, c;
};

}

#endif // LINE_H
