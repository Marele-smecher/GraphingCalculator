#include <function.hpp>
#include <iostream>

Function::Function(const std::string &s, double a) : parser(s), points(), expressionName(s), a(a)
{
    generatePoints(-a, a, 0.01);
}

Function::Function(const Function &F) 
    : parser(F.parser), 
      points(F.points), 
      expressionName(F.expressionName), 
      a(F.a)
{
}

void Function::clearPoints()
{
    points.clear();
}

std::vector<Point> Function::getPoints() const
{
    return points;
}

Function& Function::operator=(const Function &f)
{
    if (this != &f) {
        this->expressionName = f.expressionName;
        this->parser = f.parser;
        this->points = f.points;
    }
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Function &F)
{
    out << "Function: " << F.parser << "\nPoints:\n";
    for (const auto& p : F.points) {
        out << p << "\n"; 
    }
    return out;
}

void Function::generatePoints(double minX, double maxX, double step)
{
    points.clear();

    const int numSteps = static_cast<int>((maxX - minX) / step) + 1;

    for (int i = 0; i < numSteps; ++i) {
        double x = minX + i * step;         
        double y = parser.evaluate(x);
        points.emplace_back(Point(x, y));  
    }
}

Function::~Function()
{
    std::cout << "Destructing function with expression: " << expressionName << "\n";
}


