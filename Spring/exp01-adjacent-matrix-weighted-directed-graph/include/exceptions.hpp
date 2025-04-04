#pragma once

#include <iostream>
#include <string>
#include <utility>

class IllegalParameterValue {
public:
  IllegalParameterValue(std::string message = "Illegal parameter value") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class NoVertex {
public:
  NoVertex(std::string message = "No vertex.") { m_message = std::move(message); }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class VertexNotFound {
public:
  VertexNotFound(std::string message = "Vertex not found.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cerr << m_message << '\n'; }

private:
  std::string m_message;
};

class VertexAlreadyExists {
public:
  VertexAlreadyExists(std::string message = "Vertex already exists.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class EdgeNotFound {
public:
  EdgeNotFound(std::string message = "Edge not found.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class EdgeAlreadyExists {
public:
  EdgeAlreadyExists(std::string message = "Edge already exists.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class InfiniteWeight {
public:
  InfiniteWeight(std::string message = "Infinite weight.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class NegativeEdge {
public:
  NegativeEdge(std::string message = "Negative edge.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class NegativeCycle {
public:
  NegativeCycle(std::string message = "Negative cycle.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};

class GraphDisconnected {
public:
  GraphDisconnected(std::string message = "Graph is disconnected.") {
    m_message = std::move(message);
  }
  void outputMessage() { std::cout << m_message << '\n'; }

private:
  std::string m_message;
};
