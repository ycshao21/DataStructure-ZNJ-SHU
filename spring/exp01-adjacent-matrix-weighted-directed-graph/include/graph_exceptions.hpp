#pragma once

#include <print>
#include <iostream>
#include <string>
#include <utility>

class GraphException
{
public:
    GraphException(std::string message) : m_message(std::move(message))
    {
    }

    virtual void report() const
    {
        std::println(std::cerr, "{}", m_message);
    }

private:
    std::string m_message;
};

class DuplicateVertexException : public GraphException
{
public:
    DuplicateVertexException(std::string message = "Vertex is already in the graph!")
        : GraphException(std::move(message))
    {
    }
};

class VertexNotFoundException : public GraphException
{
public:
    VertexNotFoundException(std::string message = "Vertex is not in the graph!")
        : GraphException(std::move(message))
    {
    }
};

class DuplicateEdgeException : public GraphException
{
public:
    DuplicateEdgeException(std::string message = "Edge is already in the graph!")
        : GraphException(std::move(message))
    {
    }
};

class EdgeNotFoundException : public GraphException
{
public:
    EdgeNotFoundException(std::string message = "Edge is not in the graph!")
        : GraphException(std::move(message))
    {
    }
};

class InvalidWeightException : public GraphException
{
public:
    InvalidWeightException(std::string message = "Invalid weight!")
        : GraphException(std::move(message))
    {
    }
};

class SelfLoopNotAllowedException : public GraphException
{
public:
    SelfLoopNotAllowedException(std::string message = "Self loop is not allowed!")
        : GraphException(std::move(message))
    {
    }
};

class NegativeEdgeException : public GraphException
{
public:
    NegativeEdgeException(std::string message = "Negative edge!")
        : GraphException(std::move(message))
    {
    }
};

class NegativeCycleException : public GraphException
{
public:
    NegativeCycleException(std::string message = "Negative cycle!")
        : GraphException(std::move(message))
    {
    }
};
