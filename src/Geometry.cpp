#include <Geometry.h>
#include <math.h>

namespace Geom{
    double distance(const Point &A, const Point &B){
        double xSquare = (A.getX() - B.getX()) * (A.getX() - B.getX());
        double ySquare = (A.getY() - B.getY()) * (A.getY() - B.getY());
        return sqrt(xSquare + ySquare);
    }

    double distance(const Point &A, const Line &line){
        return std::fabs(line.getValue(A)) / std::sqrt(line.getA() * line.getA() + line.getB() * line.getB());
    }

    bool inCircle(const Point &A, const sf::CircleShape &circle){
        return distance(A, Point(circle.getPosition()) + Point(circle.getRadius())) <= circle.getRadius();
    }

    bool inCircleOutline(const Point &A, const sf::CircleShape &circle){
        double dist = distance(A, Point(circle.getPosition()) + Point(circle.getRadius()));
        return circle.getRadius() <= dist && dist <= circle.getRadius() + circle.getOutlineThickness();
    }

    bool inRectangle(const Point &A, const sf::RectangleShape &rectangle){
        Point upperLeft = Point(rectangle.getPosition());
        Point lowerRight = Point(rectangle.getPosition()) + Point(rectangle.getSize());
        return upperLeft.getX() <= A.getX() && A.getX() <= lowerRight.getX() &&
               upperLeft.getY() <= A.getY() && A.getY() <= lowerRight.getY();
    }

    bool inRectangleOutline(const Point &A, const sf::RectangleShape &rectangle){
        Point upperLeft = Point(rectangle.getPosition()) - Point(rectangle.getOutlineThickness());
        Point lowerRight = Point(rectangle.getPosition()) + Point(rectangle.getSize()) + Point(rectangle.getOutlineThickness());
        return inRectangle(A, rectangle) == false &&
               upperLeft.getX() <= A.getX() && A.getX() <= lowerRight.getX() &&
               upperLeft.getY() <= A.getY() && A.getY() <= lowerRight.getY();
    }
}
