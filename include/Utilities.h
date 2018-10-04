#ifndef UTILITIES_H
#define UTILITIES_H

#include <Geometry.h>

#include <string>
#include <vector>
#include <math.h>

namespace Utilities{
	const double PI = 3.14159265359;
	const double SQ2 = sqrt(2);
	const std::vector <Geom::Point> directions = {Geom::Point(-1, 0), Geom::Point(1, 0), Geom::Point(0, -1), Geom::Point(0, 1)};

    std::string toString(int x);
    void sleepFor(const double &x);
}

#endif // UTILITIES_H
