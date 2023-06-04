#ifndef __KERNIGHANLIN_FAST_PARTITIONER_H
#define __KERNIGHANLIN_FAST_PARTITIONER_H
#define KL_MAX_ITER 100

#include "AdjacentListGraph.hpp"
#include <vector>

class KernighanLinPartitionerFast {
    private:
        AdjacentListGraph G;
        std::vector<size_t> pid;

        bool KLNew(size_t p1, size_t p2);
    public:
        KernighanLinPartitionerFast(const AdjacentListGraph &_G);
        std::vector<size_t> Part(size_t target_k, size_t max_iter = 10);
        std::vector<std::vector<size_t>> PartNumpyMesh(size_t target_k, size_t max_iter = 10);
};

#endif