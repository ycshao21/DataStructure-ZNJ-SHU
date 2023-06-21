#pragma once
#include<vector>
#include<algorithm>
#include<limits>
#include<ranges>
#include<iomanip>
#include"SquareMatrix.h"
#include"ShortestPath.h"
#include"../../Tools/MyExceptions.h"

template<class VertTy = int, class WeightTy = int, WeightTy infinity = std::numeric_limits<WeightTy>::max()>
class AdjMatWDirGraph
{
    using Graph = AdjMatWDirGraph<VertTy, WeightTy, infinity>;
    using sizet = size_t;
    using indext = size_t;
public:
    /* Constructors and Destructor */

    AdjMatWDirGraph(sizet vertNum = 0) :_vertices(vertNum), _adjMat(vertNum), _edgeNum(0) {}
    AdjMatWDirGraph(const std::vector<VertTy>& vertices);
    AdjMatWDirGraph(const Graph&) = default;
    Graph& operator=(const Graph&) = default;
    virtual ~AdjMatWDirGraph() = default;

    /* Status */

    bool empty() const { return _vertices.empty(); }
    sizet numOfVertices() const { return _vertices.size(); }
    sizet numOfEdges() const { return _edgeNum; }

    /* Element Access */

    sizet outDegree(const VertTy& from) const;
    sizet inDegree(const VertTy& to) const;
    sizet degree(const VertTy& vert) const { return outDegree(vert) + inDegree(vert); }

    const VertTy* firstAdjVertex(const VertTy& from) const;
    VertTy* firstAdjVertex(const VertTy& from);
    const VertTy* nextAdjVertex(const VertTy& from, const VertTy& after)const;
    VertTy* nextAdjVertex(const VertTy& from, const VertTy& after);

    WeightTy getWeight(const VertTy& from, const VertTy& to) const;
    WeightTy getInfinity() const { return infinity; }

    /* Modifier */

    void clear() { _vertices.clear(), _adjMat.resize(0), _edgeNum = 0; }
    void setVertex(const VertTy& oldVert, const VertTy& newVert) { _vertices[indexOfVertex(oldVert)] = newVert; }
    void insertVertex(const VertTy& vert);
    void eraseVertex(const VertTy& vert);
    void setWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight);
    void insertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight);
    void eraseEdge(const VertTy& from, const VertTy& to);

    /* Shortest Path Algorithm */

    template<class VertTy, class WeightTy, WeightTy infinity>
    friend void ShortestPath::Dijkstra(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out);
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend void ShortestPath::BellmanFord(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out);
    template<class VertTy, class WeightTy, WeightTy infinity>
    friend void ShortestPath::FloydWarshall(const AdjMatWDirGraph<VertTy, WeightTy, infinity>& g,
        const VertTy& source, const VertTy& end, std::ostream* out);

    /* Output */

    void printAdjMatrix(std::ostream& out = std::cout) const;
    void printEdges(std::ostream& out = std::cout) const;
private:
    std::vector<VertTy> _vertices;  // Vertices in the graph.
    SquareMatrix<WeightTy, infinity> _adjMat;  // Adjacent matrix of the graph.
    sizet _edgeNum;  // Number of edges in the graph.

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
};

template<class VertTy, class WeightTy, WeightTy infinity>
AdjMatWDirGraph<VertTy, WeightTy, infinity>::AdjMatWDirGraph(const std::vector<VertTy>& vertices) {
    // Check if there are duplicate vertices.
    for (const auto& vert : vertices) {
        if (std::ranges::find(_vertices, vert) == _vertices.end()) {
            _vertices.push_back(vert);
        }
    }
    _adjMat.resize(_vertices.size());
    _edgeNum = 0;
}

template<class VertTy, class WeightTy, WeightTy infinity>
const VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::firstAdjVertex(const VertTy& from) const {
    indext fromIndex = indexOfVertex(from);
    for (indext toIndex = 0; toIndex < _vertices.size(); toIndex++) {
        if (_adjMat[fromIndex][toIndex] != infinity) {
            return &_vertices[toIndex];
        }
    }
    return nullptr;
}

template<class VertTy, class WeightTy, WeightTy infinity>
VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::firstAdjVertex(const VertTy& from) {
    auto const_this = const_cast<const Graph*>(this);
    return const_cast<VertTy*>(const_this->firstAdjVertex(from));
}

template<class VertTy, class WeightTy, WeightTy infinity>
const VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& after) const {
    indext fromIndex = indexOfVertex(from);
    indext afterIndex = indexOfVertex(after);
    for (indext toIndex = afterIndex + 1; toIndex < _vertices.size(); toIndex++) {
        if (_adjMat[fromIndex][toIndex] != infinity) {
            return &_vertices[toIndex];
        }
    }
    return nullptr;
}

template<class VertTy, class WeightTy, WeightTy infinity>
VertTy* AdjMatWDirGraph<VertTy, WeightTy, infinity>::nextAdjVertex(const VertTy& from, const VertTy& after) {
    auto const_this = const_cast<const Graph*>(this);
    return const_cast<VertTy*>(const_this->nextAdjVertex(from, after));
}

