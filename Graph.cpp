#include "Grafo.h"
#include "iostream"
#include <vector>
#include <list>

using namespace std;

/*
Dado un grafo no orientado que modela las rutas de la provincia de Buenos Aires, devolver todos
los caminos alternativos que se pueden tomar para ir desde la ciudad de Buenos Aires a la ciudad
de Tandil, considerando que en el tramo Las Flores-Rauch está cortado al tránsito.
*/

template <typename C>
void mostrar_grafo(const Grafo<C> & grafo, vector<string> ciudades)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		cout << "\n    *** " << ciudades[*v] << " ***\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			cout << "    " << ciudades[*v] << "-> " << ciudades[ady->devolver_adyacente()] << " (" << ady->devolver_costo() << " kms)\n";
			ady++;
		}
		v++;
	}
}

template <typename C>
void cargar_grafo(Grafo<C> & g, vector<string> & ciudades){

  	// Cargamos un grafo no dirigido
	// Primero las ciudades
	g.agregar_vertice(1);
	ciudades[1] = "Tandil";
	g.agregar_vertice(2);
	ciudades[2] = "Las Flores";
	g.agregar_vertice(3);
	ciudades[3] = "Rauch";
	g.agregar_vertice(4);
	ciudades[4] = "Azul";
	g.agregar_vertice(5);
	ciudades[5] = "San Miguel del Monte";
	g.agregar_vertice(6);
	ciudades[6] = "Buenos Aires";
	g.agregar_vertice(7);
	ciudades[7] = "Canuelas";
    g.agregar_vertice(8);
	ciudades[8] = "Brandsen";
    g.agregar_vertice(9);
	ciudades[9] = "Ranchos";
	g.agregar_vertice(10);
	ciudades[10] = "Gral.Belgrano";
	g.agregar_vertice(11);
	ciudades[11] = "Ayacucho";
    g.agregar_vertice(12);
	ciudades[12] = "Cachari";
    g.agregar_vertice(13);
	ciudades[13] = "Tapalque";
	g.agregar_vertice(14);
	ciudades[14] = "Lobos";
	g.agregar_vertice(15);
	ciudades[15] = "Saladillo";

	// Luego las rutas
	g.agregar_arco(1, 3, 81);
	g.agregar_arco(3, 2, 82);
	g.agregar_arco(2, 5, 86);
	g.agregar_arco(5, 7, 42);
	g.agregar_arco(4, 1, 90);
	g.agregar_arco(6, 7, 63);
	g.agregar_arco(6, 8, 82);
	g.agregar_arco(8, 9, 42);
    g.agregar_arco(10, 9, 36);
    g.agregar_arco(10, 11, 163);
    g.agregar_arco(1, 11, 59);
    g.agregar_arco(3, 10, 207);
    g.agregar_arco(4, 12, 69);
    g.agregar_arco(12, 2, 73);
    g.agregar_arco(13, 4, 42);
    g.agregar_arco(13, 15, 72);
    g.agregar_arco(14, 15, 77);
    g.agregar_arco(14, 7, 37);

}

bool camino_cortado(int origen, int destino, int ciudad1, int ciudad2)
//en este caso, el camino cortado es el de Las Flores (2) y Rauch (3)
{
    if (((origen == ciudad1) && (destino == ciudad2)) || ((origen == ciudad2) && (destino == ciudad1)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename C>
void devolver_todos_caminos(const Grafo<C> & g, int origen, int destino, list<int> & camino_actual, set <int> visitados, list<list<int>> & caminos, int ciudad1, int ciudad2)
{
    visitados.insert(origen);
    camino_actual.push_back(origen);
    if (origen == destino)
    {
        caminos.push_back(camino_actual);
    }
    else
    {
        list<typename Grafo<C>::Arco> lista_adyacentes;
        g.devolver_adyacentes(origen, lista_adyacentes);
        typename list<typename Grafo<C>::Arco>::const_iterator it = lista_adyacentes.begin();
        while (it != lista_adyacentes.end())
        {
            if ((visitados.find(it->devolver_adyacente())== visitados.end()) && (! camino_cortado(origen, it->devolver_adyacente(), ciudad1, ciudad2)))
            {
                devolver_todos_caminos(g, it->devolver_adyacente(), destino, camino_actual, visitados, caminos, ciudad1, ciudad2);
            }
            it++;
        }
    }
    visitados.erase(visitados.find(origen));
    camino_actual.pop_back();
};

template <typename C>
void devolver_caminos(const Grafo<C> & g, int origen, int destino, list<list<int>> & caminos)
{
    list<int> camino_actual;
    set<int> visitados;
    int ciudad1 = 2;
    int ciudad2 = 3;//el tramo entre ciudad1 y ciudad2 esta cortado.
    devolver_todos_caminos(g, origen, destino, camino_actual, visitados, caminos, ciudad1, ciudad2);
}

int main(int argc, char **argv)
{
	Grafo<int> g;
	vector<string> ciudades = vector<string>(100, ""); //inicializo el vector suponiendo 100 ciudades
    cargar_grafo(g, ciudades);

	// Mostramos el grafo
	mostrar_grafo(g, ciudades);

    list<list<int> > caminos;
    //llamo a la funcion que debe encontrar los caminos entre Buenos Aires(6) y Tandil(1)
  	devolver_caminos(g, 6, 1, caminos);

    // Mostramos los resutados
	list<list<int> >::iterator it = caminos.begin();
    cout << "\n *** TODOS LOS CAMINOS *** \n";
	while (it != caminos.end()) {
       list<int>::iterator itCamino = it->begin();
       cout << "\n CAMINO:  ";
       while (itCamino != it->end()) {
         cout << ciudades[*itCamino] << " --> ";
         itCamino++;
        }
      it++;
	}
	 cout << "\n\n\n";
	return 0;
}
