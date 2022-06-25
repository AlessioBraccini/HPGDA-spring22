#ifndef ORACLE_CONTEST_GRAPHALGORITHM_H
#define ORACLE_CONTEST_GRAPHALGORITHM_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <climits>
#include <set>
#include <string>

template<typename T>
class GraphAlgorithm {
    long v, e, last;
    long *dist;
    bool *used;
    T *graph;

public:
    GraphAlgorithm(long v, long e) : v(v), e(e) {
        used = new bool[v + 2];
        dist = new long[v + 2];
        graph = new T(v, e);
    }

    ~GraphAlgorithm() {
        delete[] used;
        delete[] dist;
        delete graph;
    }

    // required
    void populate(triple *edges) {
        graph->populate(edges);
    }

    // required
    void finished() {
        graph->finished();
    }

//    // optional
//    void sortEdgesByNodeId() {
//        graph->sortEdgesByNodeId();
//    }
//
//    // optional
//    void add_edges(long from, std::vector<long> &to, std::vector<double> &weights) {
//        graph->add_edges(from, to, weights);
//    }
//
//    // optional
//    void add_edge(long from, long to, double weight) {
//        graph->add_edge(from, to, weight);
//    }

    void write_results(std::string filename) {
        std::ofstream outfile(filename);
        for (long i = 0; i <= v; i++){
            outfile << i << " " << dist[i] << std::endl;
        }
    }

    // the bfs populate diff with the corresponding
    // layer of the BFS tree for each vertex
    double bfs(long cur_vertex) {
        // initialization
        memset(used, 0, sizeof(bool) * (v + 2));
        for (long i = 0; i < v + 2; i++)
            dist[i] = LONG_MAX;
        double sum = 0;
        std::queue<long> q;
        q.push(cur_vertex);
        used[cur_vertex] = true;
        dist[cur_vertex] = 0;

        // main loop
        while (!q.empty()) {
            cur_vertex = q.front();
            q.pop();
            for (auto& to : graph->get_neighbors(cur_vertex)) {
                if (!used[to.first]) {
                    used[to.first] = true;
                    dist[to.first] = dist[cur_vertex] + 1;
                    q.push(to.first);
                    sum = sum + to.second;
                }
            }
        }
        return sum;
    }

    // the dfs populate diff with the visiting
    // order for each vertex
    double dfs_recursion(long cur_vertex) {
        double sum = 0;
        used[cur_vertex] = true;
        for (auto& to : graph->get_neighbors(cur_vertex)) {
            if (!used[to.first]) {
                dist[to.first] = ++last;
                sum += to.second;
                sum += dfs_recursion(to.first);
            }
        }
        return sum;
    }

    double dfs(long cur_vertex) {
        // initialization
        memset(used, 0, sizeof(bool) * (v + 2));
        for (long i = 0; i < v + 2; i++)
            dist[i] = LONG_MAX;
        dist[cur_vertex] = 0;
        last = 0;
        // recursion
        return dfs_recursion(cur_vertex);
    }

};

#endif //ORACLE_CONTEST_GRAPHALGORITHM_H
