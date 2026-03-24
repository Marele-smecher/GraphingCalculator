#include <function.hpp>

Function::Function(const std::string &s, int x) : parser(s), pointCount(x), point(), expressionName(s) 
{
    generatePoints(-10, 10, 0.1);
}

/*
Function::Function(const Function &F) 
{
    
}*/

void Function::generatePoints(double minX, double maxX, double step)
{
    points.clear();

    for (double x = minX; x <= maxX; x += step) {
        double y = parser.evaluate(x); 
        points.push_back(Point(x, y));
    }

    pointCount = points.size();
}

void Function::clearPoints()
{
    pointCount = 0;
    points.clear();
}


