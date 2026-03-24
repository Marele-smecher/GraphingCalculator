#include <parser.hpp>

Parser::Parser(const std::string &s) : expression(s)
{}

double Parser::evaluate(double x)
{
    return x * x;
}

std::string Parser::getExpression() const
{
    return expression;
}

void Parser::setExpression(const std::string &s)
{
    expression = s;
}


Parser& Parser::operator=(const Parser &p)
{
    if (this == &p)
        return *this;
    
    this->expression = p.getExpression();
    return *this;
}
