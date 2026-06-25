#pragma once

#include <ostream>

template <typename T>
class Point
{
    T x, y;
public:
    explicit Point(T x = 0,  T y = 0);
    Point(const Point &p);

    [[nodiscard]] T getX() const;
    [[nodiscard]] T getY() const;

    friend std::ostream& operator<<(std::ostream &out, const Point<T> &p);
    Point<T>& operator=(const Point<T> &p);
};