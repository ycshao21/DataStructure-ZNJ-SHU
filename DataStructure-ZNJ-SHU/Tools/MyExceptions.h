#pragma once
#include <iostream>
#include <string>

class IllegalParameterValue
{
public:
    IllegalParameterValue(std::string theMessage = "Illegal parameter value") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class IllegalIndex
{
public:
    IllegalIndex(std::string theMessage = "Illegal index") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

/* Stack */

class StackEmpty
{
public:
    StackEmpty(std::string theMessage = "Stack empty") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

/* Tree */

class EmptyTree
{
public:
    EmptyTree(std::string theMessage = "Empty tree.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

/* Graph */

class NoVertex
{
public:
    NoVertex(std::string theMessage = "No vertex.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class VertexNotFound
{
public:
    VertexNotFound(std::string theMessage = "Vertex not found.") {
        message = theMessage;
    }
    void outputMessage() { std::cerr << message << std::endl; }
private:
    std::string message;
};

class VertexAlreadyExists
{
public:
    VertexAlreadyExists(std::string theMessage = "Vertex already exists.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class EdgeNotFound
{
public:
    EdgeNotFound(std::string theMessage = "Edge not found.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class EdgeAlreadyExists
{
public:
    EdgeAlreadyExists(std::string theMessage = "Edge already exists.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class NegativeEdge
{
public:
    NegativeEdge(std::string theMessage = "Negative edge.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class NegativeCycle
{
public:
    NegativeCycle(std::string theMessage = "Negative cycle.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class GraphDisconnected
{
public:
    GraphDisconnected(std::string theMessage = "Graph is disconnected.") {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};
