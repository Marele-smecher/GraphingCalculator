#pragma once

#include <ostream>

class Point
{
    double x, y;
public:
    Point(double x,  double y);

    double getX() const;
    double getY() const;

    friend std::ostream& operator<<(std::ostream &out, const Point &p);
};