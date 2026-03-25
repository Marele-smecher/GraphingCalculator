#include "graph.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Graph::Graph(uint32_t w, uint32_t h, double a, const std::string &title)
    : window(sf::VideoMode({w, h}), title, sf::State::Windowed),
      a(a), scale(static_cast<float>(w) / (2.0f * static_cast<float>(a)))
{
    
}

void Graph::setFunction(const std::string &s)
{
    currentFunction = Function(s, a);
}

void Graph::handleInput()
{
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if  (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadPlus) {
                if (a == 1) return;
                a -= 1;
                std::cout << a << "\n";
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadMinus) {
                a += 1;
                std::cout << a << "\n";
            }
        }
    }
}

void Graph::render()
{
    window.clear(sf::Color::White);

    sf::Vector2u size = window.getSize();
    const auto width = static_cast<float>(size.x);
    const auto height = static_cast<float>(size.y);
    const float midX = width / 2.0f;
    const float midY = height / 2.0f;
    
    scale = static_cast<float>(width) / (2.0f * static_cast<float>(a));

    sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, midY);
    xAxis[1].position = sf::Vector2f(static_cast<float>(width), midY);
    xAxis[0].color = xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
    yAxis[0].position = sf::Vector2f(midX, 0);
    yAxis[1].position = sf::Vector2f(midX, static_cast<float>(height));
    yAxis[0].color = yAxis[1].color = sf::Color::Black;

    window.draw(xAxis);
    window.draw(yAxis);

    const auto& points = currentFunction.getPoints(); 
    if (points.size() > 1) {
        sf::VertexArray plot(sf::PrimitiveType::Lines, 2 * (points.size() - 1));
        size_t vertexIndex = 0;

        for (size_t i = 0; i < points.size() - 1; ++i) {
            float x1 = midX + (static_cast<float>(points[i].getX()) * scale);
            float y1 = midY - (static_cast<float>(points[i].getY()) * scale);

            float x2 = midX + (static_cast<float>(points[i+1].getX()) * scale);
            float y2 = midY - (static_cast<float>(points[i+1].getY()) * scale);

            if ((y1 < 0 && y2 < 0) || (y1 > height && y2 > height)) {
                continue; 
            }

            plot[vertexIndex].position = {x1, y1};
            plot[vertexIndex].color = sf::Color::Red;
            
            plot[vertexIndex + 1].position = {x2, y2};
            plot[vertexIndex + 1].color = sf::Color::Red;

            vertexIndex += 2;
        }
        window.draw(plot);
    }
    window.display();
}

void Graph::run()
{
    while (window.isOpen()) {
        /// Events
        handleInput();

        /// Update

        /// Draw
        render();
    }
}