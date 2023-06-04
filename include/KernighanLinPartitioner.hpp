#ifndef __KERNIGHANLIN_PARTITIONER_H
#define __KERNIGHANLIN_PARTITIONER_H
#define KL_MAX_ITER 100

#include "AdjacentListGraph.hpp"
#include <vector>

class KernighanLinPartitioner {
    private:
        AdjacentListGraph G;
        std::vector<size_t> pid;
        std::vector<std::vector<size_t>> cur_part;
        std::vector<std::vector<double>> dval;
        std::set<std::pair<size_t, size_t>> exchanged;
        // void computeDvalue(std::vector<std::unordered_set<size_t>> &part1, std::vector<std::unordered_set<size_t>> &part2);
        bool KL(size_t p1, size_t p2);
        bool KLNew(size_t p1, size_t p2);
        void initDval();
        void computeDvalue();
        void updateDvalue(size_t, size_t);
        void changePart(size_t, size_t);
    public:
        KernighanLinPartitioner(const AdjacentListGraph &_G);
        std::vector<size_t> Part(size_t target_k, size_t max_iter = 10);
        std::vector<std::vector<size_t>> PartNumpyMesh(size_t target_k, size_t max_iter = 10);
};

#endif