#include "LDGPartitioner.hpp"
#include "AdjacentListGraph.hpp"
#include <algorithm>
#include <iostream>


LDGPartitioner::LDGPartitioner(const AdjacentListGraph &_G) {
    this->G = _G;
}

std::vector<size_t> LDGPartitioner::Part(size_t target_k) {
    if(target_k > G.nvert()) {
        throw std::invalid_argument("Number of partition should be less than the number of verteies");
    }
    std::vector<size_t> ret(target_k);
    // std::cout << "hello" << std::endl;

    std::cout << G.nvert() << std::endl;
    pid = std::vector<size_t>(G.nvert());
    balance_vertex_distribute = std::vector<double>(G.nvert());
    std::vector<size_t> order(G.nvert());
    for(size_t i = 0; i < G.nvert(); i ++) {
        order[i] = i;
    }

    // constant the algorithm
    const double C = 1e7;

    std::srand(time(NULL));

    std::random_shuffle(order.begin(), order.end());
    cur_parts = std::vector<std::unordered_set<size_t>>(target_k);

    // initial condition
    for(size_t i = 0; i < target_k; i ++) {
        cur_parts[i].clear();
        cur_parts[i].insert(order[i]);
        pid[order[i]] = i;
    }
    for(size_t i = target_k; i < G.nvert(); i ++) {
        size_t cur_vert = order[i];
        double cur_max = 0;
        for(size_t j = 0; j < target_k; j ++) {
            balance_vertex_distribute[j] = 1 - ((double)cur_parts[j].size() / C);
        }
        for(size_t j = 0; j < target_k; j ++) {
            size_t cnt = 0;
            std::vector<size_t> neighbor = this->G.neighbor(cur_vert);
            for(auto &ne: neighbor) {
                cnt += cur_parts[j].count(ne);
            }
            double cur = balance_vertex_distribute[j] * (double)cnt;
            if(cur_max < cur) {
                pid[cur_vert] = j;
                cur_max = cur;
            }
        }
        if(cur_max == 0) {
            pid[cur_vert] = rand() % target_k;
        }
        cur_parts[pid[cur_vert]].insert(cur_vert);
    }

    return pid;
}

std::vector<std::vector<size_t>> LDGPartitioner::PartNumpyMesh(size_t target_k) {
    if(!this->G.from_numpy()) {
        throw std::invalid_argument("Given graph isn't from numpy mesh");
    }
    std::vector<size_t> pids = Part(target_k);

    std::vector<std::vector<size_t>> ret(this->G.mesh_r(), std::vector<size_t>(this->G.mesh_c()));
    for(size_t i = 0; i < this->G.mesh_r(); i ++) {
        for(size_t j = 0; j < this->G.mesh_c(); j ++) {
            ret[i][j] = pids[i * this->G.mesh_c() + j];
        }
    }
    return ret;
}