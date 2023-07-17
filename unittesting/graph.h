/*graph.h*/

//
// Graph class using map and sets. Edges
// are directed, but edges in both directions are possible.
// weights can be positive, negative, or zero.
// 
// For this implementation of graph, the vertices are 
// string-based, and the weights are doubles.
// For example:
// 
//   graph  G;
//   G.addVertex("ORD");
//   G.addVertex("NYC");
//   G.addEdge("ORD", "NYC", 99);
//
// Oscar Depp 
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;


class graph
{
private:
  // key: pair<from,to>, value: weight
  map<pair<string, string>, double> Edges;  
  //set of vertices(strings)
  set<string> Vertices; // vertex => index 
  
public:
  //
  // constructor:
  // 
  // n is the max # of vertices the graph can hold.
  //
  graph();

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const;

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const;

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true. If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(string v);

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true. If the vertices do not exist or the weight is negative,
  // false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(string from, string to, double weight);

  //
  // getWeight
  //
  // Returns the weight associated with a given edge. If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned. If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(string from, string to, double& weight) const;

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<string> neighbors(string v) const;

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<string> getVertices() const;

  //
  // print
  // 
  // Prints the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph  G(100);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void print(ostream& output) const;

};
