#pragma once

#include "point.hpp"
#include "parser.hpp"
#include <vector>

class MathFunction
{
public:
    static int totalFunctions; 
protected:
    virtual void print(std::ostream& os) const = 0;
public:
    MathFunction();

    [[nodiscard]] virtual double evaluate(double x) const = 0;
    [[nodiscard]] virtual MathFunction* clone() const = 0;
    friend std::ostream& operator<<(std::ostream& out, const MathFunction& f);

    virtual ~MathFunction() = default;
};

class ParsedFunction : public MathFunction
{
    Parser p; 
    std::string expressionName;
protected:
    void print(std::ostream& os) const override;
public:
    explicit ParsedFunction(const std::string &expr);

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
};

class PolynomialFunction : public MathFunction
{
    std::vector<double> coeff;
protected:
    void print(std::ostream& os) const override;
public:
    explicit PolynomialFunction(std::vector<double> coefficients);

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
};

class TrigonometricFunction : public MathFunction
{
    std::string functionType;
    double amplitude, frequency;
protected:
    void print(std::ostream& os) const override;
public:
    TrigonometricFunction(std::string type, double amp, double freq);

    double evaluate(double x) const override;
    MathFunction* clone() const override;
};

/*class ExponentialFunction : public MathFunction
{
    double base, exponent;
protected:
    void print(std::ostream& os) const override;
public:
    ExponentialFunction(double b, double exp);

    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
};
*/
