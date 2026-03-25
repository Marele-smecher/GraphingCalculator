#pragma once

#include <ostream>
#include <SFML/Graphics.hpp>
#include "function.hpp"

class Graph
{
    sf::RenderWindow window;
    Function currentFunction;
    double a; /// we'll see the grid [-a, a] * [-a, a]
    float scale;

    void handleInput();
    void render();
public:
    Graph(uint32_t w, uint32_t h, double a, const std::string& title);

    void run();
    void setFunction(const std::string &s);

    friend std::ostream& operator<<(std::ostream &out, const Graph &g);

    ~Graph();
};
