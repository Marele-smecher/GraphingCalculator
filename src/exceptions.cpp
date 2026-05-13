#include "exceptions.hpp"

GraphException::GraphException(const std::string &message) : message(message) 
{}

const char* GraphException::what() const noexcept 
{
    return message.c_str();
}

ParseErrorException::ParseErrorException(const std::string &message) 
    : GraphException("Eroare de parsare: " + message) 
{}

DomainException::DomainException(double x) 
    : GraphException("Eroare de domeniu matematic (ex. div la 0) pentru x = " + std::to_string(x)) 
{}

RenderInitException::RenderInitException() 
    : GraphException("Nu s-a putut initializa fereastra SFML!") 
{}

