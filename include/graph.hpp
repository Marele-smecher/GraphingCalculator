#pragma once

#include <ostream>
#include <SFML/Graphics.hpp>
#include "function.hpp"

class Graph
{
    sf::RenderWindow window;
    std::vector<MathFunction*> functions;
    float scale;
    sf::Vector2f range;
    sf::Vector2f center;

    void handleInput();
    void render();
public:
    /***
    copy constructor
    Graph& operator=(Graph other)
    destructor
    void swap(Graph& first, Graph& second) noexcept (friend)
    void handleInput()
    void render()
    void run()
    void addFunction(MathFunction* f)    
    */
    
    Graph(uint32_t w, uint32_t h, double a, const std::string& title);
    Graph(const Graph &g);
    Graph& operator=(Graph other);
    friend void swap(Graph &first, Graph &second) noexcept;
    friend std::ostream& operator<<(std::ostream &out, const Graph &g);
    
    void addFunction(MathFunction *f);
    void run();

    ~Graph();
};
