#pragma once

#include "point.hpp"
#include "parser.hpp"
#include <vector>

class Function
{
    Parser parser;
    int pointCount;
    std::vector<Point>  points;
    std::string expressionName;
public:
    Function() = default;
    Function(const std::string&, int);
    Function(const Function&);

    void clearPoints();
    void generatePoints(double minX, double maxX, double step);

    friend std::ostream& operator<<(std::ostream&, Function);
    Function& operator=(const Function&);

    ~Function() = default;
};