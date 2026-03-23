#include "point.hpp"

Point::Point(double x = 0, double y = 0) : x(x), y(y) 
{}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

std::ostream& operator<<(std::ostream &out, const Point &p)
{
    out << p.x << " " << p.y;
    return out;
}





