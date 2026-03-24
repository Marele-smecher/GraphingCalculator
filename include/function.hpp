#pragma once

#include "point.hpp"
#include "parser.hpp"
#include <vector>

class Function
{
    Parser parser;
    int pointCount;
    std::vector<Point> points;
    std::string expressionName;
public:
    Function() = default;
    Function(const std::string& s, int x);
    // Function(const Function& F);

    void clearPoints();
    void generatePoints(double minX, double maxX, double step);

    friend std::ostream& operator<<(std::ostream& out, const Function &F);
    Function& operator=(const Function& F);

    ~Function() = default;
};