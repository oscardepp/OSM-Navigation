/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// containsThisNode
//
// Returns true if the building's nodes contains the given node id,
// false if not.
//
bool Building::containsThisNode(long long nodeid)
{
  for (long long id : this->NodeIDs)
  {
    if (nodeid == id)
      return true;
  }

  // 
  // if get here, not found:
  //
  return false;
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes.
//
void Building::print(Nodes& nodes)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;

  pair<double, double> avg_loc = this->getLocation(nodes);
  cout << "Approximate location: (" << avg_loc.first << ", " << avg_loc.second << ")" << endl;

  cout << "Nodes:" << endl;
  for (long long nodeid : this->NodeIDs)
  {
    cout << "  " << nodeid << ": ";

    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      cout << "(" << lat << ", " << lon << ")";

      if (entrance)
        cout << ", is entrance";

      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }
  }//for
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}

//
// getLocation
//
//
// lookup nodeID and gets the average latitude and longitude of the building, and returns it as a pair
//
pair<double, double> Building::getLocation(Nodes& nodes) {

    //assert(NodeIDs.size()>0);
    double avgLat = 0;
    double avgLon = 0;
    double nid_lat = 0;
    double nid_lon = 0;
    bool isEntrance;
    for(long long nid: this->NodeIDs) {
        nodes.find(nid, nid_lat,nid_lon,isEntrance);
        avgLat += nid_lat;
        avgLon += nid_lon;
    }
    avgLat /= NodeIDs.size();
    avgLon /= NodeIDs.size();
    return make_pair(avgLat, avgLon);
}


