#ifndef POINT3D_H
#define POINT3D_H

#include <SFML/Graphics.hpp>

namespace Geom{

class Point3D{
    public:
        Point3D();
        Point3D(const double &val);
        Point3D(const sf::Color &color);
        Point3D(const sf::Vector3f &point);
        Point3D(const sf::Vector3i &point);
        Point3D(const double &_x, const double &_y, const double &_z);

        void setX(const double &_x);
        void setY(const double &_y);
        void setZ(const double &_z);

        double getX() const;
        double getY() const;
        double getZ() const;

        Point3D operator + (const Point3D &point) const;
        Point3D operator - (const Point3D &point) const;
        Point3D operator * (const Point3D &point) const;
        Point3D operator / (const Point3D &point) const;

        Point3D operator + (const double &val) const;
        Point3D operator - (const double &val) const;
        Point3D operator * (const double &val) const;
        Point3D operator / (const double &val) const;

        bool operator == (const Point3D &point) const;
        bool operator != (const Point3D &point) const;
    private:
        double x, y, z;
};

}

#endif // POINT3D_H
