#include <Point3D.h>

#include <iostream>

namespace Geom{

Point3D::Point3D(){
    x = y = z = 0;
}

Point3D::Point3D(const double &val){
    x = val;
    y = val;
    z = val;
}

Point3D::Point3D(const sf::Color &color){
	x = color.r;
	y = color.g;
	z = color.b;
}

Point3D::Point3D(const sf::Vector3f &point){
    x = point.x;
    y = point.y;
    z = point.z;
}

Point3D::Point3D(const sf::Vector3i &point){
    x = point.x;
    y = point.y;
    z = point.z;
}

Point3D::Point3D(const double &_x, const double &_y, const double &_z){
    x = _x;
    y = _y;
    z = _z;
}

void Point3D::setX(const double &_x){
    x = _x;
}

void Point3D::setY(const double &_y){
    y = _y;
}

void Point3D::setZ(const double &_z){
	z = _z;
}

double Point3D::getX() const{
    return x;
}

double Point3D::getY() const{
    return y;
}

double Point3D::getZ() const{
	return z;
}

Point3D Point3D::operator + (const Point3D &point) const{
    return {this->x + point.getX(), this->y + point.getY(), this->z + point.getZ()};
}

Point3D Point3D::operator - (const Point3D &point) const{
    return {this->x - point.getX(), this->y - point.getY(), this->z - point.getZ()};
}

Point3D Point3D::operator * (const Point3D &point) const{
    return {this->x * point.getX(), this->y * point.getY(), this->z * point.getZ()};
}

Point3D Point3D::operator / (const Point3D &point) const{
    if(point.getX() == 0 || point.getY() == 0 || point.getZ() == 0){
        std::cout << "Can't divide by 0!";
        exit(0);
    }
    return {this->x / point.getX(), this->y / point.getY(), this->z  / point.getZ()};
}

Point3D Point3D::operator + (const double &val) const{
    return {this->x + val, this->y + val, this->z + val};
}

Point3D Point3D::operator - (const double &val) const{
    return {this->x - val, this->y - val, this->z - val};
}

Point3D Point3D::operator * (const double &val) const{
    return {this->x * val, this->y * val, this->z * val};
}

Point3D Point3D::operator / (const double &val) const{
    if(val == 0){
        std::cout << "Can't divide by 0!";
        exit(0);
    }
    return {this->x / val, this->y / val, this->z / val};
}


bool Point3D::operator == (const Point3D &point) const{
    return this->x == point.getX() && this->y == point.getY() && this->z == point.getZ();
}

bool Point3D::operator != (const Point3D &point) const{
    return !((*this) == point);
}


}
