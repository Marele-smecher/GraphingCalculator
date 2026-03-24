#pragma once

#include <ostream>

class Point
{
    double x, y;
public:
    Point(double x = 0,  double y = 0);

    double getX() const;
    double getY() const;

    friend std::ostream& operator<<(std::ostream &out, const Point &p);
};