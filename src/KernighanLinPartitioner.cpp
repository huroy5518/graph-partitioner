#include "KernighanLinPartitioner.hpp"
#include <iostream>
#include <queue>
#include <set>

KernighanLinPartitioner::KernighanLinPartitioner(const AdjacentListGraph &_G) {
    this->G = _G;
}

void KernighanLinPartitioner::initDval() {
    for(int i = 0; i < this->dval.size(); i ++) {
        for(int j = 0; j < this->dval[i].size(); j ++) {
            this->dval[i][j] = 0.0;
        }
    }
}

void KernighanLinPartitioner::computeDvalue() {
    initDval();
    for(auto &i : this->G.edge()) {
        size_t u = i.u;
        size_t v = i.v;
        double weight = i.weight;

        if(pid[u] == pid[v]) {
            dval[u][pid[v]] -= weight;
            dval[v][pid[u]] -= weight;
        } else {
            dval[u][pid[v]] += weight;
            dval[v][pid[u]] += weight;
        }
    }

}

void KernighanLinPartitioner::updateDvalue(size_t v1, size_t v2) {
    for(auto &i : cur_part[pid[v1]]) {
        dval[i][pid[v1]] += 2 * this->G.getEdgeWeight(i, v1);
        dval[i][pid[v2]] -= 2 * this->G.getEdgeWeight(i, v2);
    }

    for(auto &i : cur_part[pid[v2]]) {
        dval[i][pid[v2]] += 2 * this->G.getEdgeWeight(i, v2);
        dval[i][pid[v1]] -= 2 * this->G.getEdgeWeight(i, v1);
    }
}

void KernighanLinPartitioner::changePart(size_t v1, size_t v2) {


    this->cur_part[pid[v1]].erase(std::find(this->cur_part[pid[v1]].begin(), this->cur_part[pid[v1]].end(), v1));
    this->cur_part[pid[v2]].erase(std::find(this->cur_part[pid[v2]].begin(), this->cur_part[pid[v2]].end(), v2));
    size_t tmp = pid[v1];
    pid[v1] = pid[v2];
    pid[v2] = tmp;
    this->cur_part[pid[v1]].push_back(v1);
    this->cur_part[pid[v2]].push_back(v2);

}


// bool KernighanLinPartitioner::KLNew(size_t p1, size_t p2) {
//     // std::priority_queue<double, std::vector<double>, std::greater<double>> costp1;
//     // std::priority_queue<double, std::vector<double>, std::greater<double>> costp2;
//     std::set<std::pair<double, size_t>> costs[2];
//     std::vector<std::set<std::pair<double, size_t>>::iterator> head(this->G.nvert());

//     size_t max_iter = 100;

//     bool ret = false;

//     const std::vector<Edge> &edges = this->G.edge();
//     auto _update_costs = [&](size_t p, size_t vid) {
//         const std::vector<size_t> &edge_id = this->G.edgeId(vid);
//         for(auto &i : edge_id) {
//             size_t v = edges[i].v;
//             double weight = edges[i].weight;
//             if(pid[v] != p1 && pid[v] != p2) continue;
//             size_t id = 0;
//             if(pid[v] == p2) {
//                 id = 1;
//             }
//             double new_val;
//             if(head[v] != costs[id].end()) {
//                 std::pair<double, size_t> cur = *(head[v]);
//                 new_val = cur.first;
//                 if(pid[v] == p) {
//                     new_val -= 2 * weight;
//                 } else {
//                     new_val += 2 * weight;
//                 }
//                 costs[id].erase(head[v]);
//                 head[v] = costs[id].insert({new_val, v}).first;
//             } 

//         }
//     };

//     costs[0].clear();
//     costs[1].clear();

//     while(max_iter) {
//         for(size_t i = 0; i < this->G.nvert(); i ++) {
//             if(pid[i] != p1 && pid[i] != p2) {
//                 continue;
//             }
//             const std::vector<size_t> &edge_id = this->G.edgeId(i);
//             double cost_u = 0;
//             for(auto &j : edge_id) {
//                 if(pid[edges[j].v] != p1 && pid[edges[j].v] != p2) {
//                     continue;
//                 }

//                 if(pid[edges[j].v] == pid[edges[j].u]) {
//                     cost_u += edges[j].weight;
//                 } else {
//                     cost_u -= edges[j].weight;
//                 }
//             }
//             size_t id = 0;
//             if(pid[i] == p2) id = 1;
//             head[i] = costs[id].insert({cost_u, i}).first;

//         }
//         std::vector<std::pair<double, std::pair<size_t, size_t>>> upd;
//         double tot_cost = 0;
//         while(costs[0].size() && costs[1].size()) {
//             std::pair<double, size_t> cur = *(costs[0].begin());
//             size_t u = cur.second;
            
