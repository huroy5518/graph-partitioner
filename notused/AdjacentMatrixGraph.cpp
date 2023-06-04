#include "graph.hpp"
#include <stddef.h>
#include <stdint.h>
#include <stdexcept>
#include "GraphDef.hpp"


AdjacentMatrixGraph::AdjacentMatrixGraph(size_t n, const int graph_type) {
    n_node = n;
    graph.resize(n + 1, std::vector<double>(n + 1));
    this->graph_type = graph_type;
}

AdjacentMatrixGraph::AdjacentMatrixGraph(const std::vector<std::vector<double>> &mat, const int graph_type){
    this->graph_type = graph_type;
    size_t num = mat.size();
    for(size_t i = 0; i < mat.size(); i ++) {
        if(num != mat[i].size()) {
            throw std::invalid_argument("Matrix Row and Column should be the same!!");
        }
    }
    if(graph_type == GRAPH_UNDIRECT) {
        for(size_t i = 0; i < mat.size(); i ++) {
            for(size_t j = 0; j < mat[i].size(); j ++) {
                if(mat[i][j] != mat[j][i]) {
                    throw std::invalid_argument("Undirect Graph should have symetric weight");
                }
            }
        }
    }
    n_node = num;
    graph = mat;
}
AdjacentMatrixGraph::AdjacentMatrixGraph(const std::vector<std::vector<double>> &&mat, const int graph_type) {
    size_t num = mat.size();
    this->graph_type = graph_type;
    for(size_t i = 0; i < mat.size(); i ++) {
        if(num != mat[i].size()) {
            throw std::invalid_argument("Matrix Row and Column should be the same!!");
        }
    }
    if(graph_type == GRAPH_UNDIRECT) {
        for(size_t i = 0; i < mat.size(); i ++) {
            for(size_t j = 0; j < mat[i].size(); j ++) {
                if(mat[i][j] != mat[j][i]) {
                    throw std::invalid_argument("Undirect Graph should have symetric weight");
                }
            }
        }
    }
    n_node = num;
    graph = mat;
}

AdjacentMatrixGraph::AdjacentMatrixGraph(const AdjacentMatrixGraph &ano_graph) {
    graph = ano_graph.graph;
    n_node = ano_graph.n_node;
    this->graph_type = ano_graph.graph_type;
}

AdjacentMatrixGraph::AdjacentMatrixGraph(const AdjacentMatrixGraph &&ano_graph) {
    graph = ano_graph.graph;
    n_node = ano_graph.n_node;
    this->graph_type = ano_graph.graph_type;
}

void AdjacentMatrixGraph::addEdge(const size_t V1, const size_t V2, const double weight) {
    if(graph.size() < V1 || graph.size() < V2) {
        size_t new_n_node = std::max(V1, V2);
        for(size_t i = 0; i < n_node; i ++) {
            graph[i].resize(new_n_node + 1, 0);
        }
        n_node = std::max(V1, V2);
        graph.resize(new_n_node, std::vector<double>(new_n_node + 1));
    }
    graph[V1][V2] = weight;
    if(graph_type == GRAPH_UNDIRECT) {
        graph[V2][V1] = weight;
    }
}

void AdjacentMatrixGraph::updateEdge(const size_t V1, const size_t V2, const double weight) {
    if(V1 > n_node || V2 > n_node) {
        throw std::out_of_range("Index should be in size range");
    }

    graph[V1][V2] = weight;
    if(graph_type == GRAPH_UNDIRECT) {
        graph[V1][V2] = weight;
    }
}

void AdjacentMatrixGraph::deleteEdge(const size_t V1, const size_t V2, const double weight) {
    if(V1 > n_node || V2 > n_node) {
        throw std::out_of_range("Index should be in size range");
    }

    graph[V1][V2] = weight;
    if(graph_type == GRAPH_UNDIRECT) {
        graph[V1][V2] = weight;
    }
}