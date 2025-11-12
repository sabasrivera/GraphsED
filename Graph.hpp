#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector> 
#include <limits> 

using namespace std;

class Graph
{
private:
    map<string, list<pair<string, int>>> adjList;
public:
    // Añade un nodo al mapa si no existe
    void addNode(string node);
    // Método para obtener todos los nodos (ciudades)
    vector<string> getNodes() const;
    // Añade una arista
    void addEdge(string src, string dest, int weight = 0, bool directed = false);
    // Imprime el grafo
    void printGraph();
    // Devuelve la ruta más corta y su peso usando Dijkstra
    pair<int, list<string>> dijkstraShortestPath(string start, string end);
};
#endif
