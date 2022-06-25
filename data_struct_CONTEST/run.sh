#!/bin/bash

# Run 10 iterations on example_directed, with src vertex 2
# Save results in results_directed.csv
echo "Benchmarking example_directed graph (10 iterations)"
echo "Src_Vertex,PopulateTime(ms),MemUsage(MB),BFSTime(ms),BFSSum,DFSTime(ms),DFSSum" > results_directed.csv
bin/exe data/example_directed 2 10 >> results_directed.csv

# Run 10 iterations on example_undirected, with src vertex 2
# Save results in results_undirected.csv
echo "Benchmarking example_undirected graph (10 iterations)"
echo "Src_Vertex,PopulateTime(ms),MemUsage(MB),BFSTime(ms),BFSSum,DFSTime(ms),DFSSum" > results_undirected.csv
bin/exe data/example_undirected 2 10 -U >> results_undirected.csv

# Run 10 iterations on wiki-Talk, with src vertex 2
# Save results in results_wiki-Talk.csv
echo "Benchmarking wiki-Talk graph (10 iterations)"
echo "Src_Vertex,PopulateTime(ms),MemUsage(MB),BFSTime(ms),BFSSum,DFSTime(ms),DFSSum" > results_wiki-Talk.csv
bin/exe data/wiki-Talk 2 10 >> results_wiki-Talk.csv

# Run 10 iterations on cit-Patents, with src vertex 3774754
# Save results in results_cit-Patents.csv
echo "Benchmarking cit-Patents graph (10 iterations)"
echo "Src_Vertex,PopulateTime(ms),MemUsage(MB),BFSTime(ms),BFSSum,DFSTime(ms),DFSSum" > results_cit-Patents.csv
bin/exe data/cit-Patents 3774754 10 >> results_cit-Patents.csv

# Run 10 iterations on dota-league, with src vertex 55712
# Save results in results_dota-league.csv
echo "Benchmarking dota-league graph (10 iterations)"
echo "Src_Vertex,PopulateTime(ms),MemUsage(MB),BFSTime(ms),BFSSum,DFSTime(ms),DFSSum" > results_dota-league.csv
bin/exe data/dota-league 55712 10 -U >> results_dota-league.csv