template<class VertTy, class WeightTy, WeightTy infinity>
auto AdjMatWDirGraph<VertTy, WeightTy, infinity>::outDegree(const VertTy& from) const -> sizet {
    indext fromIndex = indexOfVertex(from);
    sizet outD = 0;
    for (const auto& w : _adjMat[fromIndex]) {
        if (w != infinity) {
            outD++;
        }
    }
    return outD;
}

template<class VertTy, class WeightTy, WeightTy infinity>
auto AdjMatWDirGraph<VertTy, WeightTy, infinity>::inDegree(const VertTy& to) const -> sizet {
    indext toIndex = indexOfVertex(to);
    int inD = 0;
    for (int fromIndex = 0; fromIndex < _vertices.size(); fromIndex++) {
        if (_adjMat[fromIndex][toIndex] != infinity) {
            inD++;
        }
    }
    return inD;
}

template<class VertTy, class WeightTy, WeightTy infinity>
WeightTy AdjMatWDirGraph<VertTy, WeightTy, infinity>::getWeight(const VertTy& from, const VertTy& to) const {
    indexOfVertex(from);
    indexOfVertex(to);
    return _adjMat[from][to];
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::insertVertex(const VertTy& vert) {
    if (std::ranges::find(_vertices, vert) != _vertices.end()) {
        throw VertexAlreadyExists();
    }
    _vertices.push_back(vert);
    _adjMat.addOneDimension();
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::eraseVertex(const VertTy& vert) {
    indext vertIndex = indexOfVertex(vert);
    for (indext i = 0; i < _vertices.size(); i++) {
        if (_adjMat[vertIndex][i] != infinity) {
            _edgeNum--;
        }
        if (_adjMat[i][vertIndex] != infinity) {
            _edgeNum--;
        }
    }
    indext lastIndex = _vertices.size() - 1;
    if (vertIndex != lastIndex) {
        // Replace the vertex to be deleted with the last vertex
        _vertices[vertIndex] = std::move(_vertices[lastIndex]);
        _adjMat[vertIndex] = std::move(_adjMat[lastIndex]);
        for (int i = 0; i < lastIndex; i++) {
            _adjMat[i][vertIndex] = std::move(_adjMat[i][lastIndex]);
        }
        _adjMat[vertIndex][vertIndex] = infinity;
    }
    _adjMat.removeOneDimension();
    _vertices.pop_back();
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::setWeight(const VertTy& from, const VertTy& to, const WeightTy& newWeight) {
    if (newWeight == infinity) {
        throw IllegalParameterValue("Weight should not be infinity!");
    }
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (_adjMat[fromIndex][toIndex] == infinity) {
        throw EdgeNotFound();
    }
    _adjMat[fromIndex][toIndex] = newWeight;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::insertEdge(const VertTy& from, const VertTy& to, const WeightTy& weight) {
    if (weight == infinity) {
        throw IllegalParameterValue("Weight cannot be infinity.");
    }
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (fromIndex == toIndex) {
        throw IllegalParameterValue("Loop is not allowed.");
    }
    if (_adjMat[fromIndex][toIndex] != infinity) {
        throw EdgeAlreadyExists();
    }
    _adjMat[fromIndex][toIndex] = weight;
    _edgeNum++;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::eraseEdge(const VertTy& from, const VertTy& to) {
    indext fromIndex = indexOfVertex(from),
        toIndex = indexOfVertex(to);
    if (_adjMat[fromIndex][toIndex] == infinity) {
        throw EdgeNotFound();
    }
    _adjMat[fromIndex][toIndex] = infinity;
    _edgeNum--;
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::printAdjMatrix(std::ostream& out) const {
    if (_vertices.empty()) { return; }
    sizet width = 5;
    out << std::setw(width) << "";
    for (const auto& v : _vertices) {
        out << std::setw(width) << v << " ";
    }
    out << std::endl;

    out << std::setw(width) << "";
    for (const auto& v : _vertices) {
        out << "______";
    }
    out << std::endl;
    for (indext i = 0; i < _adjMat.size(); i++) {
        out << std::setw(width - 1) << _vertices[i] << "|";
        for (const auto& w : _adjMat[i]) {
            if (w == infinity) {
                out << std::setw(width) << "inf" << " ";
            } else {
                out << std::setw(width) << w << " ";
            }
        }
        out << std::endl;
    }
}

template<class VertTy, class WeightTy, WeightTy infinity>
void AdjMatWDirGraph<VertTy, WeightTy, infinity>::printEdges(std::ostream& out) const {
    sizet edgeCnt = 0;
    for (indext fromIndex = 0; fromIndex < _adjMat.size(); fromIndex++) {
        for (indext toIndex = 0; toIndex < _adjMat[fromIndex].size(); toIndex++) {
            if (_adjMat[fromIndex][toIndex] != infinity) {
                edgeCnt++;
                out << "(" << edgeCnt << ") "
                    << "<" << _vertices[fromIndex] << ", " << _vertices[toIndex] << ">: "
                    << _adjMat[fromIndex][toIndex] << "\n";
            }
        }
    }
}
