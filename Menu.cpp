#include "Menu.hpp"
#include "Graph.hpp"


pair<string, string> selectCities(Graph &g)
{
    vector<string> availableNodes = g.getNodes();
    string origen, destino;
    int indiceOrigen, indiceDestino;
    bool seleccionValida;

    if (availableNodes.empty())
    {
        cout << "No hay ciudades en el mapa para seleccionar." << endl;
        return make_pair("", "");
    }

    // --- SELECCIÓN DE ORIGEN ---
    do
    {
        cout << "\nSeleccione el punto de ORIGEN:" << endl;
        for (size_t i = 0; i < availableNodes.size(); ++i)
        {
            cout << i + 1 << ". " << availableNodes[i] << endl;
        }
        cout << "Opcion: ";
        if (!(cin >> indiceOrigen) || indiceOrigen <= 0 || indiceOrigen > availableNodes.size())
        {
            cout << "Opción inválida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            seleccionValida = false;
        }
        else
        {
            seleccionValida = true;
        }
    } while (!seleccionValida);

    origen = availableNodes[indiceOrigen - 1];

    // --- SELECCIÓN DE DESTINO ---

    // Eliminar el origen de la lista para el destino
    availableNodes.erase(availableNodes.begin() + (indiceOrigen - 1));

    if (availableNodes.empty())
    {
        cout << "Solo hay una ciudad. No se puede establecer un destino diferente." << endl;
        return make_pair(origen, "");
    }

    do
    {
        cout << "\nSeleccione el punto de DESTINO:" << endl;
        for (size_t i = 0; i < availableNodes.size(); ++i)
        {
            cout << i + 1 << ". " << availableNodes[i] << endl;
        }
        cout << "Opcion: ";
        if (!(cin >> indiceDestino) || indiceDestino <= 0 || indiceDestino > availableNodes.size())
        {
            cout << "Opción inválida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            seleccionValida = false;
        }
        else
        {
            seleccionValida = true;
        }
    } while (!seleccionValida);

    destino = availableNodes[indiceDestino - 1];

    return make_pair(origen, destino);
}

void menu(){
    int seleccion;
    Graph g;
    // Las llamadas a addEdge también llaman implícitamente a addNode (buena práctica)
    g.addEdge("Tegucigalpa", "Comayagua", 50);
    g.addEdge("Tegucigalpa", "Danli", 80);
    g.addEdge("Comayagua", "El Progreso", 85);
    g.addEdge("Comayagua", "San Pedro Sula", 85);
    g.addEdge("El Progreso", "San Pedro Sula", 84);
    g.addEdge("San Pedro Sula", "La Ceiba", 130);
    g.addEdge("La Ceiba", "Tela", 60);
    g.addEdge("Danli", "Juticalpa", 110);
    g.addEdge("Juticalpa", "Trujillo", 300);
    g.addEdge("Trujillo", "Tela", 60);
    

    // Bucle principal para permitir múltiples operaciones
    do
    {
        cout << "====================================" << endl;
        cout << "           HonduMaps                " << endl;
        cout << "====================================" << endl;
        cout << "1. Ingresar nueva ciudad" << endl;
        cout << "2. Establecer conexiones y distancia" << endl;
        cout << "3. Consultar rutas" << endl;
        cout << "4. Mostrar mapa de conexiones" << endl;
        cout << "5. Salir" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione una opcion: ";
        if (!(cin >> seleccion))
        {
            cout << "\nEntrada invalida. Saliendo del programa." << endl;
            break;
        }

        // Limpia el buffer después de leer el entero (necesario si después hay un getline o la entrada del case 1)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (seleccion)
        {
        case 1:
        {
            string ciudad;
            cout << "====================================" << endl;
            cout << "         Ingresando ciudad          " << endl;
            cout << "====================================" << endl;
            cout << "Nombre de la nueva ciudad: ";
            getline(cin, ciudad); // Usa getline aquí, por eso se necesita el cin.ignore() arriba.
            g.addNode(ciudad);
            cout << "\nCiudad '" << ciudad << "' agregada." << endl;
            break;
        }
        case 2:
        {
            string origen, destino;
            int distancia;

            cout << "====================================" << endl;
            cout << "      Establecer conexiones         " << endl;
            cout << "====================================" << endl;

            pair<string, string> selection = selectCities(g);
            origen = selection.first;
            destino = selection.second;

            if (origen.empty() || destino.empty())
            {
                cout << "\nOperación cancelada o sin suficientes ciudades." << endl;
                break;
            }

            // --- INGRESO DE DISTANCIA ---
            cout << "\nIngrese la distancia (peso) entre " << origen << " y " << destino << ": ";
            cin >> distancia;

            // Añadir la conexión
            g.addEdge(origen, destino, distancia);
            cout << "\nConexión de " << origen << " a " << destino << " con distancia " << distancia << " establecida." << endl;
            break;
        }
        case 3:
        {
            cout << "====================================" << endl;
            cout << "      Consultar Ruta Más Corta      " << endl;
            cout << "====================================" << endl;

            // Uso de la función auxiliar para obtener origen y destino
            pair<string, string> selection = selectCities(g);
            string origen = selection.first;
            string destino = selection.second;

            if (origen.empty() || destino.empty())
            {
                cout << "\nOperación cancelada o sin suficientes ciudades." << endl;
                break;
            }

            // Ejecutar Dijkstra
            pair<int, list<string>> result = g.dijkstraShortestPath(origen, destino);
            int totalWeight = result.first;
            list<string> path = result.second;

            cout << "\n--- RESULTADO DE LA BUSQUEDA ---\n";

            if (totalWeight == -1)
            {
                cout << "No se encontro ninguna ruta entre " << origen << " y " << destino << "." << endl;
            }
            else
            {
                cout << "Ruta Unica (Mas Corta):" << endl;
                cout << " - ";

                for (const string &city : path)
                {
                    cout << city;
                    if (city != destino)
                    {
                        cout << " -> ";
                    }
                }
                cout << endl;

                cout << " - Peso total: " << totalWeight << " km" << endl;
            }

            break;
        }
        case 4:
        {
            cout << "====================================" << endl;
            cout << "      Mapa de Conexiones            " << endl;
            cout << "====================================" << endl;
            g.printGraph();
            break;
        }
        case 5:
        {
            cout << "\nSaliendo del programa. ¡Hasta pronto!" << endl;
            break;
        }
        default:
        {
            cout << "\nOpcion invalida. Intente de nuevo." << endl;
            break;
        }
        }
    } while (seleccion != 5);
}