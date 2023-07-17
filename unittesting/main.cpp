/* main.cpp */

//
// This program checks the whether the graph class
// accurately does what its supposed to-add edges and vertices
// to a graph, can retrieve the weights between existing edges, 
// and prints if necessary.
// 
// Oscar Depp
// Northwestern Unversity
// CS211 Project08
//

#include <iostream>
#include <string>
#include "graph.h"
#include "gtest/gtest.h"

using namespace std;

graph buildGraph();
graph buildGraph2();
graph buildGraph3();
graph buildGraph4();

//simple graph, testing the weights function
TEST(testing, test01)
{
    graph G = buildGraph();
    ASSERT_TRUE(G.NumEdges() == 13);
    ASSERT_TRUE( G.NumVertices() == 13);

    // checking the weights function
    //simple case
    double weight = -1; 
    G.getWeight("Chicago","NYC",weight);
    ASSERT_TRUE(weight == 1.0);
    //overwrite edge//updates
    G.addEdge("Chicago","NYC",14.4);
    weight = -1; 
    G.getWeight("Chicago","NYC",weight);
    ASSERT_TRUE(weight == 14.4);
    //vertex doesn't exist
    weight = -1; 
    bool got_weight = G.getWeight("Moscow","NYC",weight);
    ASSERT_TRUE(!got_weight);
    ASSERT_TRUE(weight == -1);
    // edge that doesn't exist
    weight = -1; 
    bool changed = G.getWeight("NYC","NYC",weight);
    ASSERT_TRUE(weight == -1);
    ASSERT_TRUE(!changed);

}
// // stress test
// TEST(testing, test02)
// {
//     graph G2;
//     //add 3e6 vertices
// 	for (int i = 0; i < 3000000; i++) {
//         G2.addVertex( to_string(i) );
//     }
//     //random vertex to test edges
//     string from = "yamaha"; 
//     G2.addVertex(from);
//     // random weight, adding 1.5e6 edges
//     for(int j = 0;j < 1500000;j++) {
//         G2.addEdge(from,to_string(j),j+.154);
//     }
//     ASSERT_TRUE( G2.NumVertices() == 3000001);
//     ASSERT_TRUE( G2.NumEdges() == 1500000 );
// }

//add existing vertex doesn't work, 
// different combinations  of adding edge
TEST(testing, test03)
{
    graph G = buildGraph2();
    //vertex already exists
    bool added = G.addVertex("Orchid");
    ASSERT_TRUE(G.NumVertices() == 10);
    ASSERT_TRUE(!added);
    
    //y doesn't exist, should be false
    bool add_existing_edge = G.addEdge("NYC","semi",234);
    ASSERT_TRUE(!add_existing_edge);
    // x doesn't exist
    add_existing_edge = G.addEdge("semi","Orchid",22);
    ASSERT_TRUE(!add_existing_edge);
    // y and x exist
    add_existing_edge = G.addEdge("Sunflower","Orchid",3.2);
    ASSERT_TRUE(add_existing_edge);
    
}
//testing empty graph, and neighbors
TEST(testing, test04)
{
    graph G;
    ASSERT_TRUE(G.NumVertices() == 0);
    ASSERT_TRUE(G.NumEdges() == 0);
    ASSERT_TRUE(G.getVertices().empty());
    ASSERT_TRUE(G.neighbors("NYC").empty());
    graph G4 = buildGraph4();
    ASSERT_TRUE(G4.NumVertices() == 16); 
    ASSERT_TRUE(G4.NumEdges() == 20);
    //no neighbors of "A Gentleman in Moscow" should exist,
    // Jakarta isn't a valid vertex(or russian book)
    ASSERT_TRUE(G4.neighbors("A Gentleman in Moscow").empty());
    ASSERT_TRUE(G4.neighbors("Cactus").empty());
    
}
//testing different graph; simple graph
TEST(testing, test05) {
    graph G3 = buildGraph3();
    ASSERT_TRUE(G3.NumVertices() == 10);
    ASSERT_TRUE(G3.NumEdges() == 12);
    set<string> n_exp = {"Mongol Conquests", "Napoleonic Wars","World War I","Dungan Revolt"};
    set<string> n_act = G3.neighbors("World War II");
    ASSERT_TRUE(equal(n_exp.begin(),n_exp.end(),n_act.begin()));
}

int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

graph buildGraph() {
    graph G;
    G.addVertex("NYC");
    G.addVertex("Chicago");
    G.addVertex("LA");
    G.addVertex("Tokyo");
    G.addVertex("Paris");
    G.addVertex("Amman");
    G.addVertex("Canada");
    G.addVertex("Warsaw");
    G.addVertex("Singapore");
    G.addVertex("KL");
    G.addVertex("Evanston");
    G.addVertex("New Orleans");
    G.addVertex("Detroit");
    G.addEdge("Amman", "Canada", 23.1);
    G.addEdge("KL","Singapore",-21);
    G.addEdge("Paris","Tokyo",0);
    G.addEdge("Tokyo","Tokyo",0);
    G.addEdge("NYC","Evanston",59);
    G.addEdge("Tokyo","Paris",69);
    G.addEdge("Tokyo","Evanston",79.4);
    G.addEdge("New Orleans", "Detroit",23.5);
    G.addEdge("NYC","Chicago",1.2);
    G.addEdge("Chicago","NYC",1.0);
    G.addEdge("Chicago","Chicago",0.2);
    G.addEdge("Singapore","KL",0.01);
    G.addEdge("Singapore","Evanston",100.01);
    return G;
}

