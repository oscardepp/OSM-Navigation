/*graph.cpp*/

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
// CS 211: Winter 2023 Project08
//

#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <vector>

#include "graph.h"

using namespace std;


//
// constructor:
//
// n is the max # of vertices the graph can hold.
//
graph::graph() 
{
  //cout << "** Constructor! **" << endl;
}

//
// NumVertices
//
// Returns the # of vertices currently in the graph.
//
int graph::NumVertices() const 
{ 
  return (int) this->Vertices.size(); 
}

//
// NumEdges
//
// Returns the # of edges currently in the graph.
//
int graph::NumEdges() const 
{ 
  return this->Edges.size();
}

//
// addVertex
//
// Adds the vertex v to the graph if there's room, and if so
// returns true. If the graph is full, or the vertex already
// exists in the graph, then false is returned.
//
bool graph::addVertex(string v)
{ 
  //if it exists already, don't add it
  if (this->Vertices.find(v) != this->Vertices.end()) {
      return false; 
    }
    else {
      this->Vertices.emplace(v);
    }
    return true; 
}

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
bool graph::addEdge(string from, string to, double weight)
{
  // check whether from and to are valid edges
  auto ptr = this->Vertices.find(from); 
  if (ptr == this->Vertices.end()) {
    // not found:
    //cout << "NOT VALID**" << endl;
    return false;
  }
  ptr = this->Vertices.find(to); 
  if (ptr == this->Vertices.end()) { 
    // not found:
    return false;
  }
  //does it exist in the edges:
  pair<string, string> search_pair(from, to);

  auto iter = this->Edges.find(search_pair);
  if (iter != this->Edges.end()) {
    this->Edges[search_pair] = weight; 
  } else {
    this->Edges.insert({search_pair, weight});
  }
  return true; 
}

//
// getWeight
//
// Returns the weight associated with a given edge. If
// the edge exists, the weight is returned via the reference
// parameter and true is returned. If the edge does not
// exist, the weight parameter is unchanged and false is
// returned.
//
bool graph::getWeight(string from, string to, double& weight) const
{
  //do the vertices exist?
  auto ptr = this->Vertices.find(from);
  if (ptr == this->Vertices.end()) 
    // not found:
    return false;
  ptr = this->Vertices.find(to);
  if (ptr == this->Vertices.end()) 
    // not found:
    return false;

  //pair of from to combos we want to search in the map
  pair<string,string> search_pair(from,to);
  //set weight and return true if found//don't do anything if not found
  auto iter = this->Edges.find(search_pair);
  if(iter == this->Edges.end()) {
    return false; 
  } else {
    weight = iter->second;
  }
  return true;
}

//
// neighbors
//
// Returns a set containing the neighbors of v, i.e. all
// vertices that can be reached from v along one edge.
// Since a set is returned, the neighbors are returned in
// sorted order; use foreach to iterate through the set.
//
set<string> graph::neighbors(string v) const {
  set<string> S;
  //go through each edge and see whether there is an edge from v to an edge
  for (auto &pair: this->Edges) // for each vertex:
  {
    //access the pair <from, to>, and get the to
    string to = pair.first.second;
    if (this->Edges.find(make_pair(v,to)) != this->Edges.end()) // exists!
    {
      S.insert(to);
    }
  }

  return S;
}

//
// getVertices
//
// Returns a vector containing all the vertices currently in
// the graph.
//
vector<string> graph::getVertices() const
{
  vector<string> V(this->Vertices.begin(), this->Vertices.end());
  return V;
}

//
// print
//
// Prints the internal state of the graph for debugging purposes.
//
// Example:
//    graph  G(100);
//    ...
//    G.print(cout);  // dump to console
//
void graph::print(ostream& output) const
{
  output << "***************************************************" << endl;
  output << "********************* GRAPH ***********************" << endl;

  output << "**Num vertices: " << this->NumVertices() << endl;
  output << "**Num edges: " << this->NumEdges() << endl;

  output << endl;
  output << "**Vertices map**" << endl;
  output<< endl;
  for (string vertex : this->Vertices) // for each vertex:
  {
    output << vertex << endl;
  }
  output << endl;
  output << "**Edges in (from,to) format**" << endl;
  output << endl;
  for (auto& pair : this->Edges) {
    output << "(" << pair.first.first << ", " << pair.first.second << ")" << endl;
  }
  output << endl;
  output << "**************************************************" << endl;
}
