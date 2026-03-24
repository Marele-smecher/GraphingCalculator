#pragma once

#include <ostream>

class Point
{
    double x, y;
public:
    explicit Point(double x = 0,  double y = 0);

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;

    friend std::ostream& operator<<(std::ostream &out, const Point &p);
};