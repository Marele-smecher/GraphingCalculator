#pragma once

#include <string>   

class Parser
{
    std::string expression;
public:
    Parser() = default;
    explicit Parser(std::string s);

    double evaluate(double x);
    void setExpression(const std::string &s);
    [[nodiscard]]  std::string getExpression() const;

    Parser& operator=(const Parser &p);
};