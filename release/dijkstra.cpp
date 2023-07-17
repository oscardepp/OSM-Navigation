#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <utility>
#include <functional>
#include "graph.h"
#include "dijkstra.h"

//
// compares two pairs and sets order  prioritized based off their values, if they are tied, orders it by key
//
struct prioritize {
  bool operator()(const pair<long long, double>& p1, const pair<long long, double>& p2) const
    {
        if (p1.second > p2.second)
            return true;
        else if (p1.second < p2.second)
            return false;
        else { // if two values are the same :
            return p1.first > p2.first; // order by the key
        }
    }
};

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
vector<long long> Dijkstra(graph& G, long long startV, map<long long, double> & distances,map<long long, long long> &predecessor)
{
    vector<long long> visited;     // to return
    priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> pq;

    // initialize distances and add start vertex to the priority queue
    for (long long currentV : G.getVertices())
    {
        distances[currentV] = INF;
        predecessor[currentV] = 0;
        pq.push(make_pair(currentV, distances[currentV]));
    }
    distances[startV] = 0;
    pq.push(make_pair(startV,distances[startV]));

    while (!pq.empty())
    {
        long long currentV = pq.top().first;
        pq.pop();

        if(distances[currentV] ==INF) {
          break;
        } else if(std::find(visited.begin(), visited.end(), currentV) != visited.end()) {
           continue;
        } else {
           visited.push_back(currentV); // add to visited

        }
        set<long long> neighbors = G.neighbors(currentV);
        for (long long adjV : neighbors) {
            double edgeWeight;
            G.getWeight(currentV, adjV,edgeWeight);
            double alternativePathDistance = distances[currentV] +edgeWeight;
         
            if(alternativePathDistance < distances[adjV]) {
                distances[adjV] = alternativePathDistance;
                predecessor[adjV] =currentV;
                pq.push(make_pair(adjV, alternativePathDistance));
            }
        }
    }
   return visited;
}
