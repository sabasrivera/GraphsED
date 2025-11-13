#include "Menu.hpp"
#include "Graph.hpp"

pair<string, string> seleccionarCiudades(Grafo &g)
{
    vector<string> nodosDisponibles = g.obtenerNodos();
    string origen, destino;
    int indiceOrigen, indiceDestino;
    bool seleccionValida;

    if (nodosDisponibles.empty())
    {
        cout << "No hay ciudades en el mapa para seleccionar." << endl;
        return make_pair("", "");
    }

    // Seleccion de origen
    do
    {
        cout << "\nSeleccione el punto de ORIGEN:" << endl;
        for (size_t i = 0; i < nodosDisponibles.size(); ++i)
        {
            cout << i + 1 << ". " << nodosDisponibles[i] << endl;
        }
        cout << "Opcion: ";
        if (!(cin >> indiceOrigen) || indiceOrigen <= 0 || indiceOrigen > nodosDisponibles.size())
        {
            cout << "Opcion no permitida intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            seleccionValida = false;
        }
        else
        {
            seleccionValida = true;
        }
    } while (!seleccionValida);

    origen = nodosDisponibles[indiceOrigen - 1];

    // Seleccin de destino
    nodosDisponibles.erase(nodosDisponibles.begin() + (indiceOrigen - 1));

    if (nodosDisponibles.empty())
    {
        cout << "Solo hay una ciudad o no se puede establecer un destino diferente." << endl;
        return make_pair(origen, "");
    }

    do
    {
        cout << "\nSeleccione el punto de DESTINO:" << endl;
        for (size_t i = 0; i < nodosDisponibles.size(); ++i)
        {
            cout << i + 1 << ". " << nodosDisponibles[i] << endl;
        }
        cout << "Opcion: ";
        if (!(cin >> indiceDestino) || indiceDestino <= 0 || indiceDestino > nodosDisponibles.size())
        {
            cout << "Opcion no permitida intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            seleccionValida = false;
        }
        else
        {
            seleccionValida = true;
        }
    } while (!seleccionValida);

    destino = nodosDisponibles[indiceDestino - 1];

    return make_pair(origen, destino);
}

void menu()
{
    int seleccion;
    Grafo g;
    g.agregarArista("Tegucigalpa", "Comayagua", 50);
    g.agregarArista("Tegucigalpa", "Danli", 80);
    g.agregarArista("Comayagua", "El Progreso", 85);
    g.agregarArista("Comayagua", "San Pedro Sula", 85);
    g.agregarArista("El Progreso", "San Pedro Sula", 84);
    g.agregarArista("San Pedro Sula", "La Ceiba", 130);
    g.agregarArista("La Ceiba", "Tela", 60);
    g.agregarArista("Danli", "Juticalpa", 110);
    g.agregarArista("Juticalpa", "Trujillo", 300);
    g.agregarArista("Trujillo", "Tela", 60);

    do
    {
        cout << "====================================" << endl;
        cout << "           RUTAS MAPAS                  " << endl;
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
            cout << "\nEntrada no permitida programa finalizado." << endl;
            break;
        }

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
            getline(cin, ciudad);
            g.agregarNodo(ciudad);
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

            pair<string, string> seleccionCiudades = seleccionarCiudades(g);
            origen = seleccionCiudades.first;
            destino = seleccionCiudades.second;

            if (origen.empty() || destino.empty())
            {
                cout << "\nOperacion cancelada o sin suficientes ciudades." << endl;
                break;
            }

            cout << "\nIngrese la distancia entre " << origen << " y " << destino << ": ";
            cin >> distancia;

            g.agregarArista(origen, destino, distancia);
            cout << "\nConexion de " << origen << " a " << destino << " con distancia " << distancia << " establecida." << endl;
            break;
        }
        case 3:
        {
            cout << "====================================" << endl;
            cout << "      Consultar Ruta Mas Corta      " << endl;
            cout << "====================================" << endl;

            pair<string, string> seleccionCiudades = seleccionarCiudades(g);
            string origen = seleccionCiudades.first;
            string destino = seleccionCiudades.second;

            if (origen.empty() || destino.empty())
            {
                cout << "\nOperacion cancelada o sin suficientes ciudades." << endl;
                break;
            }

            pair<int, list<string>> resultado = g.caminoMasCortoDijkstra(origen, destino);
            int distanciaTotal = resultado.first;
            list<string> camino = resultado.second;

            cout << "\n--- RESULTADO DE LA BUSQUEDA ---\n";

            if (distanciaTotal == -1)
            {
                cout << "No se encontro ninguna ruta entre " << origen << " y " << destino << "." << endl;
            }
            else
            {
                cout << "Ruta Unica (Mas Corta):" << endl;
                cout << " - ";

                for (const string &ciudad : camino)
                {
                    cout << ciudad;
                    if (ciudad != destino)
                    {
                        cout << " -> ";
                    }
                }
                cout << endl;
                cout << " - Distancia total: " << distanciaTotal << " km" << endl;
            }
            break;
        }
        case 4:
        {
            cout << "====================================" << endl;
            cout << "      Mapa de Conexiones            " << endl;
            cout << "====================================" << endl;
            g.imprimirGrafo();
            break;
        }
        case 5:
        {
            cout << "\nSaliendo del programa Hasta pronto" << endl;
            break;
        }
        default:
        {
            cout << "\nOpcion invalida Intente de nuevo" << endl;
            break;
        }
        }
    } while (seleccion != 5);
}
