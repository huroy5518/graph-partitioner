#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "AdjacentListGraph.hpp"
#include "GraphDef.hpp"
#include <iostream>


AdjacentListGraph::AdjacentListGraph(size_t n) {
    this->from_numpy_mesh = false;
    graph.resize(n, std::vector<size_t>());
    this->n_vert = n;
}

AdjacentListGraph::AdjacentListGraph(const std::vector<std::vector<double>> &mat) {
    this->from_numpy_mesh = false;
    size_t num = mat.size();
    for(size_t i = 0; i < mat.size(); i ++) {
        if(num != mat[i].size()) {
            throw std::invalid_argument("Matrix Row and Column should be the same!!");
        }
        for(size_t j = 0; j < mat[i].size(); j ++) {
            if(mat[i][j] != mat[j][i]) {
                throw std::invalid_argument("Undirect Graph should have symetric weight");
            }
        }
    }
    for(size_t i = 0; i < mat.size(); i ++) {
        for(size_t j = 0; j < mat[i].size(); j ++) {
            if(abs(mat[i][j]) > EPS) {
                graph[i].push_back(edges.size());
                edges.push_back({i, j, mat[i][j]});
                edge_weight[{i, j}] = mat[i][j];
                // graph[i].push_back(j);
            }
        }
    }
    n_vert = num;
}
AdjacentListGraph::AdjacentListGraph(const std::vector<std::vector<double>> &&mat) {
    this->from_numpy_mesh = false;
    size_t num = mat.size();
    for(size_t i = 0; i < mat.size(); i ++) {
        if(num != mat[i].size()) {
            throw std::invalid_argument("Matrix Row and Column should be the same!!");
        }
        for(size_t j = 0; j < mat[i].size(); j ++) {
            throw std::invalid_argument("Undirect Graph should have symetric weight");
        }
    }
    for(size_t i = 0; i < mat.size(); i ++) {
        for(size_t j = 0; j < mat[i].size(); j ++) {
            if(abs(mat[i][j]) > EPS) {
                graph[i].push_back(edges.size());
                edge_weight[{i, j}] = mat[i][j];
                edges.push_back({i, j, mat[i][j]});
                // graph[i].push_back(j);
            }
        }
    }
    n_vert = num;
}
AdjacentListGraph::AdjacentListGraph(const AdjacentListGraph &ano_graph) {
    this->n_vert = ano_graph.n_vert;
    this->graph = ano_graph.graph;
    this->from_numpy_mesh = ano_graph.from_numpy_mesh;
    this->edge_weight = ano_graph.edge_weight;
    this->numpy_mesh_c = ano_graph.numpy_mesh_c;
    this->numpy_mesh_r = ano_graph.numpy_mesh_r;
    // this->edges = ano_graph.edges;
}
AdjacentListGraph::AdjacentListGraph(const AdjacentListGraph &&ano_graph) {
    this->from_numpy_mesh = ano_graph.from_numpy_mesh;
    this->n_vert = ano_graph.n_vert;
    this->graph = ano_graph.graph;
    this->edge_weight = ano_graph.edge_weight;
    this->numpy_mesh_c = ano_graph.numpy_mesh_c;
    this->numpy_mesh_r = ano_graph.numpy_mesh_r;
    // this->edges = ano_graph.edges;
}

