#pragma once
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include<ranges>
#include<iomanip>
#include<limits>
#include"AdjListEdge.h"
#include"MinimumSpanningTree.h"
#include"../../Tools/MyExceptions.h"

template<class VertTy = int, class WeightTy = int, WeightTy infinity = std::numeric_limits<WeightTy>::max()>
class AdjListWUndirGraph
{
    using Graph = AdjListWUndirGraph<VertTy, WeightTy, infinity>;
    using indext = size_t;
    using sizet = size_t;
    using Edge = AdjListEdge<WeightTy>;
    using EdgeList = std::list<Edge>;
public:
    AdjListWUndirGraph(sizet vertNum = 0) : _vertices(vertNum), _adjList(vertNum), _edgeNum(0) {}
    AdjListWUndirGraph(const std::vector<VertTy>& vertices);
    AdjListWUndirGraph(const Graph&) = default;
    AdjListWUndirGraph(Graph&&) = default;
    Graph& operator=(const Graph&) = default;
    ~AdjListWUndirGraph() = default;

    /* Status */

    sizet numOfVertices() const { return _vertices.size(); }
    sizet numOfEdges() const { return _edgeNum; }
    bool connected() const;
    sizet numOfConnectedComponent() const;
    bool hasUniqueMST() const { return MST::isUnique(*this); }

    /* Element Access */
public:
    sizet degree(const VertTy& vert) const;

    const VertTy* firstAdjVertex(const VertTy& from) const;
    VertTy* firstAdjVertex(const VertTy& from);
    const VertTy* nextAdjVertex(const VertTy& from, const VertTy& after)const;
    VertTy* nextAdjVertex(const VertTy& from, const VertTy& after);

    WeightTy getWeight(const VertTy& from, const VertTy& to) const;
    WeightTy getInfinity() const { return infinity; }
private:
    indext indexOfVertex(const VertTy& vert) const;

    /* Modifier */
public:
    void clear() { _vertices.clear(), _adjList.clear(), _edgeNum = 0; }
    void setVertex(const VertTy& oldVert, const VertTy& newVert) { _vertices[indexOfVertex(oldVert)] = newVert; }
    void insertVertex(const VertTy& vert);
    void eraseVertex(const VertTy& vert);
    void setWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight);
    void insertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight);
    void eraseEdge(const VertTy& from, const VertTy& to);

    /* Traversal */
public:
    // @brief Depth-first search from one vertex.
    void DFS(const VertTy& from, void (*visit)(const VertTy&) = outputVertex) const;
    // @brief Depth-first search for the whole graph.
    void DFS(void (*visit)(const VertTy&) = outputVertex) const;
    // @brief Breadth-first search from one vertex.
    void BFS(const VertTy& from, void (*visit)(const VertTy&) = outputVertex) const;
    // @brief Breadth-first search for the whole graph.
    void BFS(void (*visit)(const VertTy&) = outputVertex) const;
private:
    void _dfs(indext sourceIndex, std::vector<uint8_t>& visited, void (*visit)(const VertTy&) = outputVertex) const;
    void _bfs(indext sourceIndex, std::vector<uint8_t>& visited, void (*visit)(const VertTy&) = outputVertex) const;
    static void outputVertex(const VertTy& vert) { std::cout << vert << " "; }

    /* Minimum Spanning Tree */
