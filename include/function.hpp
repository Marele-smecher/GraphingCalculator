#pragma once

#include "point.hpp"
#include "parser.hpp"
#include <vector>

class MathFunction
{
    static int totalFunctions; 
protected:
    virtual void print(std::ostream& os) const;
public:
    MathFunction();

    [[nodiscard]] virtual double evaluate(double x) const = 0;
    [[nodiscard]] virtual MathFunction* clone() const = 0;
    friend std::ostream& operator<<(std::ostream& out, const MathFunction& f);

    virtual ~MathFunction() = 0;
};

class ParsedFunction : public MathFunction
{
    Parser p; 
    std::string expressionName;
public:
    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
    void print(std::ostream& os) const override;
};

class PolynomialFunction : public MathFunction
{
    std::vector<double> coeff;
public:
    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
    void print(std::ostream& os) const override;
};

class ExponentialFunction : public MathFunction
{
    double base, exponent;
public:
    [[nodiscard]] double evaluate(double x) const override;
    [[nodiscard]] MathFunction* clone() const override;
    void print(std::ostream& os) const override;
};

/*
class TrigonometricFunction : public MathFunction
{
    std::string functionType;
    double amplitude, frequency;
public:
    double evaluate(double x) const;
    MathFunction* clone() const;
    void print(std::ostream& os) const;
};*/

class Function
{
    Parser parser;
    std::vector<Point> points;
    std::string expressionName;
    double a;
    void clearPoints();
    void generatePoints(double minX, double maxX, double step);
public:
    Function() = default;
    explicit Function(const std::string& s, double a = 5);
    Function(const Function &F);

    [[nodiscard]] std::string getExpression() const;
    [[nodiscard]] std::vector<Point> getPoints() const;
    void setExpression(const std::string &s);

    friend std::ostream& operator<<(std::ostream& out, const Function &F);
    Function& operator=(const Function& F);

    ~Function();
};