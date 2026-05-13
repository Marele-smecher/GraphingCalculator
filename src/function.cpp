#include "function.hpp"
#include <cmath>
#include <iostream>

int MathFunction::totalFunctions = 0; 

MathFunction::MathFunction() 
{
    totalFunctions++;
}

std::ostream& operator<<(std::ostream& out, const MathFunction& f) 
{
    f.print(out); 
    return out;
}

ParsedFunction::ParsedFunction(const std::string &expr) 
    : MathFunction(), p(expr), expressionName(expr) {}

double ParsedFunction::evaluate(double x) const 
{
    return const_cast<Parser&>(p).evaluate(x);
}

MathFunction* ParsedFunction::clone() const 
{
    return new ParsedFunction(*this);
}

void ParsedFunction::print(std::ostream& os) const 
{
    os << "f(x) = " << expressionName << " (Expresie parsata)";
}

PolynomialFunction::PolynomialFunction(std::vector<double> coefficients) 
    : MathFunction(), coeff(std::move(coefficients)) {}

double PolynomialFunction::evaluate(double x) const 
{
    double result = 0;
    double currentX = 1.0;
    
    for (double c : coeff) {
        result += c * currentX;
        currentX *= x;
    }
    return result;
}

MathFunction* PolynomialFunction::clone() const 
{
    return new PolynomialFunction(*this);
}

void PolynomialFunction::print(std::ostream& os) const 
{
    os << "Polinom de grad " << (coeff.empty() ? 0 : coeff.size() - 1);
}

TrigonometricFunction::TrigonometricFunction(std::string type, double amp, double freq)
    : MathFunction(), functionType(std::move(type)), amplitude(amp), frequency(freq) {}

double TrigonometricFunction::evaluate(double x) const 
{
    if (functionType == "sin") {
        return amplitude * std::sin(frequency * x);
    } else if (functionType == "cos") {
        return amplitude * std::cos(frequency * x);
    } else if (functionType == "tan") {
        return amplitude * std::tan(frequency * x);
    }
    return 0.0; 
}

MathFunction* TrigonometricFunction::clone() const 
{
    return new TrigonometricFunction(*this);
}

void TrigonometricFunction::print(std::ostream& os) const 
{
    os << amplitude << " * " << functionType << "(" << frequency << " * x)";
}

ExponentialFunction::ExponentialFunction(double b, double exp)
    : MathFunction(), base(b), exponent(exp) {}

double ExponentialFunction::evaluate(double x) const 
{
    // Calculeaza base la puterea (exponent * x)
    return std::pow(base, exponent * x);
}

MathFunction* ExponentialFunction::clone() const 
{
    return new ExponentialFunction(*this);
}

void ExponentialFunction::print(std::ostream& os) const 
{
    os << base << "^(" << exponent << " * x)";
}
