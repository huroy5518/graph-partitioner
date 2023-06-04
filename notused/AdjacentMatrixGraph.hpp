#ifndef __ADJACENT_MATRIX_GRAPH_H
#define __ADJACENT_MATRIX_GRAPH_H

#include <stdint.h>
#include <vector>
#include <stdexcept>
#include <stddef.h>
#include "GraphDef.hpp"

class AdjacentMatrixGraph {
    private:
        std::vector<std::vector<double>> graph;
        size_t n_node;
        int graph_type;
    public:
        AdjacentMatrixGraph() = default;
        AdjacentMatrixGraph(size_t n, const int graph_type = GRAPH_UNDIRECT);
        AdjacentMatrixGraph(const std::vector<std::vector<double>> &mat, const int graph_type = GRAPH_UNDIRECT);
        AdjacentMatrixGraph(const std::vector<std::vector<double>> &&mat, const int graph_type = GRAPH_UNDIRECT); 
        AdjacentMatrixGraph(const AdjacentMatrixGraph &ano_graph);
        AdjacentMatrixGraph(const AdjacentMatrixGraph &&ano_graph);


        void addEdge(const size_t V1, const size_t V2, const double weight = 0.0);
        void updateEdge(const size_t V1, const size_t V2, const double weight = 0.0);
        void deleteEdge(const size_t V1, const size_t V2, const double weight = 0.0);
};

#endif