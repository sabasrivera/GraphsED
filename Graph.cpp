#include "Graph.hpp"

// Añade un nodo al mapa si no existe
void Graph::addNode(string node)
{
    if (adjList.find(node) == adjList.end())
    {
        adjList[node] = list<pair<string, int>>();
    }
}

// Método para obtener todos los nodos (ciudades)
vector<string> Graph::getNodes() const
{
    vector<string> nodes;
    for (const auto &pair : adjList)
    {
        nodes.push_back(pair.first);
    }
    return nodes;
}

// Añade una arista (y los nodos si no existen)
void Graph::addEdge(string src, string dest, int weight, bool directed)
{
    // Se asegura que los nodos existan (aunque en tu main ya están predefinidos, es buena práctica)
    addNode(src);
    addNode(dest);

    // Añade la arista de origen a destino
    adjList[src].push_back(make_pair(dest, weight));

    if (!directed)
    { // Si el grafo es no dirigido, añade la arista de vuelta
        adjList[dest].push_back(make_pair(src, weight));
    }
}

// Imprime el grafo
/*void Graph::printGraph()
{
    for (auto &node : adjList)
    {
        cout << "Nodo " << node.first << " -> ";
        for (auto &neighbor : node.second)
        {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}*/

// En Graph.cpp

void Graph::printGraph()
{
    // El título "Mapa de Conexiones" ya se imprime en tu Menu.cpp,
    // así que aquí vamos directo al contenido.

    // Itera sobre cada nodo (ciudad) en el mapa
    for (auto &node : adjList)
    {
        // 'node.first' es el nombre de la ciudad de origen (ej. "Tegucigalpa")
        // 'node.second' es la lista de sus vecinos

        cout << "\nDesde [" << node.first << "]:" << endl;

        // Revisa si esta ciudad tiene conexiones
        if (node.second.empty())
        {
            cout << "  -> (No tiene conexiones registradas)" << endl;
        }
        else
        {
            // Si tiene, itera sobre cada vecino en la lista
            // 'neighbor' es un pair<string, int>
            for (auto &neighbor : node.second)
            {
                // 'neighbor.first' es el destino (ej. "San Pedro Sula")
                // 'neighbor.second' es el peso (ej. 240)

                // ¡AQUÍ ESTÁ EL CAMBIO!
                // Imprimimos CADA vecino en su propia línea
                cout << "  -> Conecta con [" << neighbor.first << "]";
                cout << " (Distancia: " << neighbor.second << " km)" << endl;
            }
        }
    }
}

// Devuelve la ruta más corta y su peso usando Dijkstra
pair<int, list<string>> Graph::dijkstraShortestPath(string start, string end)
{
    // ... (Implementación de Dijkstra es correcta, se mantiene) ...
    map<string, int> distances;
    map<string, string> predecessors;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    const int INF = 1e9;

    for (const auto &nodePair : adjList)
        distances[nodePair.first] = INF;
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int currentDist = pq.top().first;
        string u = pq.top().second;
        pq.pop();

        if (currentDist > distances[u])
            continue;
        if (u == end)
            break;

        for (const auto &neighborPair : adjList[u])
        {
            string v = neighborPair.first;
            int weight = neighborPair.second;

            if (distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
                pq.push({distances[v], v});
            }
        }
    }

    list<string> path;
    int totalWeight = distances[end];

    if (totalWeight == INF)
        return {-1, path};

    string currentNode = end;
    while (currentNode != start)
    {
        // Verificación para manejar el caso de nodo desconectado, aunque Dijkstra lo maneja con INF
        if (predecessors.find(currentNode) == predecessors.end())
        {
            return {-1, list<string>()}; // Ruta no encontrada
        }
        path.push_front(currentNode);
        currentNode = predecessors[currentNode];
    }
    path.push_front(start);
    return {totalWeight, path};
}