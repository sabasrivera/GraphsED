#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <unordered_set>
#include <vector>
#include <limits>

using namespace std;

class Grafo
{
private:
    map<string, list<pair<string, int>>> listaAdyacencia;
public:
    void agregarNodo(string nodo); // Añade un nodo
    vector<string> obtenerNodos() const; // Devuelve una lista de nodos
    void agregarArista(string origen, string destino, int distancia = 0, bool dirigido = false);
    void imprimirGrafo(); // Imprime el grafo
    pair<int, list<string>> caminoMasCortoDijkstra(string inicio, string fin); // Devuelve la ruta mas corta
};

#endif
