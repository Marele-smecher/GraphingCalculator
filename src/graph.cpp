#include "graph.hpp"

Graph::Graph(uint32_t w, uint32_t h, const std::string &title)
{
    window.create(sf::VideoMode({w, h}), title, sf::State::Windowed);
}

void Graph::run()
{
    while (window.isOpen()) {
        /// Events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if  (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }

        /// Update

        /// Draw

    }
}