#include "graph.hpp"
#include "exceptions.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <function.hpp>
#include <iostream>
#include <ostream>
#include <cmath>

Graph::Graph(uint32_t w, uint32_t h, double a, const std::string &title)
    : window(sf::VideoMode({w, h}), title, sf::State::Windowed),
     center(0.0f, 0.0f)
{
    if (!window.isOpen()) throw RenderInitException();

    range.x = static_cast<float>(-a);
    range.y = static_cast<float>(a);    
    scale = static_cast<float>(w) / (range.y - range.x);
}

Graph::Graph(const Graph &g) 
    : window(sf::VideoMode({800, 600}), "Graph Copy", sf::State::Windowed), 
      scale(g.scale), range(g.range), center(g.center)
{
    for (auto f : g.functions) {
        functions.push_back(f->clone());
    }
}

Graph& Graph::operator=(Graph other)
{
    swap(*this, other);
    return *this;
}

void swap(Graph &first, Graph &second) noexcept
{
    std::swap(first.functions, second.functions);
    std::swap(first.range, second.range);
    std::swap(first.center, second.center);
    std::swap(first.scale, second.scale);
}

Graph::~Graph()
{
    for (auto w : functions) {
        delete w;
    }
}

std::ostream& operator<<(std::ostream &out, const Graph &g)
{
    out << "Settings: a=" << g.range.x << ", " << g.range.y << ", scale=" << g.scale << "\nFunctions:\n";
    for (const auto& f : g.functions) {
        out << " - " << *f << "\n"; 
    }
    return out;
}

void Graph::addFunction(MathFunction *f)
{
    functions.push_back(f);
}

void Graph::handleInput()
{
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            float movWidth = (range.y - range.x);
            float moveSpeed = movWidth * 0.05f;

            if  (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadPlus) {
                if (movWidth <= 1) return;
                range.x += movWidth * 0.1f;
                range.y -= movWidth * 0.1f;
                std::cout << range.x << " " << range.y << "\n";
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::NumpadMinus) {
                range.x -= movWidth * 0.1f;
                range.y += movWidth * 0.1f;
                std::cout << range.x << " " << range.y << "\n";
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                range.x += moveSpeed;
                range.y += moveSpeed;
                center.x += moveSpeed;
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                center.y += moveSpeed; 
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                range.x -= moveSpeed;
                range.y -= moveSpeed;
                center.x -= moveSpeed;
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                center.y -= moveSpeed;
            }
            
            /*
                Right,          //!< Keyboard Right Arrow key
    Left,           //!< Keyboard Left Arrow key
    Down,           //!< Keyboard Down Arrow key
    Up,             //!< Keyboard Up Arrow key
*/
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
    
    scale = width / (range.y - range.x);

    sf::Color gridColor(220, 220, 220); 

    int startX = static_cast<int>(std::ceil(range.x));
    int endX = static_cast<int>(std::floor(range.y));
    
    for (int i = startX; i <= endX; ++i) {
        float x_screen = (i - range.x) * scale;
        sf::VertexArray vLine(sf::PrimitiveType::Lines, 2);
        vLine[0].position = sf::Vector2f(x_screen, 0);
        vLine[1].position = sf::Vector2f(x_screen, height);
        vLine[0].color = vLine[1].color = gridColor;
        window.draw(vLine);
    }

    float mathHeight = height / scale; 
    float minY = center.y - (mathHeight / 2.0f);
    float maxY = center.y + (mathHeight / 2.0f);
    
    int startY = static_cast<int>(std::ceil(minY));
    int endY = static_cast<int>(std::floor(maxY));

    for (int i = startY; i <= endY; ++i) {
        float y_screen = midY - ((i - center.y) * scale);
        sf::VertexArray hLine(sf::PrimitiveType::Lines, 2);
        hLine[0].position = sf::Vector2f(0, y_screen);
        hLine[1].position = sf::Vector2f(width, y_screen);
        hLine[0].color = hLine[1].color = gridColor;
        window.draw(hLine);
    }

    float originX_screen = (0.0f - range.x) * scale;
    float originY_screen = midY + (center.y * scale);

    sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
    xAxis[0].position = sf::Vector2f(0, originY_screen);
    xAxis[1].position = sf::Vector2f(static_cast<float>(width), originY_screen);
    xAxis[0].color = xAxis[1].color = sf::Color::Black;

    sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
    yAxis[0].position = sf::Vector2f(originX_screen, 0);
    yAxis[1].position = sf::Vector2f(originX_screen, static_cast<float>(height));
    yAxis[0].color = yAxis[1].color = sf::Color::Black;

    window.draw(xAxis);
    window.draw(yAxis);

    const float step = (range.y - range.x) / width;

    for (auto f : functions) {
        
        sf::Color plotColor = sf::Color::Red;
        if (dynamic_cast<TrigonometricFunction*>(f)) {
            plotColor = sf::Color::Blue;
        } else if (dynamic_cast<ParsedFunction*>(f)) {
            plotColor = sf::Color::Green;
        }

        std::vector<sf::Vertex> linePoints;

        for (float mathX = range.x; mathX <= range.y; mathX += step) {
            try {
                double mathY = f->evaluate(mathX); 

                float x_screen = (mathX - range.x) * scale;
                float y_screen = midY - ((static_cast<float>(mathY) - center.y) * scale);

                if (y_screen >= -100 && y_screen <= height + 100) {
                    linePoints.push_back(sf::Vertex(sf::Vector2f(x_screen, y_screen), plotColor));
                }
            } catch (const DomainException& e) {
                continue;
            }
        }

        if (linePoints.size() > 1) {
            sf::VertexArray plot(sf::PrimitiveType::LineStrip, linePoints.size());
            for(size_t i = 0; i < linePoints.size(); ++i) {
                plot[i] = linePoints[i];
            }
            window.draw(plot);
        }
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
