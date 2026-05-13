#include <cstddef>
#include <iostream>
#include <string>
#include "graph.hpp"
#include "exceptions.hpp"
#include "function.hpp"

constexpr size_t SCR_WIDTH = 800;
constexpr size_t SCR_HEIGHT = 600;

int main() 
{
    std::cout << "Graphing calculator\n";

    std::cout << "Welcome to graphing calculator!!!\n";

    try {
        std::string expr, line;

        std::cout << "Enter a valid expression (only '(', ')', '+', '-', '*', '/', 'x'):\n";
        std::getline(std::cin, expr);

        std::cout << "Enter how big you want the graph to be:\n";
        std::cout << "You'll still be able to adjust the size with NumpadPlus and NumpadMinus\n";
        std::getline(std::cin, line);

        double a = 10;
        if (!line.empty()) {
            a = std::stod(line);            
        }

        Graph grapher(SCR_WIDTH, SCR_HEIGHT, a, "Graphing Calculator");
        
        grapher.addFunction(new ParsedFunction(expr));
        grapher.addFunction(new PolynomialFunction({-5.0, 0.0, 1.0}));
        grapher.addFunction(new TrigonometricFunction("sin", 2.0, 1.0));
        
        std::cout << grapher << "\n";
        
        grapher.run();
    } catch (const GraphException& e) { // Prindem excepțiile din ierarhia noastră
        std::cerr << "\n[Eroare Interna Grafic]: " << e.what() << "\n";
    } catch (const std::exception& e) { // Prindem orice altceva (ex. std::stod fails)
        std::cerr << "\n[Eroare Generala]: " << e.what() << "\n";
    }

    std::cout << "\nTotal number of functions: " 
              << MathFunction::totalFunctions << "\n";

    return 0;
}
