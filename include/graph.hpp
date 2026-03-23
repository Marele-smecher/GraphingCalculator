#pragma once

#include <SFML/Graphics.hpp>
#include "function.hpp"

class Graph
{
    sf::RenderWindow window;
    Function currentFunction;

    float zoomScale;
    sf::Vector2f originOffset;
    void updateView();
public:
    Graph(uint32_t w, uint32_t h, const std::string& title);

    void render();
    void handleInput();
    void run();

    ~Graph() = default;
};
