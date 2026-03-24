#include <parser.hpp>

Parser::Parser(const std::string &s) : expression(s)
{}

double Parser::evaluate(double x)
{
    x = x + 1;
    return 0;
}

void Parser::setExpression(const std::string &s)
{
    expression = s;
}
