#pragma once

#include <iostream>
#include <string>
#include <utility>

class DuplicateVertex
{
public:
    DuplicateVertex(std::string message = "Duplicate vertex.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class VertexNotFound
{
public:
    VertexNotFound(std::string message = "Vertex not found.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class DuplicateEdge
{
public:
    DuplicateEdge(std::string message = "Duplicate edge.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class EdgeNotFound
{
public:
    EdgeNotFound(std::string message = "Edge not found.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class InvalidWeight
{
public:
    InvalidWeight(std::string message = "Invalid weight.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class SelfLoopNotAllowed
{
public:
    SelfLoopNotAllowed(std::string message = "Loop not allowed.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class NegativeEdge
{
public:
    NegativeEdge(std::string message = "Negative edge.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};

class NegativeCycle
{
public:
    NegativeCycle(std::string message = "Negative cycle.")
    {
        m_message = std::move(message);
    }
    void outputMessage()
    {
        std::cerr << m_message << '\n';
    }

private:
    std::string m_message;
};