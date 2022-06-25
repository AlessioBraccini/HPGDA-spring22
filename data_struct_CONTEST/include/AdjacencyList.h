#ifndef ORACLE_CONTEST_ADJACENCYLIST_H
#define ORACLE_CONTEST_ADJACENCYLIST_H

#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include <map>
#include "utils.h"

// Adjacency list implementation of Graph
class AdjacencyList{

    class EdgeIter {
        
        class iterator {
        public:
            iterator(std::list<long>::iterator ptr, std::list<double>::iterator begin_w_ptr) : ptr(ptr), begin_w_ptr(begin_w_ptr) {}

            iterator operator++() {
                ++ptr;
                ++begin_w_ptr;
                return *this;
            }

            bool operator!=(const iterator &other) { return ptr != other.ptr; }

            const std::pair<long, double> &operator*() {
                current.first = *ptr;
                current.second = *begin_w_ptr;
                return current;
            };

        private:
            std::list<long>::iterator ptr;
            std::list<double>::iterator begin_w_ptr;
            std::pair<long, double> current;
        };

    private:
        std::list<long>::iterator begin_ptr, end_ptr;
        std::list<double>::iterator begin_w_ptr;
    public:
        EdgeIter(std::list<long>::iterator begin_ptr, std::list<long>::iterator end_ptr, std::list<double>::iterator begin_w_ptr) : begin_ptr(begin_ptr), end_ptr(end_ptr), begin_w_ptr(begin_w_ptr) {}

        iterator begin() const { return iterator(begin_ptr, begin_w_ptr); }

        iterator end() const { return iterator(end_ptr, begin_w_ptr); }
    };

    long v, e;
    std::list<long>* edges;
    std::list<double>* weights;

public:

    EdgeIter get_neighbors(int idx){
        return EdgeIter(begin(idx), end(idx), begin_weights(idx));
    }

    AdjacencyList(long v, long e) : v(v), e(e){
        edges = new std::list<long>[v + 2];
        weights = new std::list<double>[v + 2];
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
    }

    ~AdjacencyList(){
        for(int i = 0; i <= v; ++i)
            edges[i].clear(), weights[i].clear();
        delete[] edges;
        delete[] weights;
        //std::cout<<"AdjacencyList delete"<<std::endl;
    }

    void add_edges(int from, std::vector<long>& to, std::vector<double>& w);

    void add_edge(int from, long to, double weight = 0);

    void sortEdgesByNodeId();

    void finished();

    void populate(std::tuple<long, long, double>* e_list);

    inline std::list<long>::iterator begin(int cur_vertex) {
        return edges[cur_vertex].begin();
    }

    inline std::list<long>::iterator end(int cur_vertex){
        return edges[cur_vertex].end();
    }

    inline std::list<double>::iterator begin_weights(int cur_vertex) {
        return weights[cur_vertex].begin();
    }

};


#endif //ORACLE_CONTEST_ADJACENCYLIST_H