public:
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend WeightTy MST::Kruskal(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend WeightTy MST::Prim(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend WeightTy MST::ReverseDelete(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out);
private:
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend bool MST::treeFindPath(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& tree,
        indext prevIndex, indext fromIndex, indext endIndex, std::stack<MST_Edge<WeightTy>>& path);
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend bool MST::isUnique(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g);

    /* Output */
public:
    void printAdjList(std::ostream& out = std::cout) const;
    void printEdges(std::ostream& out = std::cout) const;

private:
    std::vector<VertTy> _vertices;
    std::vector<EdgeList> _adjList;
    sizet _edgeNum;

    class FindEdge  // For finding edge according to the toIndex.
    {
    public:
        FindEdge(indext toIndex) : _toIndex(toIndex) {}
        bool operator()(const Edge& edge) const { return edge.toIndex == _toIndex; }
    private:
        indext _toIndex;
    };
};

template<class VertTy, class WeightTy, WeightTy infinity>
AdjListWUndirGraph<VertTy, WeightTy, infinity>::AdjListWUndirGraph(const std::vector<VertTy>& vertices) {
    // Check if there are duplicate vertices.
    for (const auto& vert : vertices) {
        if (std::ranges::find(_vertices, vert) == _vertices.end()) {
            _vertices.push_back(vert);
        }
    }
    _adjList.resize(_vertices.size());
    _edgeNum = 0;
}

template<class VertTy, class WeightTy, WeightTy infinity>
bool AdjListWUndirGraph<VertTy, WeightTy, infinity>::connected() const {
    if (_vertices.empty()) {
        throw NoVertex();
    }
    if (_vertices.size() == 1) { return true; }
    if (_edgeNum < _vertices.size() - 1) { return false; }
    // If the graph can be wholly traversed from one vertex, it is connected.
    std::vector<uint8_t> visited(_vertices.size(), 0);
    _bfs(0, visited, nullptr);
    return std::ranges::find(visited, 0) == visited.end();
}

template<class VertTy, class WeightTy, WeightTy infinity>
size_t AdjListWUndirGraph<VertTy, WeightTy, infinity>::numOfConnectedComponent() const {
    if (_vertices.empty()) {
        throw NoVertex();
    }
    // The number of connected components is equal to the number of times of traversal.
    sizet cnt = 0;
    std::vector<uint8_t> visited(_vertices.size(), 0);
    for (indext vertIndex = 0; vertIndex < _vertices.size(); vertIndex++) {
        if (visited[vertIndex] == 0) {
            cnt++;
            _bfs(vertIndex, visited, nullptr);
        }
    }
    return cnt;
}

template<class VertTy, class WeightTy, WeightTy infinity>
auto AdjListWUndirGraph<VertTy, WeightTy, infinity>::degree(const VertTy& vert) const -> sizet {
    indext vertIndex = indexOfVertex(vert);
    return _adjList[vertIndex].size();
}

template<class VertTy, class WeightTy, WeightTy infinity>
const VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::firstAdjVertex(const VertTy& from) const {
    indext fromIndex = indexOfVertex(from);
    if (_adjList[fromIndex].empty()) { return nullptr; }
    indext toIndex = _adjList[fromIndex].front().to;
    return &_vertices[toIndex];
}

template<class VertTy, class WeightTy, WeightTy infinity>
VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::firstAdjVertex(const VertTy& from) {
    auto const_this = const_cast<const Graph*>(this);
    return const_cast<VertTy*>(const_this->firstAdjVertex(from));
}

template<class VertTy, class WeightTy, WeightTy infinity>
const VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& after) const {
    indext fromIndex = indexOfVertex(from),
        afterIndex = indexOfVertex(after);
    // Check if "to" is adjacent to "from".
    auto edgeIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(afterIndex));
    if (edgeIter == _adjList[fromIndex].end()) {
        return nullptr;
    }
    // Move to the next adjacent vertex.
    edgeIter++;
    if (edgeIter == _adjList[fromIndex].end()) {
        return nullptr;
    }
    indext nextIndex = edgeIter->toIndex;
    return &_vertices[nextIndex];
}

template<class VertTy, class WeightTy, WeightTy infinity>
VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& after) {
    auto const_this = const_cast<const Graph*>(this);
    return const_cast<VertTy*>(const_this->nextAdjVertex(from, after));
}

template<class VertTy, class WeightTy, WeightTy infinity>
WeightTy AdjListWUndirGraph<VertTy, WeightTy, infinity>::getWeight(const VertTy& from, const VertTy& to) const {
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    auto edgeIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(toIndex));
    if (edgeIter != _adjList[fromIndex].end()) {
        return edgeIter->weight;
    }
    return infinity;
}

