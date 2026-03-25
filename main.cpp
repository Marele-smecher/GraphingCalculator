#include <cstddef>
#include <iostream>
#include <string>
#include "graph.hpp"

constexpr size_t SCR_WIDTH = 800;
constexpr size_t SCR_HEIGHT = 600;

int main() 
{
    std::cout << "Graphing calculator\n";

    std::string expr, line;

    std::cout << "Enter a valid expression(only \'(\', \')\', \'+\',  \'-\',  \'*\',  \'/\',  \'x\'):\n";
    std::getline(std::cin, expr);
    std::cout << "Enter how big you want the graph to be:\n";
    std::getline(std::cin, line);
    const double a = std::stod(line);
    Graph grapher(SCR_WIDTH, SCR_HEIGHT, a, "Graphing Calculator");
    grapher.setFunction(expr);
    grapher.run();
    
    return 0;
}
