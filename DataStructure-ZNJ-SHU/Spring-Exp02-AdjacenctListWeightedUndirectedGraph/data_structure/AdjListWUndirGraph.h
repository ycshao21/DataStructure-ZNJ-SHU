#pragma once
#include<vector>
#include<list>
#include<queue>
#include<unordered_set>
#include<stack>
#include<algorithm>
#include<ranges>
#include<sstream>
#include"AdjListEdge.h"
//#include"MinimumSpanningTree.h"
#include"../../Tools/MyExceptions.h"

template<class VertTy = int, class WeightTy = int, WeightTy infinity = std::numeric_limits<WeightTy>::max()>
class AdjListWUndirGraph
{
public:
    using Graph = AdjListWUndirGraph<VertTy, WeightTy, infinity>;
    using indext = size_t;
    using sizet = size_t;
    using Edge = AdjListEdge<WeightTy>;
    using EdgeList = std::list<Edge>;
public:
    AdjListWUndirGraph(sizet vertNum = 0) : _vertices(vertNum), _adjList(vertNum), _edgeNum(0) {}
    AdjListWUndirGraph(const std::vector<VertTy>& vertices);
    AdjListWUndirGraph(const Graph&) = default;
    Graph& operator=(const Graph&) = default;
    ~AdjListWUndirGraph() = default;

    /* Status */

    bool empty() const { return _vertices.empty(); }
    sizet numOfvertices() const { return _vertices.size(); }
    sizet numOfEdges() const { return _edgeNum; }
    bool connected() const;
    sizet numOfConnectedComponent() const;
    bool hasUniqueMST() const;

    /* Element Access */

    sizet degree(const VertTy& vert) const;

    const VertTy* firstAdjVertex(const VertTy& from) const;
    VertTy* firstAdjVertex(const VertTy& from);
    const VertTy* nextAdjVertex(const VertTy& from, const VertTy& after)const;
    VertTy* nextAdjVertex(const VertTy& from, const VertTy& after);

    WeightTy getWeight(const VertTy& from, const VertTy& to) const;
    WeightTy getInfinity() const { return infinity; }

    /* Modifier */

    void clear() { _vertices.clear(), _adjList.clear(), _edgeNum = 0; }
    void setVertex(const VertTy& oldVert, const VertTy& newVert) { _vertices[indexOfVertex(oldVert)] = newVert; }
    void insertVertex(const VertTy& vert);
    void eraseVertex(const VertTy& vert);
    void setWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight);
    void insertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight);
    void eraseEdge(const VertTy& from, const VertTy& to);

    /* Traversal */

    void DFS_from(const VertTy& from, void (*traverse)(const VertTy&) = OutputVertex) const;
    void DFS_wholeGraph(void (*visit)(const VertTy&) = OutputVertex) const;
    void BFS_from(const VertTy& from, void (*traverse)(const VertTy&) = OutputVertex) const;
    void BFS_wholeGraph(void (*visit)(const VertTy&) = OutputVertex) const;

    /* Minimum Spanning Tree */

    //template<class VertTy, class WeightTy, WeightTy infinity>
    //friend WeightTy MST::Kruskal(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout);
    //template<class VertTy, class WeightTy, WeightTy infinity>
    //friend WeightTy MST::Prim(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout);
    //template<class VertTy, class WeightTy, WeightTy infinity>
    //friend WeightTy MST::ReverseDelete(const AdjListWUndirGraph<VertTy, WeightTy, infinity>& g, std::ostream* out = &std::cout);

    /* Output */

    void printAdjList(std::ostream& out = std::cout) const;
    void printVertices(std::ostream& out = std::cout) const;
    void printEdges(std::ostream& out = std::cout) const;
private:
    std::vector<VertTy> _vertices;
    std::vector<EdgeList> _adjList;
    sizet _edgeNum;

    indext indexOfVertex(const VertTy& vert) const {
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

    static void OutputVertex(const VertTy& vert) { std::cout << vert << " "; }

    void _dfs(indext fromIndex, std::vector<int>& visited, void (*visit)(const VertTy&) = nullptr) const;
    void _bfs(indext fromIndex, std::vector<int>& visited, void (*visit)(const VertTy&) = nullptr) const;

    //bool treeFindPath(indext prev, indext start, indext end, std::stack<MST_Edge>&) const;
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
    if (_vertices.empty()) { return false; }
    if (_vertices.size() == 1) { return true; }
    if (_edgeNum < _vertices.size() - 1) { return false; }
    // If the graph can be wholly traversed from one vertex, it is connected.
    std::vector<int> visited(_vertices.size(), 0);
    _bfs(0, visited, nullptr);
    return std::ranges::find(visited, 0) == visited.end();
}

