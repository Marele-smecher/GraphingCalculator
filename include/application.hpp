#pragma once

#include <string>
#include <vector>
#include "function.hpp"

class FunctionFactory {
public:
    static MathFunction* createParsed(const std::string& expr) {
        return new ParsedFunction(expr);
    }
    
    static MathFunction* createPolynomial(const std::vector<double>& coefficients) {
        return new PolynomialFunction(coefficients);
    }
    
    static MathFunction* createTrigonometric(const std::string& type, double amp, double freq) {
        return new TrigonometricFunction(type, amp, freq);
    }
    
    static MathFunction* createExponential(double base, double exponent) {
        return new ExponentialFunction(base, exponent);
    }
};


class CalculatorApp {
private:
    CalculatorApp() = default;

    CalculatorApp(const CalculatorApp&) = delete;
    CalculatorApp& operator=(const CalculatorApp&) = delete;

public:
    static CalculatorApp& getInstance() {
        static CalculatorApp instance;
        return instance;
    }

    void run();
};