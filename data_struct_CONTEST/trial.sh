#!/bin/bash

echo "Benchmarking example_directed graph"
bin/exe data/example_directed 2 1 -d
echo "-----------------------------------------------------------------------------------"

echo "Benchmarking example_undirected graph "
bin/exe data/example_undirected 2 1 -U -d
echo "-----------------------------------------------------------------------------------"

echo "Benchmarking wiki-Talk graph "
bin/exe data/wiki-Talk 2 1 -d
echo "-----------------------------------------------------------------------------------"

echo "Benchmarking cit patents graph "
bin/exe data/cit-Patents 3774754 1 -d
echo "-----------------------------------------------------------------------------------"

echo "Benchmarking dota graph "
bin/exe data/dota-league 55712 1 -U -d