template<class VertTy, class WeightTy, WeightTy infinity>
size_t AdjListWUndirGraph<VertTy, WeightTy, infinity>::numOfConnectedComponent() const {
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
const VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& to) const {
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    // Check if "to" is adjacent to "from".
    auto edgeIter = _adjList[fromIndex].begin();
    for (; edgeIter != _adjList[fromIndex].end(); edgeIter++) {
        if (edgeIter->toIndex == toIndex) {
            break;
        }
    }
    if (edgeIter == _adjList[fromIndex].end()) {
        throw EdgeNotFound();
    }
    // Move to the next adjacent vertex.
    ++edgeIter;
    if (edgeIter == _adjList[fromIndex].end()) {
        return nullptr;
    }
    indext nextIndex = edgeIter->toIndex;
    return &_vertices[nextIndex];
}

template<class VertTy, class WeightTy, WeightTy infinity>
VertTy* AdjListWUndirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& to) {
    auto const_this = const_cast<const Graph*>(this);
    return const_cast<VertTy*>(const_this->nextAdjVertex(from, to));
}

template<class VertTy, class WeightTy, WeightTy infinity>
WeightTy AdjListWUndirGraph<VertTy, WeightTy, infinity>::getWeight(const VertTy& from, const VertTy& to) const {
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    auto edgeIter = _adjList[fromIndex].begin();
    for (; edgeIter != _adjList[fromIndex].end(); edgeIter++) {
        if (edgeIter->toIndex == toIndex) {
            break;
        }
    }
    if (edgeIter != _adjList[fromIndex].end()) {
        return edgeIter->weight;
    }
    return infinity;
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
        for (auto edgeIter = _adjList[fromIndex].begin(); edgeIter != _adjList[fromIndex].end(); edgeIter++) {
            if (edgeIter->toIndex == vertIndex) {
                _adjList[fromIndex].erase(edgeIter);
                break;
            }
        }
    }
    indext lastIndex = _vertices.size() - 1;
    if (vertIndex != lastIndex) {
        // Replace the vertex to be deleted with the last vertex
        _vertices[vertIndex] = std::move(_vertices[lastIndex]);
        _adjList[vertIndex] = std::move(_adjList[lastIndex]);
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
    auto fromIter = _adjList[fromIndex].begin();
    for (; fromIter != _adjList[fromIndex].end(); fromIter++) {
        if (fromIter->toIndex == toIndex) {
            fromIter->weight = newWeight;
            break;
        }
    }
    if (fromIter == _adjList[fromIndex].end()) {
        throw EdgeNotFound();
    }

    // Modify the weight of the edge from "to" to "from".
    for (auto toIter = _adjList[toIndex].begin(); toIter != _adjList[toIndex].end(); toIter++) {
        if (toIter->toIndex == fromIndex) {
            toIter->weight = newWeight;
            return;
        }
    }
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
    auto fromIter = _adjList[fromIndex].begin();
    for (; fromIter != _adjList[fromIndex].end(); fromIter++) {
        if (fromIter->toIndex == toIndex) {
            throw EdgeAlreadyExists();
        }
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
    // Check if the edge exists.
    auto fromIter = _adjList[fromIndex].begin();
    for (; fromIter != _adjList[fromIndex].end(); fromIter++) {
        if (fromIter->toIndex == toIndex) {
            break;
        }
    }
    if (fromIter == _adjList[fromIndex].end()) {
        throw EdgeNotFound();
    }
    // Erase (from, to).
    _adjList[fromIndex].erase(fromIter);
    // Erase (to, from).
    for (auto toIter = _adjList[toIndex].begin(); toIter != _adjList[toIndex].end(); toIter++) {
        if (toIter->toIndex == fromIndex) {
            _adjList[toIndex].erase(toIter);
            break;
        }
    }
    _edgeNum--;
}

/* Look up */

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
_dfs(indext fromIndex, std::vector<int>& visited, void (*visit)(const VertTy&)) const {
    // Visit the current vertex:
    visited[fromIndex] = 1;
    if (visit != nullptr) {
        (*visit)(_adjList[fromIndex].value);
    }
    // Visit its adjacent vertices:
    for (const auto& edge : _adjList[fromIndex].edges) {
        if (visited[edge.vertIndex] == 0) {
            _dfs(edge.vertIndex, visited, visit);
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
_bfs(indext fromIndex, std::vector<int>& visited, void (*visit)(const VertTy&)) const {
    std::queue<indext> vertices;
    // Visit the starting vertex:
    visited[fromIndex] = 1;
    if (visit != nullptr) {
        (*visit)(_adjList[fromIndex].value);
    }
    vertices.push(fromIndex);
    while (!vertices.empty()) {
        indext curIndex = vertices.front();
        vertices.pop();
        // Visit its adjacent vertices:
        for (auto edge : _adjList[curIndex].edges) {
            indext adjIndex = edge.vertIndex;
            if (visited[adjIndex] == 0) {
                visited[adjIndex] = 1;
                if (visit != nullptr) {
                    (*visit)(_adjList[adjIndex].value);
                }
                vertices.push(adjIndex);
            }
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
DFS_from(const VertTy& start, void (*visit)(const VertTy&)) const {
    std::vector<int> visited(_adjList.size(), 0);
    // Find startVert:
    auto vertIt = std::ranges::find_if(_adjList, FindVert(start));
    if (vertIt == _adjList.end()) {
        throw VertexNotFound("startVert not found.");
    }
    indext fromIndex = vertIt - _adjList.begin();
    _dfs(fromIndex, visited, visit);
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
DFS_wholeGraph(void (*visit)(const VertTy&)) const {
    std::vector<int> visited(_adjList.size(), 0);
    for (indext vertIndex = 0; vertIndex < _adjList.size(); vertIndex++) {
        if (visited[vertIndex] == 0) {
            _dfs(vertIndex, visited, visit);
        }
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
BFS_from(const VertTy& start, void (*visit)(const VertTy&)) const {
    std::vector<int> visited(_adjList.size(), 0);
    // Find startVert:
    auto vertIt = std::ranges::find_if(_adjList, FindVert(start));
    if (vertIt == _adjList.end()) {
        throw VertexNotFound("startVert not found.");
    }
    indext fromIndex = vertIt - _adjList.begin();
    _bfs(fromIndex, visited, visit);
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::
BFS_wholeGraph(void (*visit)(const VertTy&)) const {
    std::vector<int> visited(_adjList.size(), 0);
    for (indext vertIndex = 0; vertIndex < _adjList.size(); vertIndex++) {
        if (visited[vertIndex] == 0) {
            _bfs(vertIndex, visited, visit);
        }
    }
}

///* Function required */
//
//template<class VertTy, class WeightTy, WeightTy infinity>
//bool AdjListWUndirGraph<VertTy, WeightTy, infinity>::treeFindPath(indext prev, indext start, indext end, std::stack<Edge>& prev) const {
//    if (start == end) { return true; }
//    for (const auto& e : _adjList[start].edges) {
//        if (e.vertIndex == prev) { continue; }
//        prev.emplace(start, e.vertIndex, e.weight);
//        if (treeFindPath(start, e.vertIndex, end, prev)) {
//            return true;
//        }
//        prev.pop();
//    }
//    return false;
//}

template<class VertTy, class WeightTy, WeightTy infinity>
bool AdjListWUndirGraph<VertTy, WeightTy, infinity>::hasUniqueMST() const {
    ////if (_adjList.empty()) {
    ////    throw EmptyGraph();
    ////}
    ////if (_adjList.size() == 1) { return true; }
    ////if (!this->connected()) {
    ////    throw GraphDisconnected();
    ////}
    ////// Use Kruskal algorithm to find an MST and store the discarded edges:
    ////DisjointSet vertSet(_adjList.size());
    ////std::priority_queue<MST_Edge, std::vector<MST_Edge>,
    ////    std::greater<MST_Edge>> minHeap;
    ////for (indext i = 0; i < _adjList.size() - 1; i++) {
    ////    for (const auto& e : _adjList[i].edges) {
    ////        if (i < e.vertIndex) {
    ////            minHeap.emplace(i, e.vertIndex, e.weight);
    ////        }
    ////    }
    ////}
    ////// Initialize another graph for MST:
    ////Graph MST;
    ////for (const auto& v : _adjList) {
    ////    MST.insertVertex(v.value);
    ////}
    ////// Find edges:
    ////std::vector<MST_Edge> discardedEdges;
    ////for (indext cnt = 0; cnt < _adjList.size() - 1;) {
    ////    MST_Edge curEdge = minHeap.top();
    ////    minHeap.pop();
    ////    int v1Root = vertSet.findRoot(curEdge.from);
    ////    int v2Root = vertSet.findRoot(curEdge.to);
    ////    if (v1Root != v2Root) {
    ////        vertSet.unite(v1Root, v2Root);
    ////        cnt++;
    ////        MST.insertEdge(MST._adjList[curEdge.from].value,
    ////            MST._adjList[curEdge.to].value, curEdge.weight);
    ////    } else {
    ////        discardedEdges.push_back(curEdge);
    ////    }
    ////}
    ////while (!minHeap.empty()) {
    ////    discardedEdges.push_back(minHeap.top());
    ////    minHeap.pop();
    ////}
    ////// Check if the weight of any discarded edge is greater than
    ////// other edges in the circle formed with the edge:
    ////std::stack<MST_Edge> prev;
    ////for (const auto& e : discardedEdges) {
    ////    MST.treeFindPath(-1, e.vert1, e.vert2, prev);
    ////    while (!prev.empty()) {
    ////        if (e.weight <= prev.top().weight) { return false; }
    ////        prev.pop();
    ////    }
    ////}
    return true;
}

/* Output */

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::printAdjList(std::ostream& out) const {
    for (indext fromIndex = 0; fromIndex < _vertices.size(); fromIndex++) {
        out << _vertices[fromIndex] << " | ";
        for (const auto& e : _adjList[fromIndex]) {
            out << _vertices[e.toIndex] << "(" << e.weight << ") -> ";
        }
        out << "end" << std::endl;
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjListWUndirGraph<VertTy, WeightTy, infinity>::printVertices(std::ostream& out) const {
    for (indext i = 0; i < _vertices.size(); i++) {
        out << "(" << (i + 1) << ") " << _vertices[i] << "\n";
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
