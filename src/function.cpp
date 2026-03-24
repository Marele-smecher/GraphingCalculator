#include <function.hpp>

Function::Function(const std::string &s, int x) : pointCount(x),  expressionName(s) 
{}

/*
Function::Function(const Function &F) 
{
    
}*/

void Function::clearPoints()
{
    pointCount = 0;
    points.clear();
}


