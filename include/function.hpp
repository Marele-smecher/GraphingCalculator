#pragma once

#include "point.hpp"
#include "parser.hpp"
#include <vector>

class Function
{
    Parser parser;
    std::vector<Point> points;
    std::string expressionName;
    double a;
    void clearPoints();
    void generatePoints(double minX, double maxX, double step);
public:
    Function() = default;
    explicit Function(const std::string& s, double a = 5);
    Function(const Function &F);
    // Function(const Function& F);

    [[nodiscard]] std::string getExpression() const;
    [[nodiscard]] std::vector<Point> getPoints() const;
    void setExpression(const std::string &s);

    friend std::ostream& operator<<(std::ostream& out, const Function &F);
    Function& operator=(const Function& F);

    ~Function() = default;
};