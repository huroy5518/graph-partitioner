#ifndef __ADJACENT_LIST_GRAPH_H
#define __ADJACENT_LIST_GRAPH_H
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <vector>
#include <stddef.h>
#include <stdint.h>
#include <stdexcept>
#include "GraphDef.hpp"
#include "Mesh.hpp"


// namespace py=pybind11;

class Edge {
public:
    size_t u, v;
    double weight;
    Edge() {
        u = 0;
        v = 0;
        weight = 0.0;
    }
    Edge(size_t _u, size_t _v, double _weight = 0.0) {
        u = _u;
        v = _v;
        weight = _weight;
    }
    Edge(const Edge & ano) {
        u = ano.u;
        v = ano.v;
        weight = ano.weight;
    }
    Edge(const Edge && ano) {
        u = ano.u;
        v = ano.v;
        weight = ano.weight;
    }
    Edge & operator=(const Edge &edge) {
        if(this != &edge) {
            this->u = edge.u;
            this->v = edge.v;
            this->weight = edge.weight;
        }
        return *this;
    }
};


class AdjacentListGraph {
    private:
        std::vector<Edge> edges;
        std::vector<std::vector<size_t>> graph;
        std::map<std::pair<size_t, size_t>, double> edge_weight;
        size_t n_vert;
        int graph_type;
        bool from_numpy_mesh;
        size_t numpy_mesh_r;
        size_t numpy_mesh_c;
    public:
        AdjacentListGraph() = default;
        AdjacentListGraph(size_t n);
        AdjacentListGraph(const std::vector<std::vector<double>> &mat);
        AdjacentListGraph(const std::vector<std::vector<double>> &&mat); 
        AdjacentListGraph(const AdjacentListGraph &ano_graph);
        AdjacentListGraph(const AdjacentListGraph &&ano_graph);
        AdjacentListGraph(const MeshGrid &grid);
        AdjacentListGraph(const MeshGrid &&grid);
        AdjacentListGraph(pybind11::array_t<double> &x, pybind11::array_t<double> &y, bool sparse=false);

        void addEdge(const size_t V1, const size_t V2, double weight = 1.0);
        size_t nvert();
        AdjacentListGraph & operator=(const AdjacentListGraph &G);
        std::vector<size_t> neighbor(size_t ne);
        const std::vector<Edge> & edge();
        double getEdgeWeight(const size_t v1, const size_t v2);
        const std::vector<size_t> & edgeId(const size_t v);
        void addEdgeList(const std::vector<std::pair<size_t, size_t>>&);
        void addEdgeList(const std::vector<std::tuple<const size_t, const size_t, double>> &edge);
        bool from_numpy() {
            return this->from_numpy_mesh;
        }
        size_t mesh_r() {
            return this->numpy_mesh_r;
        }
        size_t mesh_c() {
            return this->numpy_mesh_c;
        }
};
#endif