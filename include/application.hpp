#pragma once

#include <string>
#include <vector>
#include "function.hpp"

// --- DESIGN PATTERN 2: SIMPLE FACTORY ---
// Izolează crearea obiectelor matematice polimorfice de restul aplicației
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


// --- DESIGN PATTERN 1: SINGLETON ---
// Garantează că există o singură instanță a aplicației și oferă un punct global de acces
class CalculatorApp {
private:
    // Constructor privat ca să blocăm instanțierea din exterior
    CalculatorApp() = default;

    // Ștergem constructorul de copiere și operatorul de atribuire ca să evităm duplicarea
    CalculatorApp(const CalculatorApp&) = delete;
    CalculatorApp& operator=(const CalculatorApp&) = delete;

public:
    // Metoda statică pentru a obține singura instanță validă (Meyers Singleton)
    static CalculatorApp& getInstance() {
        static CalculatorApp instance;
        return instance;
    }

    // Funcția principală care pornește execuția și înglobează logica mare
    void run();
};