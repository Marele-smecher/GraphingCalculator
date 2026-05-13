#pragma once

#include <exception>
#include <string>

class GraphException : public std::exception
{
protected:
    std::string message;
public:
    explicit GraphException(const std::string &message);
    [[nodiscard]] const char* what() const noexcept override;
};

class ParseErrorException : public GraphException
{
public:
    explicit ParseErrorException(const std::string &message);
};

class DomainException : public GraphException
{
public:
    explicit DomainException(double x);
};

class RenderInitException : public GraphException
{
public:
    explicit RenderInitException();
};

/***
Ierarhia de Excepții

    clasa GraphException : std::exception

        variabile: message (string, protected)

        metode: constructor, what (suprascrisă)

    clasa ParseErrorException : GraphException

        variabile: -

        metode: constructor

    clasa DomainException : GraphException

        variabile: -

        metode: constructor

    clasa RenderInitException : GraphException

        variabile: -

        metode: constructor

*/