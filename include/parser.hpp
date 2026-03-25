#pragma once

#include <string>   

class Parser
{
    std::string expression;
    double parseTerm(size_t &i, double x);
    double parseFactor(size_t &i, double x);
public:
    Parser() = default;
    explicit Parser(std::string s);

    double parseExpression(size_t &i, double x);
    double evaluate(double x);
    void setExpression(const std::string &s);
    [[nodiscard]]  std::string getExpression() const;
    // static bool valid(const std::string &s);

    Parser& operator=(const Parser &p);
};
