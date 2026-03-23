#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "graph.hpp"

constexpr uint32_t SCR_WIDTH = 800;
constexpr uint32_t SCR_HEIGHT = 600;

int main() 
{
    std::cout << "Graphing calculator\n";

    Graph graph(SCR_WIDTH, SCR_HEIGHT, "Graphing calculator");
    graph.run();
    return 0;
}
