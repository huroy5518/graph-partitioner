#include "KernighanLinPartitionerFast.hpp"
#include <iostream>
#include <queue>
#include <set>

KernighanLinPartitionerFast::KernighanLinPartitionerFast(const AdjacentListGraph &_G) {
    this->G = _G;
}

bool KernighanLinPartitionerFast::KLNew(size_t p1, size_t p2) {
    // std::priority_queue<double, std::vector<double>, std::greater<double>> costp1;
    // std::priority_queue<double, std::vector<double>, std::greater<double>> costp2;
    std::set<std::pair<double, size_t>> costs[2];
    std::vector<std::set<std::pair<double, size_t>>::iterator> head(this->G.nvert());

    size_t max_iter = 100;

    bool ret = false;

    const std::vector<Edge> &edges = this->G.edge();
    auto _update_costs = [&](size_t p, size_t vid) {
        const std::vector<size_t> &edge_id = this->G.edgeId(vid);
        for(auto &i : edge_id) {
            size_t v = edges[i].v;
            double weight = edges[i].weight;
            if(pid[v] != p1 && pid[v] != p2) continue;
            size_t id = 0;
            if(pid[v] == p2) {
                id = 1;
            }
            double new_val;
            if(head[v] != costs[id].end()) {
                std::pair<double, size_t> cur = *(head[v]);
                new_val = cur.first;
                if(pid[v] == p) {
                    new_val -= 2 * weight;
                } else {
                    new_val += 2 * weight;
                }
                costs[id].erase(head[v]);
                head[v] = costs[id].insert({new_val, v}).first;
            } 

        }
    };

    costs[0].clear();
    costs[1].clear();

    while(max_iter) {
        for(size_t i = 0; i < this->G.nvert(); i ++) {
            if(pid[i] != p1 && pid[i] != p2) {
                continue;
            }
            const std::vector<size_t> &edge_id = this->G.edgeId(i);
            double cost_u = 0;
            for(auto &j : edge_id) {
                if(pid[edges[j].v] != p1 && pid[edges[j].v] != p2) {
                    continue;
                }

                if(pid[edges[j].v] == pid[edges[j].u]) {
                    cost_u += edges[j].weight;
                } else {
                    cost_u -= edges[j].weight;
                }
            }
            size_t id = 0;
            if(pid[i] == p2) id = 1;
            head[i] = costs[id].insert({cost_u, i}).first;

        }
        std::vector<std::pair<double, std::pair<size_t, size_t>>> upd;
        double tot_cost = 0;
        while(costs[0].size() && costs[1].size()) {
            std::pair<double, size_t> cur = *(costs[0].begin());
            size_t u = cur.second;
            
            tot_cost += cur.first;
            head[cur.second] = costs[0].end();
            costs[0].erase(costs[0].begin());
            _update_costs(0, cur.second);

            cur = *(costs[1].begin());
            size_t v = cur.second;
            tot_cost += cur.first;
            head[cur.second] = costs[1].end();
            costs[1].erase(costs[1].begin());
            _update_costs(1, cur.second);
            upd.push_back({tot_cost, {u, v}});
        }
        double best_val = 100000;
        size_t best_idx = 0;
        for(size_t i = 0; i < upd.size(); i ++) {
            if(upd[i].first < best_val) {
                best_val = upd[i].first;
                best_idx = i;
            }
        }
        if(best_val > 0) {
            break;
        }
        for(size_t i = 0; i < best_idx; i ++) {
            std::pair<size_t, size_t> swp = upd[i].second;
            size_t tmp = pid[swp.first];
            pid[swp.first] = pid[swp.second];
            pid[swp.second] = tmp;
        }
        max_iter -= 1;
    }
    return ret;
}


std::vector<size_t> KernighanLinPartitionerFast::Part(size_t target_k, size_t max_iter) {
    size_t n_vert = this->G.nvert();
    this->pid = std::vector<size_t>(n_vert);

    size_t n_vert_part = (n_vert + target_k - 1) / target_k;
    for(size_t i = 0; i < n_vert; i ++) {
        this->pid[i] = (i / n_vert_part);
    }
    std::srand(time(NULL));
    std::random_shuffle(this->pid.begin(), this->pid.end());
    // return this->pid;

    

    for(int i = 0; i < max_iter; i ++) {
        bool improve = false;
        for(size_t j = 0; j < target_k; j ++) {
            for(size_t k = j + 1; k < target_k; k ++) {
                improve |= KLNew(j, k);
            }
        }
        if(!improve) break;
    }
    return this->pid;
}


std::vector<std::vector<size_t>> KernighanLinPartitionerFast::PartNumpyMesh(size_t target_k, size_t max_iter) {
    if(!this->G.from_numpy()) {
        throw std::invalid_argument("Given graph isn't from numpy mesh");
    }
    std::vector<size_t> pids = Part(target_k, max_iter);

    std::vector<std::vector<size_t>> ret(this->G.mesh_r(), std::vector<size_t>(this->G.mesh_c()));
    for(size_t i = 0; i < this->G.mesh_r(); i ++) {
        for(size_t j = 0; j < this->G.mesh_c(); j ++) {
            ret[i][j] = pids[i * this->G.mesh_c() + j];
        }
    }
    return ret;
}