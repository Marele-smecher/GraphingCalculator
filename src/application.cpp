#include "application.hpp"
#include <iostream>
#include "graph.hpp"
#include "parser.hpp"
#include "exceptions.hpp"

void CalculatorApp::run() {
    std::cout << "Graphing calculator\n";
    std::cout << "Welcome to graphing calculator!!!\n";

    try {
        std::string expr, line;

        std::cout << "Enter a valid expression (only '(', ')', '+', '-', '*', '/', 'x'):\n";
        std::getline(std::cin, expr);

        if (!Parser::isValid(expr)) {
            throw ParseErrorException("Invalid expresion!");
        }

        std::cout << "Enter how big you want the graph to be:\n";
        std::cout << "You'll still be able to adjust the size with NumpadPlus and NumpadMinus\n";
        std::getline(std::cin, line);

        double a = 10;
        if (!line.empty()) {
            a = std::stod(line);            
        }

        constexpr size_t SCR_WIDTH = 800;
        constexpr size_t SCR_HEIGHT = 600;

        // Inițializăm graful cu dimensiunile dorite
        Graph grapher(SCR_WIDTH, SCR_HEIGHT, a, "Graphing Calculator");
        
        // În loc de new direct, folosim Factory-ul nostru curat!
        grapher.addFunction(FunctionFactory::createParsed(expr));
        grapher.addFunction(FunctionFactory::createPolynomial({-5.0, 0.0, 1.0}));
        grapher.addFunction(FunctionFactory::createTrigonometric("sin", 2.0, 1.0));
        grapher.addFunction(FunctionFactory::createExponential(2.718, 1.0));
        
        std::cout << grapher << "\n";
        
        // Pornim loop-ul SFML
        grapher.run();

    } catch (const GraphException& e) { 
        std::cerr << "\n[Eroare Interna Grafic]: " << e.what() << "\n";
    } catch (const std::exception& e) { 
        std::cerr << "\n[Eroare Generala]: " << e.what() << "\n";
    }

    // Afișăm statistica la final, apelând variabila statică din clasa de bază
    std::cout << "\nTotal number of functions: " 
              << MathFunction::totalFunctions << "\n";
}