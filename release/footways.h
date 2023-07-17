/*footways.h*/

//
// A collection of footways / paths in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once
#include <vector>
#include <limits>
#include <utility>
#include "building.h"
#include "footway.h"
#include "tinyxml2.h"
#include "dist.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the footways / paths in the map.
//
class Footways
{
public:
  vector<Footway> MapFootways;

  //
  // readMapFootways
  //
  // Given an XML document, reads through the document and 
  // stores all the footways into the given vector.
  //
  void readMapFootways(XMLDocument& xmldoc);

  //
  // intersectWithBuilding
  // 
  // Outputs all the footways that intersect --- i.e. share
  // a common node --- with Building B.
  //
  void intersectWithBuilding(Building& B);

  //
  // findMin
  //
  // finds a footway nodeID that is closest to the building and returns its distance,
  // the footway nodeID closest, and the footwayID associated with it
  //
  void findMin(Building &B,Nodes &nodes, pair<long long, long long> &min, double &minDistance);

  //
  // accessors / getters
  //
  int getNumMapFootways();

};