//             tot_cost += cur.first;
//             head[cur.second] = costs[0].end();
//             costs[0].erase(costs[0].begin());
//             _update_costs(0, cur.second);

//             cur = *(costs[1].begin());
//             size_t v = cur.second;
//             tot_cost += cur.first;
//             head[cur.second] = costs[1].end();
//             costs[1].erase(costs[1].begin());
//             _update_costs(1, cur.second);
//             upd.push_back({tot_cost, {u, v}});
//         }
//         double best_val = 100000;
//         size_t best_idx = 0;
//         for(size_t i = 0; i < upd.size(); i ++) {
//             if(upd[i].first < best_val) {
//                 best_val = upd[i].first;
//                 best_idx = i;
//             }
//         }
//         if(best_val > 0) {
//             break;
//         }
//         for(size_t i = 0; i < best_idx; i ++) {
//             std::pair<size_t, size_t> swp = upd[i].second;
//             size_t tmp = pid[swp.first];
//             pid[swp.first] = pid[swp.second];
//             pid[swp.second] = tmp;
//         }
//         max_iter -= 1;
//     }
//     return ret;
// }

bool KernighanLinPartitioner::KL(size_t p1, size_t p2) {
    std::vector<bool> skip(this->G.nvert(), false);
    std::vector<bool> outerskip(this->G.nvert(), false);

    size_t tot_size = cur_part[p1].size() + cur_part[p2].size();
    // std::cout << "Hello" << std::endl;
    size_t tot_iter = tot_size >> 1;

    double max_g = -1000000;

    size_t a, b;


    std::vector<size_t> alist;

    std::vector<size_t> blist;

    size_t max_iter = 15;
    bool ret = false;
    while (max_iter) {
        alist.clear();
        blist.clear();
        computeDvalue();
        double max_g = -1000000;
        std::fill(skip.begin(), skip.end(), false);
        for(size_t k = 0; k < tot_iter; k ++) {
            max_g = -100000;
            for(auto &i : cur_part[p1]) {
                for(auto &j : cur_part[p2]) {
                    // if(this->exchanged[i][j])
                    if(skip[i] || skip[j] || outerskip[i] || outerskip[j]) continue;
                    if(this->exchanged.find({i, j}) != this->exchanged.end()) continue;
                    // std::cout << i << ' ' << j << ' ' << pid[i] << ' ' << pid[j] << ' ' << p1 << ' ' << p2 << ' ' << dval[i][p2] << std::endl;
                    double cur_g = (dval[i][p2] + dval[i][p1]) + (dval[j][p1] + dval[j][p2]) - 2 * this->G.getEdgeWeight(i, j);
                    if(cur_g > max_g) {
                        max_g = cur_g;
                        a = i;
                        b = j;
                    }
                }
            }

            if(max_g >= 0) {
                alist.push_back(a);
                blist.push_back(b);
            } 
            skip[a] = true;
            skip[b] = true;
            updateDvalue(a, b);
        }

        if(alist.size() == 0) break;

        for(size_t i = 0; i < alist.size(); i ++) {
            changePart(alist[i], blist[i]);
            this->exchanged.insert({alist[i], blist[i]});
            this->exchanged.insert({blist[i], alist[i]});
            // std::cout << alist[i] << ' ' << blist[i] << std::endl;
            // outerskip[alist[i]] = true;
            // outerskip[blist[i]] = true;
            ret = true;
        }
        -- max_iter;
    }
    return ret;
}

std::vector<size_t> KernighanLinPartitioner::Part(size_t target_k, size_t max_iter) {
    size_t n_vert = this->G.nvert();
    this->pid = std::vector<size_t>(n_vert);

    this->exchanged = std::set<std::pair<size_t, size_t>>();

    this->dval = std::vector<std::vector<double>>(n_vert, std::vector<double>(target_k));
    size_t n_vert_part = (n_vert + target_k - 1) / target_k;

    this->cur_part.resize(target_k);
    for(size_t i = 0; i < target_k; i ++) {
        this->cur_part[i].clear();
    }
    for(size_t i = 0; i < n_vert; i ++) {
        this->pid[i] = (i / n_vert_part);
    }
    std::srand(time(NULL));
    std::random_shuffle(this->pid.begin(), this->pid.end());
    // return this->pid;

    for(size_t i = 0; i < n_vert; i ++) {
        this->cur_part[this->pid[i]].push_back(i);
    }
    

    for(int i = 0; i < max_iter; i ++) {
        bool improve = false;
        for(size_t j = 0; j < target_k; j ++) {
            for(size_t k = j + 1; k < target_k; k ++) {
                // improve |= KLNew(j, k);
                improve |= KL(j, k);
            }
        }
        if(!improve) break;
    }
    return this->pid;
}
std::vector<std::vector<size_t>> KernighanLinPartitioner::PartNumpyMesh(size_t target_k, size_t max_iter) {
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