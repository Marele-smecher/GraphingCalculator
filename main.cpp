#include <iostream>
#include "graph.hpp"

constexpr uint32_t SCR_WIDTH = 800;
constexpr uint32_t SCR_HEIGHT = 600;

int main() 
{
    std::cout << "Graphing calculator\n";

    std::string line;
    Parser parser;

    while (true)  {
        std::cout << "Go to GUI?(y/N/quit)\n";
        std::getline(std::cin, line);
        if (line == "Y" || line == "y") {
            Graph graph(SCR_WIDTH, SCR_HEIGHT, "Graphing calculator");
            graph.run();
            break;
        } else if (line == "N" || line == "n") {
            std::getline(std::cin, line);
            parser.setExpression(line);
            while (true) {
                std::cout << "Number(or 'quit' to go to GUI or use another expression):\n";
                std::getline(std::cin, line);
                if (line == "quit") {
                    break;
                }
                double x = std::stod(line,nullptr);
                std::cout << parser.evaluate(x) << "\n";
            }
        } else if (line == "quit") {
            break;
        }
    }
    
    return 0;
}
