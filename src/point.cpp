#include "point.hpp"

template <typename T>
Point<T>::Point(T x, T y) : x(x), y(y) 
{}

template <typename T>
Point<T>::Point(const Point<T> &p) :
    x(p.x), y(p.y)
{}

template <typename T>
T Point<T>::getX() const
{
    return x;
}

template <typename T>
T Point<T>::getY() const
{
    return y;
}

template <typename T>
Point<T>& Point<T>::operator=(const Point<T> &p)
{
    if (this == &p) return *this;
    this->x = p.x; 
    this->y = p.y;
    return *this;
}

template class Point<double>;
template class Point<int>;
