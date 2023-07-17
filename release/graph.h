/*graph.h*/

//
// Graph class using adjacency list representation. Edges
// are directed, so building an undirected graph requires
// adding edges in both directions. No limit on graph size,
// but multi-edges (multiple edges between the same two
// vertices) are not allowed.
// 
// For this implementation of graph, the vertices are 
// long long, and the weights are doubles.  Example:
// 
//   graph  G;
//   G.addVertex(129850);
//   G.addVertex(552985);
//   G.addEdge(129850, 552985, 99.99);
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include "nodes.h"
#include "footway.h"
#include "dist.h"

using namespace std;


class graph
{
private:
  vector<long long>    Vertices;
  map<long long, int>  Vertex2Index;
  vector<map<int, double>> Edges;
  int EdgeCount;

  int _LookupVertex(long long v) const;

public:
  //
  // constructor:
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
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(long long v);

  //
  // add FootwayEdges
  //
  // adds the edges to the graph between nodeIds of a given footway front and back, by finding the distance between them 
  // and using that as weight. 
  //
  void addFootwayEdges(Footway &F,Nodes &nodes) {
      double lat1,long1,lat2,long2;
      bool isEntrance;
      long long source, dest;
      double weight;
      //add edges from the front
      for(unsigned int i = 0; i <F.NodeIDs.size()-1;i++) {
          source = F.NodeIDs[i];
          dest = F.NodeIDs[i+1];
          nodes.find(source,lat1,long1,isEntrance);
          nodes.find(dest,lat2,long2,isEntrance);
          weight = distBetween2Points(lat1, long1, lat2, long2);
          this->addEdge(source, dest, weight);
      }
      // add edges going backwards
      for(unsigned int i = F.NodeIDs.size()-1; i>0;i--) {
          source = F.NodeIDs[i];
          dest = F.NodeIDs[i-1];
          nodes.find(source,lat1,long1,isEntrance);
          nodes.find(dest,lat2,long2,isEntrance);
          weight = distBetween2Points(lat1,long1,lat2,long2);
          this->addEdge(source, dest, weight);
      }
  }

  //
  // printGraph
  //
  // sanity check! prints the edges of the footway 986532630 when "!" is entered.
  //
  void printEdges() {
      //test case
      double weight;
      std::vector<long long> from{9119071425, 533996671, 533996671, 533996672, 533996672, 2240260064};
      std::vector<long long> to{533996671, 9119071425, 533996672, 533996671, 2240260064, 533996672};
      cout << "Graph check of Footway ID 986532630" << endl;
      //print out all the edges between a from and a to footway
      for (unsigned int i = 0; i < from.size(); i++) {
          this->getWeight(from[i], to[i], weight);
          cout << "  Edge: (" << from[i] << ", " << to[i] << ", " << weight << ")" << endl;
      }
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(long long from, long long to, double weight);

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(long long from, long long to, double& weight) const;

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<long long> neighbors(long long v) const;

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<long long> getVertices() const;

  //
  // print
  // 
  // Prints the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph G;
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void print(ostream& output) const;

};
