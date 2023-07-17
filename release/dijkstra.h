/*dijkstra.h*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <limits>

#include "graph.h"

using namespace std;

const double INF = numeric_limits<double>::max();

//
// Dijkstra:
//
// Performs Dijkstra's shortest weighted path algorithm from
// the given start vertex.  Returns a vector of vertices in
// the order they were visited, along with a map of (long long, double)
// pairs where the long long is a vertex V and the int is the 
// distance from the start vertex to V; if no such path exists,
// the distance is INF (defined in dijkstra.h), and returns a predecessor map
// of (long long, long long) pairs to help return the shortest path. 
//
vector<long long> Dijkstra(graph& G, long long startV, map<long long, double>& distances,map<long long, long long> &predecessor);
