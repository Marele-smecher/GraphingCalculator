#pragma once

#include <string>   

class Parser
{
    std::string expression;
public:
    Parser() = default;
    Parser(const std::string &s);

    double evaluate(double x);
    void setExpression(const std::string &s);

};