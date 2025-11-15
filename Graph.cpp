#include "Graph.hpp"

// Añade un nodo al mapa si no existe
void Grafo::agregarNodo(string nodo)
{
    if (listaAdyacencia.find(nodo) == listaAdyacencia.end())
    {
        listaAdyacencia[nodo] = list<pair<string, int>>();
    } //lista vacia de conexiones
}

vector<string> Grafo::obtenerNodos() const // Devuelve una lista de nodos
{
    vector<string> nodos;
    for (const auto &par : listaAdyacencia)
    {
        nodos.push_back(par.first);
    }
    return nodos;
}

void Grafo::agregarArista(string origen, string destino, int distancia, bool dirigido)
{
    agregarNodo(origen); // Asegura que el nodo de origen exista
    agregarNodo(destino);

    listaAdyacencia[origen].push_back(make_pair(destino, distancia));

    if (!dirigido)
    {
        listaAdyacencia[destino].push_back(make_pair(origen, distancia));
    }
}

void Grafo::imprimirGrafo()
{
    // Itera sobre cada nodo en el mapa
    for (auto &nodo : listaAdyacencia)
    {
        cout << "\nDesde [" << nodo.first << "]:" << endl;

        if (nodo.second.empty()) //que el nodo no este vacio 
        {
            cout << "  -> (No tiene conexiones registradas)" << endl;
        }
        else
        {
            for (auto &vecino : nodo.second)
            {
                cout << "  -> Conecta con [" << vecino.first << "]";
                cout << " (Distancia: " << vecino.second << " km)" << endl;
            }
        }
    }
}

// Implementacion del algoritmo de Dijkstra para encontrar el camino mas corto

pair<int, list<string>> Grafo::caminoMasCortoDijkstra(string inicio, string fin)
{
    map<string, int> distancias; // Distancias desde el nodo inicial
    map<string, string> predecesores;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> colaPrioridad;
    const int INFINITO = 1e9;

    for (const auto &parNodo : listaAdyacencia) // inicializa todas las distancias
        distancias[parNodo.first] = INFINITO;
    distancias[inicio] = 0;
    colaPrioridad.push({0, inicio});

    while (!colaPrioridad.empty())
    {
        int distanciaActual = colaPrioridad.top().first; //ciclo principal
        string u = colaPrioridad.top().second;
        colaPrioridad.pop();

        if (distanciaActual > distancias[u]) //se ignora
            continue;
        if (u == fin)
            break; //si se llega al nodo final, se termina el algoritmo

        for (const auto &parVecino : listaAdyacencia[u])
        {
            string v = parVecino.first;
            int distancia = parVecino.second; 

            if (distancias[u] + distancia < distancias[v])
            {
                distancias[v] = distancias[u] + distancia;
                predecesores[v] = u;
                colaPrioridad.push({distancias[v], v});
            }
        }
    }

    list<string> camino;
    int distanciaTotal = distancias[fin]; // Distancia total al nodo final

    if (distanciaTotal == INFINITO)
        return {-1, camino};

    string nodoActual = fin;
    while (nodoActual != inicio)
    {
        if (predecesores.find(nodoActual) == predecesores.end())
        {
            return {-1, list<string>()};
        }
        camino.push_front(nodoActual);
        nodoActual = predecesores[nodoActual];
    }
    camino.push_front(inicio);
    return {distanciaTotal, camino};
}
