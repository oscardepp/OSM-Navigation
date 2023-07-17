/*main.cpp*/

//
// Program to input Nodes (positions), Buildings and Footways
// from an Open Street Map file.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>
#include <limits>
#include "buildings.h"
#include "dist.h"
#include "footways.h"
#include "node.h"
#include "graph.h"
#include "nodes.h"
#include "dijkstra.h"
#include "osm.h"
#include "tinyxml2.h"


using namespace std;
using namespace tinyxml2;

//
// buildGraph
//
// Inputs the graph vertices and edges from the nodes and footways.
//
graph buildGraph(Nodes &nodes, Footways &footways) {
//
    graph G;
    // Input vertices
    for(auto &pair:nodes)
    {
        G.addVertex(pair.first);
    }
    //add vertex first
    // then for every footway, you add an edge between nodeids
    //front and back
    // add the edges
    for (Footway &F:footways.MapFootways)
   {
      G.addFootwayEdges(F,nodes);
   }
    return G;
}

//
// shortestPath
//
//
// Finds the shortest possible path between a start footway nodeID and another and prints the distance between the two, nodes visited, 
// and the path way from one to another
//
void shortestPath(long long startNode, long long endNode, graph&G) {

  cout << "Shortest weighted path:"<< endl;
  vector<long long> visited;
  map<long long, double> distances;
  map<long long, long long> predecessor;
  visited = Dijkstra(G, startNode, distances,predecessor);
  if(distances[endNode] == INF) {
    cout << "**Sorry, destination unreachable" << endl; 
    return;
  } 
  cout << "  # nodes visited: "<< visited.size() << endl;
  cout << "  Distance: " << distances[endNode] << " miles" << endl;
  cout << "  Path: ";
  stack <long long> path;
  long long pred= endNode;
  path.push(pred);
  // keep finding the predecessor node until you reach the start node
  while (pred != startNode) {
    pred = predecessor[pred];
    path.push(pred);
  }
  cout << path.top();
  path.pop();
  //print out the list using a stack
  while (!path.empty()) {
    cout << "->" << path.top();
    path.pop();
  }
  cout << endl;
} 

//
// navigate
//
// navigates from an inputted building S to another inputted building D using the closest footway,
// and prints the minimum path from one to the other, and prints the path from one to the other. 
//
void navigate(Buildings &buildings, Nodes &nodes,Footways &footways, graph &G) {
    constexpr double INF = numeric_limits<double>::max();
    string start, dest;
    cout<< "Enter start building name (partial or complete)> " << endl;
    getline(cin, start);

    //will return an empty building with empty info(0, "") if the start building is not found
    Building startB = buildings.findPrintStartAndEnd(start, nodes);
    if(startB.ID == 0) {
      cout << "**Start building not found" << endl;
      return;
    }
    double minDistance = INF;
    //defined as (footway ID, footway nodeID)
    pair <long long, long long> minStart(-1,-1);  
    footways.findMin(startB,nodes,minStart, minDistance);
    cout << "  Closest footway ID " << minStart.first << ", node ID " << minStart.second << ", distance " << minDistance << endl;
    cout<< "Enter destination building name (partial or complete)> " << endl;
    getline(cin, dest);
    //will return an empty building with empty info(0, "") if the destination building is not found
    Building destB = buildings.findPrintStartAndEnd(dest,nodes);
    if(destB.ID == 0) {
      cout << "**Destination building not found" << endl;
      return;
    }
    minDistance = INF;
    //(footway ID, footway nodeID)
    pair <long long, long long> minDest(-1,-1);  
    footways.findMin(destB,nodes,minDest,minDistance);
    cout << "  Closest footway ID " << minDest.first << ", node ID " << minDest.second << ", distance " << minDistance << endl;
    // prints the shortest path between the two node ids
    shortestPath(minStart.second,minDest.second,G);
}


//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;

  cout << setprecision(12);
  
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // NOTE: let's sort so we can use binary search when we need 
  // to lookup nodes.
  //
  nodes.sortByID();

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways, which are the walking paths:
  //
  footways.readMapFootways(xmldoc);

  //
  // build the graph
  //
  graph G = buildGraph(nodes,footways);

  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;
  cout << "# of graph vertices: " << G.NumVertices() << endl;
  cout << "# of graph edges: " << G.NumEdges() << endl;

  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name, * to list, @ to navigate, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
        buildings.print();
    }
    else if (name == "!") {
        G.printEdges();
    } else if (name == "@") {
        navigate(buildings, nodes,footways, G);
    }
    else {
      buildings.findAndPrint(name, nodes, footways);
    }

  }//while

  //
  // done:
  //
  cout << endl;
  cout << "** Done  **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;
  cout << endl;

  return 0;
}
