#include "point.hpp"

Point::Point(double x, double y) : x(x), y(y) 
{}

Point::Point(const Point &p) :
    x(p.x), y(p.y)
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

Point& Point::operator=(const Point &p)
{
    if (this == &p) return *this;
    this->x = p.x; this->y = p.y;
    return *this;
}




