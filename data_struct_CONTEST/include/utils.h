#ifndef ORACLE_CONTEST_UTILS_H
#define ORACLE_CONTEST_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <chrono>
#include <algorithm>
#include <functional>
#include <unistd.h>
#include <map>
#include "triple.h"


// count non empty lines in a file
inline long count_lines(std::string filename){
    std::ifstream inFile(filename);
    long numLines = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty())
            numLines++;
    }
    return numLines;
}

// split a string in a vector of strings, given a separator char
inline std::vector<std::string> split(const std::string &s, char delim){
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

// load the graph
inline std::set<long> load_graph(std::string filename, bool undirected, triple *edges, long e){
    std::ifstream eFile(filename+".e");
    std::string line;
    std::vector<std::string> tmp;
    std::set<long> nodes;
    std::vector<triple> e_tmp;


    while (std::getline(eFile, line)){
        if (!line.empty()){
            tmp = split(line, ' ');
            break;
        }
    }
    eFile.seekg(0);

    bool weighted = false;
    if (tmp.size() == 3)
        weighted = true;

    long i = 0;

    triple edge;

    // TODO make it faster
    while (std::getline(eFile, line)){
        if (!line.empty()){
            tmp = split(line, ' ');

            edge.x = std::stol(tmp[0]);
            edge.y = std::stol(tmp[1]);
            edge.val = (weighted)?std::stof(tmp[2]):1;

            e_tmp.push_back(edge);

            if (undirected){
                edge.x = std::stol(tmp[1]);
                edge.y = std::stol(tmp[0]);
                edge.val = (weighted)?std::stof(tmp[2]):1;

                e_tmp.push_back(edge);
            }
            nodes.insert(std::stol(tmp[0]));
            nodes.insert(std::stol(tmp[1]));
            i++;
        }
    }

    std::sort(e_tmp.begin(), e_tmp.end());

    for (long j = 0; j < e; ++j) {
        edges[j]=e_tmp[j];
    }

    // for loop that manage the node "jump"
    //long max_idx = *nodes.rbegin();
    //for(long j = 0; j < max_idx; j++) 
    //    nodes.insert(j); 


    return nodes;
}

inline void print_graph_info(long v, long e, bool undirected){
    std::string prop = (undirected) ? "Undirected" : "Directed";
    std::cout << prop << " graph" << std::endl;
    std::cout << "num nodes: " << v << std::endl;
    std::cout << "num directed edges: " << e << std::endl << std::endl;
}

inline void print_edge_list(std::tuple<long, long, double>* edges, long e){
    for(long j = 0; j < e; j++)
        std::cout << std::get<0>(edges[j]) << " " << std::get<1>(edges[j]) << " " << std::get<2>(edges[j]) << std::endl;
    std::cout << std::endl;
}

inline void process_mem_usage(double& vm_usage, double& resident_set, bool diff)
{
    std::ifstream stat_stream("/proc/self/stat",std::ios_base::in);

    std::string pid, comm, state, ppid, pgrp, session, tty_nr;
    std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    std::string utime, stime, cutime, cstime, priority, nice;
    std::string O, itrealvalue, starttime;

    unsigned long vsize;
    long rss;

    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

    stat_stream.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages

    if(!diff){
        vm_usage = vsize / 1024.0;
        resident_set = rss * page_size_kb;
    } else {
        vm_usage = (vsize / 1024.0) - vm_usage;
        resident_set = (rss * page_size_kb) - resident_set;
    }
}

#endif //ORACLE_CONTEST_UTILS_H
