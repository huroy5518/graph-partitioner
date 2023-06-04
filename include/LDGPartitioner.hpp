#ifndef __LDGPARTITIONER_H
#define __LDGPARTITIONER_H

#include "AdjacentListGraph.hpp"
#include <unordered_set>

class LDGPartitioner {
    private:
        AdjacentListGraph G;
        std::vector<std::unordered_set<size_t>> cur_parts;
        std::vector<size_t> pid;
        std::vector<double> balance_vertex_distribute;
    public:
        LDGPartitioner(const AdjacentListGraph &G);
        std::vector<size_t> Part(size_t target_k);
        std::vector<std::vector<size_t>> PartNumpyMesh(size_t target_k);
};
#endif