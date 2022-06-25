#include "../include/AdjacencyList.h"
#include "map"




void AdjacencyList::add_edges(int from, std::vector<long>& to, std::vector<double>& w) {
    for(int i : to)
        edges[from].push_back(i);
    for(double i : w)
        weights[from].push_back(i);
}

void AdjacencyList::add_edge(int from, long to, double weight) {
    edges[from].push_back(to);
    weights[from].push_back(weight);
}

void AdjacencyList::populate(std::tuple<long, long, double>* e_list){
    for(long i = 0; i < e; i++)
        add_edge(std::get<0>(e_list[i]), std::get<1>(e_list[i]), std::get<2>(e_list[i]));

    finished();
}

void AdjacencyList::sortEdgesByNodeId() {
    for(int i = 0; i <= v; ++i)
        edges[i].sort();
}

void AdjacencyList::finished() {}