template<class VertTy, class WeightTy, WeightTy infinity>
auto AdjListWUndirGraph<VertTy, WeightTy, infinity>::indexOfVertex(const VertTy& vert) const -> indext {
    indext i = 0;
    for (; i < _vertices.size(); i++) {
        if (_vertices[i] == vert) {
            break;
        }
    }
    if (i == _vertices.size()) {
        throw VertexNotFound();
    }
    return i;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::insertVertex(const VertTy& vert) {
    if (std::ranges::find(_vertices, vert) != _vertices.end()) {
        throw VertexAlreadyExists();
    }
    _vertices.push_back(vert);
    _adjList.push_back(std::list<Edge>{});
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::eraseVertex(const VertTy& vert) {
    indext vertIndex = indexOfVertex(vert);
    _edgeNum -= _adjList[vertIndex].size();
    for (indext fromIndex = 0; fromIndex < _adjList.size(); fromIndex++) {
        if (fromIndex == vertIndex) { continue; }
        auto edgeIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(vertIndex));
        if (edgeIter != _adjList[fromIndex].end()) {
            _adjList[fromIndex].erase(edgeIter);
        }
    }
    indext lastIndex = _vertices.size() - 1;
    if (vertIndex != lastIndex) {
        // Replace the vertex to be deleted with the last vertex
        _vertices[vertIndex] = std::move(_vertices[lastIndex]);
        _adjList[vertIndex] = std::move(_adjList[lastIndex]);
        for (indext fromIndex = 0; fromIndex < lastIndex; fromIndex++) {
            if (fromIndex == vertIndex) { continue; }
            auto edgeIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(lastIndex));
            if (edgeIter != _adjList[fromIndex].end()) {
                edgeIter->toIndex = vertIndex;
            }
        }
    }
    _vertices.pop_back();
    _adjList.pop_back();
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::setWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight) {
    if (newWeight == infinity) {
        throw IllegalParameterValue("Weight cannot be infinity.");
    }
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (fromIndex == toIndex) {
        throw EdgeNotFound();
    }
    // Modify the weight of the edge from "from" to "to".
    auto fromIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(toIndex));
    if (fromIter == _adjList[fromIndex].end()) {
        throw EdgeNotFound();
    }
    fromIter->weight = newWeight;
    // Modify the weight of the edge from "to" to "from".
    auto toIter = std::ranges::find_if(_adjList[toIndex], FindEdge(fromIndex));
    toIter->weight = newWeight;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::insertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight) {
    if (weight == infinity) {
        throw IllegalParameterValue("Weight cannot be infinity.");
    }
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (fromIndex == toIndex) {
        throw IllegalParameterValue("Loop is not allowed.");
    }
    // Check if the edge already exists.
    if (std::ranges::find_if(_adjList[fromIndex], FindEdge(toIndex)) != _adjList[fromIndex].end()) {
        throw EdgeAlreadyExists();
    }
    // Insert the edge at the front of the list.
    _adjList[fromIndex].push_front(Edge{ toIndex, weight });
    _adjList[toIndex].push_front(Edge{ fromIndex, weight });
    _edgeNum++;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::eraseEdge(const VertTy& from, const VertTy& to) {
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (fromIndex == toIndex) {
        throw EdgeNotFound();
    }
    // Erase (from, to).
    auto fromIter = std::ranges::find_if(_adjList[fromIndex], FindEdge(toIndex));
    if (fromIter == _adjList[fromIndex].end()) {
        throw EdgeNotFound();
    }
    _adjList[fromIndex].erase(fromIter);
    // Erase (to, from).
    auto toIter = std::ranges::find_if(_adjList[toIndex], FindEdge(fromIndex));
    _adjList[toIndex].erase(toIter);
    _edgeNum--;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::_dfs(indext sourceIndex,
    std::vector<uint8_t>& visited, void (*visit)(const VertTy&)) const
{
    // Visit the current vertex:
    visited[sourceIndex] = 1;
    if (visit != nullptr) {
        (*visit)(_vertices[sourceIndex]);
    }
    // Visit its unvisited adjacent vertices:
    for (const auto& edge : _adjList[sourceIndex]) {
        if (visited[edge.toIndex] == 0) {
            _dfs(edge.toIndex, visited, visit);
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::_bfs(indext sourceIndex,
    std::vector<uint8_t>& visited, void (*visit)(const VertTy&)) const
{
    std::queue<indext> vertQueue;
    // Visit the current vertex:
    visited[sourceIndex] = 1;
    if (visit != nullptr) {
        (*visit)(_vertices[sourceIndex]);
    }
    vertQueue.push(sourceIndex);
    while (!vertQueue.empty()) {
        indext curIndex = vertQueue.front();
        vertQueue.pop();
        // Visit its adjacent vertices:
        for (const auto& edge : _adjList[curIndex]) {
            indext adjIndex = edge.toIndex;
            if (visited[adjIndex] == 0) {
                visited[adjIndex] = 1;
                if (visit != nullptr) {
                    (*visit)(_vertices[adjIndex]);
                }
                vertQueue.push(adjIndex);
            }
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::DFS(const VertTy& source, void (*visit)(const VertTy&)) const {
    indext fromIndex = indexOfVertex(source);
    std::vector<uint8_t> visited(_vertices.size(), 0);
    _dfs(fromIndex, visited, visit);
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::DFS(void (*visit)(const VertTy&)) const {
    std::vector<uint8_t> visited(_vertices.size(), 0);
    for (indext fromIndex = 0; fromIndex < _vertices.size(); fromIndex++) {
        if (visited[fromIndex] == 0) {
            _dfs(fromIndex, visited, visit);
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::BFS(const VertTy& source, void (*visit)(const VertTy&)) const {
    indext fromIndex = indexOfVertex(source);
    std::vector<uint8_t> visited(_vertices.size(), 0);
    _bfs(fromIndex, visited, visit);
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::BFS(void (*visit)(const VertTy&)) const {
    std::vector<uint8_t> visited(_vertices.size(), 0);
    for (indext fromIndex = 0; fromIndex < _vertices.size(); fromIndex++) {
        if (visited[fromIndex] == 0) {
            _bfs(fromIndex, visited, visit);
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::printAdjList(std::ostream& out) const {
    for (indext fromIndex = 0; fromIndex < _vertices.size(); fromIndex++) {
        out << std::setw(4) << _vertices[fromIndex] << " | ";
        for (const auto& e : _adjList[fromIndex]) {
            out << _vertices[e.toIndex] << "(" << e.weight << ") -> ";
        }
        out << "end" << std::endl;
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::printEdges(std::ostream& out) const {
    sizet edgeCnt = 0;
    for (indext fromIndex = 0; fromIndex < _adjList.size(); fromIndex++) {
        for (const auto& e : _adjList[fromIndex]) {
            indext toIndex = e.toIndex;
            if (fromIndex < toIndex) {
                edgeCnt++;
                out << "(" << edgeCnt << ") "
                    << "(" << _vertices[fromIndex] << ", " << _vertices[toIndex] << "): "
                    << e.weight << "\n";
            }
        }
    }
}