AdjacentListGraph::AdjacentListGraph(pybind11::array_t<double> &x, pybind11::array_t<double> &y, bool sparse) {
    this->from_numpy_mesh = true;
    this->graph_type = GRAPH_UNDIRECT;
    if(x.ndim() != y.ndim()) {
        throw std::invalid_argument("X and Y should have same dimension");
    }

    if(x.ndim() != 2 && y.ndim() != 2) {
        throw std::invalid_argument("2-dimensional Mesh Grid should have ndim=2");
    }

    if(sparse) {
        this->numpy_mesh_c = x.shape(1);
        this->numpy_mesh_r = y.shape(0);
        this->n_vert = x.shape(1) * y.shape(0);
        this->graph = std::vector<std::vector<size_t>>(n_vert, std::vector<size_t>());
        for(int i = 0; i < y.shape(0); i ++) {
            for(int j = 0; j < x.shape(1); j ++) {
                if(i) {
                    addEdge((i - 1) * x.shape(1) + j + 1, (i) * x.shape(1) + j + 1);
                }
                if(j) {
                    addEdge((i) * x.shape(1) + (j - 1) + 1, (i) * x.shape(1) + (j) + 1);
                }
            }
        }
        return;
    }
    this->n_vert = x.shape(0) * x.shape(1);
    // label 2d mesh grid 
    this->numpy_mesh_c = x.shape(1);
    this->numpy_mesh_r = x.shape(0);
    this->graph = std::vector<std::vector<size_t>>(n_vert, std::vector<size_t>());
    for(int i = 0; i < x.shape(0); i ++) {
        for(int j = 0; j < x.shape(1); j ++) {
            if(i) {
                addEdge((i - 1) * x.shape(1) + j + 1, (i) * x.shape(1) + j + 1);
            }
            if(j) {
                addEdge((i) * x.shape(1) + (j - 1) + 1, (i) * x.shape(1) + (j) + 1);
            }
        }
    }
}

void AdjacentListGraph::addEdge(const size_t V1, const size_t V2, double weight) {
    if(V1 > n_vert || V2 > n_vert) {
        throw std::out_of_range("Index should be in size range");
    }
    // this->graph[V1 - 1].push_back(V2 - 1);
    this->graph[V1 - 1].push_back(edges.size());
    this->edges.push_back({V1 - 1, V2 - 1, weight});
    edge_weight[{V1 - 1, V2 - 1}] = weight;
    if(this->graph_type == GRAPH_UNDIRECT) {
        edge_weight[{V2 - 1, V1 - 1}] = weight;
        this->graph[V2 - 1].push_back(edges.size());
        this->edges.push_back({V2 - 1, V1 - 1, weight});
        // this->graph[V2 - 1].push_back(V1 - 1);
    }
}

AdjacentListGraph & AdjacentListGraph::operator=(const AdjacentListGraph &G) {
    if(this != &G) {
        this->from_numpy_mesh = G.from_numpy_mesh;
        this->numpy_mesh_c = G.numpy_mesh_c;
        this->numpy_mesh_r = G.numpy_mesh_r;
        this->n_vert = G.n_vert;
        this->graph = G.graph;
        this->graph_type = G.graph_type;
        this->edges = G.edges;
        this->edge_weight = std::map<std::pair<size_t, size_t>, double>(G.edge_weight);
    }
    return *this;
}

size_t AdjacentListGraph::nvert() {
    return this->n_vert;
}

std::vector<size_t> AdjacentListGraph::neighbor(size_t ne) {
    std::vector<size_t> ret;
    for(auto &i : this->graph[ne]) {
        ret.push_back(this->edges[i].v);
    }
    return ret;
}

const std::vector<Edge>& AdjacentListGraph::edge() {
    return this->edges;
}

double AdjacentListGraph::getEdgeWeight(const size_t v1, const size_t v2) {
    if(this->edge_weight.find({v1, v2}) == this->edge_weight.end()) {
        return 0.0;
    }
    return this->edge_weight[{v1, v2}];
}

const std::vector<size_t> & AdjacentListGraph::edgeId(const size_t v) {
    return this->graph[v];
}
void AdjacentListGraph::addEdgeList(const std::vector<std::pair<size_t, size_t>> &edge) {
    bool resize = false;
    for(auto &i: edge) {
        if(this->n_vert < i.first) {
            this->n_vert = i.first;
            resize = true;
        }

        if(this->n_vert < i.second) {
            this->n_vert = i.second;
            resize = true;
        }
    }
    if(resize) {
        this->graph.resize(this->n_vert);
    }
    for(auto &i : edge) {
        addEdge(i.first, i.second);
    }
}

void AdjacentListGraph::addEdgeList(const std::vector<std::tuple<const size_t, const size_t, double>> &edge){
    bool resize = false;
    for(auto &i : edge) {
        auto [u, v, w] = i;
        if(this->n_vert < u) {
            this->n_vert = u;
            resize = true;
        }

        if(this->n_vert < v) {
            this->n_vert = v;
            resize = true;
        }
    }
    if(resize) {
        this->graph.resize(this->n_vert);
    }
    for(auto &i : edge) {
        auto [u, v, w] = i;
        addEdge(u, v, w);
    }
}