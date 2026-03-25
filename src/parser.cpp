#include <cctype>
#include <parser.hpp>
#include <cmath>
#include <stdexcept>

Parser::Parser(std::string s) : expression(std::move(s))
{}

double Parser::parseExpression(size_t &i, double x) // NOLINT(misc-no-recursion)
{ 
    double ans = parseTerm(i, x);

    while (i < expression.length()) {
        while (i < expression.length() && std::isspace(expression[i])) i++;
        if (i >= expression.length()) break;

        char op = expression[i];
        if (op != '+' && op != '-') break;

        i++; 
        if (op == '+') ans += parseTerm(i, x);
        else ans -= parseTerm(i, x);
    }
    return ans;
}

double Parser::parseTerm(size_t &i, double x) // NOLINT(misc-no-recursion)
{
    double ans = parseFactor(i, x);

    while (i < expression.length()) {
        while (i < expression.length() && std::isspace(expression[i])) i++;
        if (i >= expression.length()) break;

        char op = expression[i];
        if (op != '*' && op != '/') break;

        i++; 
        double nextFactor = parseFactor(i, x);
        if (op == '*') {
            ans *= nextFactor;
        } else {
            if (std::abs(nextFactor) < 1e-9) return std::nan("");
            ans /= nextFactor;
        }
    }
    return ans;
}

double Parser::parseFactor(size_t &i, double x) // NOLINT(misc-no-recursion)
{ 
    while (i < expression.length() && std::isspace(expression[i])) i++;

    if (i >= expression.length()) throw std::runtime_error("Unexpected end of expression");

    if (expression[i] == 'x') {
        i++;
        return x;
    }

    if (expression[i] == '(') {
        i++; 
        double ans = parseExpression(i, x);
        while (i < expression.length() && std::isspace(expression[i])) i++;
        if (i < expression.length() && expression[i] == ')') {
            i++; 
        } else {
            throw std::runtime_error("Missing closing parenthesis");
        }
        return ans;
    } 

    size_t start = i;
    bool hasDecimal = false;
    while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
        if (expression[i] == '.') {
            if (hasDecimal) throw std::runtime_error("Multiple decimal points in number");
            hasDecimal = true;
        }
        i++;
    }

    if (start == i) throw std::runtime_error("Expected a number or 'x' at position " + std::to_string(i));
    
    return std::stod(expression.substr(start, i - start));
}

double Parser::evaluate(double x) 
{
    size_t i = 0;
    double result = parseExpression(i, x);
    
    while (i < expression.length() && std::isspace(expression[i])) i++;
    if (i < expression.length()) {
        throw std::runtime_error("Invalid expression: trailing characters at " + std::to_string(i));
    }
    return result;
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
    if (this != &p) {
        this->expression = p.getExpression();
    }
    return *this;
}