graph buildGraph2() {
    graph G;
    G.addVertex("Rose");
    G.addVertex("Lily");
    G.addVertex("Orchid");
    G.addVertex("Tulip");
    G.addVertex("Daisy");
    G.addVertex("Sunflower");
    G.addVertex("Cactus");
    G.addVertex("Fern");
    G.addVertex("Bamboo");
    G.addVertex("Palm");
    G.addEdge("Rose", "Lily", 0.5);
    G.addEdge("Rose", "Tulip", -0.2);
    G.addEdge("Rose", "Sunflower", 1.0);
    G.addEdge("Lily", "Orchid", 0.3);
    G.addEdge("Lily", "Daisy", -0.4);
    G.addEdge("Orchid", "Tulip", 0.1);
    G.addEdge("Orchid", "Fern", 0.7);
    G.addEdge("Tulip", "Daisy", -0.6);
    G.addEdge("Tulip", "Bamboo", 0.9);
    G.addEdge("Daisy", "Cactus", -0.3);
    G.addEdge("Sunflower", "Palm", 1.2);
    G.addEdge("Fern", "Bamboo", 0.6);
    G.addEdge("Bamboo", "Palm", 1.1);
    return G;
}

graph buildGraph3() {
    graph G;
    G.addVertex("World War II");
    G.addVertex("World War I");
    G.addVertex("Taiping Rebellion");
    G.addVertex("Napoleonic Wars");
    G.addVertex("Mongol Conquests");
    G.addVertex("Thirty Years' War");
    G.addVertex("An Lushan Rebellion");
    G.addVertex("Qing dynasty conquest of the Ming dynasty");
    G.addVertex("Dungan Revolt");
    G.addVertex("Conquests of Timur");
    G.addEdge("World War II", "World War I", 23);
    G.addEdge("World War II", "Dungan Revolt", 123);
    G.addEdge("World War II", "Mongol Conquests", 160);
    G.addEdge("World War II", "Napoleonic Wars", 121);
    G.addEdge("World War I", "Napoleonic Wars", 104);
    G.addEdge("Taiping Rebellion", "Qing dynasty conquest of the Ming dynasty", 10);
    G.addEdge("Napoleonic Wars", "Thirty Years' War", 85);
    G.addEdge("Mongol Conquests", "Conquests of Timur", 117);
    G.addEdge("Thirty Years' War", "An Lushan Rebellion", 27);
    G.addEdge("An Lushan Rebellion", "Dungan Revolt", 47);
    G.addEdge("Mongol Conquests", "Thirty Years' War", 290);
    G.addEdge("Qing dynasty conquest of the Ming dynasty", "Conquests of Timur", 122);
    return G;
}

graph buildGraph4() {
    graph G;

    G.addVertex("A Gentleman in Moscow");    
    G.addVertex("War and Peace");
    G.addVertex("Crime and Punishment");
    G.addVertex("Anna Karenina");
    G.addVertex("The Brothers Karamazov");
    G.addVertex("Dead Souls");
    G.addVertex("Doctor Zhivago");
    G.addVertex("The Master and Margarita");
    G.addVertex("Eugene Onegin");
    G.addVertex("Fathers and Sons");
    G.addVertex("One Day in the Life of Ivan Denisovich");
    G.addVertex("The Idiot");
    G.addVertex("The Cherry Orchard");
    G.addVertex("The Seagull");
    G.addVertex("Uncle Vanya");
    G.addVertex("The Three Sisters");

    G.addEdge("War and Peace", "Anna Karenina", 12.3);
    G.addEdge("War and Peace", "The Brothers Karamazov", 4.5);
    G.addEdge("War and Peace", "Dead Souls", 9.8);
    G.addEdge("War and Peace", "Fathers and Sons", 7.2);
    G.addEdge("Anna Karenina", "The Brothers Karamazov", 5.5);
    G.addEdge("Anna Karenina", "Doctor Zhivago", 3.9);
    G.addEdge("The Brothers Karamazov", "The Idiot", 8.1);
    G.addEdge("The Brothers Karamazov", "The Cherry Orchard", 2.7);
    G.addEdge("Dead Souls", "Fathers and Sons", 6.4);
    G.addEdge("Dead Souls", "One Day in the Life of Ivan Denisovich", 1.8);
    G.addEdge("Doctor Zhivago", "The Master and Margarita", 7.5);
    G.addEdge("Doctor Zhivago", "Uncle Vanya", 6.2);
    G.addEdge("Doctor Zhivago", "Crime and Punishment", 9.8);
    G.addEdge("The Master and Margarita", "The Idiot", 9.1);
    G.addEdge("The Master and Margarita", "The Three Sisters", 3.7);
    G.addEdge("Fathers and Sons", "One Day in the Life of Ivan Denisovich", 2.3);
    G.addEdge("Fathers and Sons", "The Seagull", 5.9);
    G.addEdge("One Day in the Life of Ivan Denisovich", "The Idiot", 1.1);
    G.addEdge("The Cherry Orchard", "Uncle Vanya", 4.2);
    G.addEdge("The Seagull", "The Three Sisters", 3.6);
    return G;
}
