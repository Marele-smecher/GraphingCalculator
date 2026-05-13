#pragma once

#include <exception>
#include <string>

class GraphException : std::exception
{
protected:
    std::string message;
public:
    explicit GraphException(const std::string &message);
    [[nodiscard]] const char* what() const noexcept override;
};

class ParseErrorException : GraphException
{
public:
    explicit ParseErrorException(const std::string &message);
};

class DomainException : GraphException
{
public:
    explicit DomainException(const std::string &message);
};

class RenderInitException : GraphException
{
public:
    explicit RenderInitException(const std::string &message);
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