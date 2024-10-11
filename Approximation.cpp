#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>

#define CANT_PAQUETES  10

using namespace std;


/**
ENUNCIADO:
Una empresa de logística tiene que enviar N paquetes de una ciudad a otra.
Cada paquete ocupa un volumen Vi, con 1 mts3 < Vi < 100 mts3.
La empresa cuenta con varios camiones de 100mts3 de capacidad pero desea MINIMIZAR
la cantidad de camiones que deben viajar.

Considerando solo el volumen de los paquetes SIN considerar su forma, escribir un algoritmo
de aproximación en C++ para determinar cuántos camiones deben viajar y cómo
se deben distribuir los paquetes en cada camión.

*/


struct Paquete {
    int idPaquete;
    int volumen;
    bool operator < (const Paquete &other) const { return idPaquete < other.idPaquete; }
};


struct Camion {
    int idCamion;
    int capacidad;
    vector<int> packs;
};


void cargar_paquetes(list<Paquete> & paquetes){

    int capacidades[CANT_PAQUETES] = {23, 52, 12, 71, 63, 96, 7, 19, 47, 76};
      cout << "PAQUETES: " << endl;
    for (int i=0; i < CANT_PAQUETES ; i++){
        Paquete p = {i+1, capacidades[i]};
        cout << "Paquete: " << p.idPaquete << " (" << p.volumen <<")"<< endl;
        paquetes.push_back(p);
    }

}

void inic_camiones(list<Camion> & camiones){

    int nro_camion = 1;
    while (nro_camion <= CANT_PAQUETES){
        Camion c;
        c.idCamion = nro_camion;
        c.capacidad = 100;
        camiones.push_back(c);
        nro_camion++;
    }
}

// completar con un algoritmo de costo polinomial, donde se cargue en la lista "camiones" la distribucion de los paquetes
 // y en "max_camiones_usados" la cantidad de camiones a utilizar
bool algoritmo_aprox(list<Paquete> paquetes, list<Camion> & camiones, int & max_camiones_usados)
{
    /**Basado en Bin Packing Best Fit. Para que haya el menor desperdicio posible. Ya que en este caso, el desperdicio llevaría a la utilizacion de mayor cantidad de camiones.**/
    bool tiene_solucion = false;
    list<Paquete>::const_iterator it;
    set<int> camiones_usados; //El size de este set donde se guardan los id de los camiones utilizados se usa para obtener la cantidad de camiones utilizados. Aprovechando la caracteristica de los sets de no guardar dos elementos iguales, cada id se guardará una unica vez.
    for (it = paquetes.cbegin(); it != paquetes.cend(); it++) //mientras haya paquetes por acomodar
    {
        list<Camion>::iterator itC = camiones.begin(); //Recorre todos los camiones
        list<Camion>::iterator itCamionMenorDesperdicio; //Apuntara al Camion con menor desperdicio
        float menorDesperdicio = 0;
        while (itC != camiones.end()) //Busca entre todos los camiones.
        {
            if ( (it->volumen <= itC->capacidad) && (itC->capacidad + it->volumen < menorDesperdicio || menorDesperdicio == 0)) //Si el camion apuntado tiene lugar para guardar el paquete y se obtiene un menor desperdicio, lo apunta
            {
                menorDesperdicio = itC->capacidad + it->volumen; //se actualiza el menorDesperdicio
                itCamionMenorDesperdicio = itC; //se apunta al camion elegido hasta el momento
            }
            itC++;
        }
        if (menorDesperdicio != 0) //Si menorDesperdicio cambió, encontró al menos un camión donde entra el paquete. Por ende, agrego el paquete al camion
        {
            itCamionMenorDesperdicio->packs.push_back(it->idPaquete); //Agrego el ID del paquete al vector packs del camion
            itCamionMenorDesperdicio->capacidad -= it->volumen; //Actualizo la capacidad libre del camion
            camiones_usados.insert(itCamionMenorDesperdicio->idCamion); //Agrego el Id del camion al conjunto de Id's.
        }
        else //si el paquete no entra en ninguno de los camiones, el problema no tiene solucion.
        {
            return tiene_solucion;
        }
    }
    max_camiones_usados = camiones_usados.size();
    tiene_solucion = true;
    return tiene_solucion;

}

void mostrar_resultado(list<Camion> camiones, int max_camiones_usados){

    cout << endl << "---------------------------" << endl;
    cout << "ALG.DE APROXIMACION" << endl;
    cout << "Cantidad de camiones: " << max_camiones_usados << endl;
    cout << "---------------------------" << endl << endl;
    cout << "CAMIONES CARGADOS: " << endl <<endl;


    list<Camion>::iterator itc = camiones.begin();
    int aux_cant_camiones = 1;
    while (itc != camiones.end() && (aux_cant_camiones <= max_camiones_usados)){

        cout << " Camion: " << itc->idCamion << " Espacio libre->"<< itc->capacidad << endl;
        vector<int>::iterator itPacks = itc->packs.begin();
        while (itPacks != itc->packs.end() && *itPacks > 0){
            cout << " - Paquete: " << *itPacks << endl;
            itPacks++;
         }
        aux_cant_camiones++;
        itc++;
    }

}

int main()
{
    list<Paquete> paquetes;
    cargar_paquetes(paquetes);

    list<Camion> camiones;
    inic_camiones(camiones);

    int max_camiones_usados = 0;

    // Llamado al algormitmo de aproximación que toma como entada el conjunto de paquetes
    // y los asigna en la lista de camiones, donde queda el resultado.
    if (algoritmo_aprox(paquetes, camiones, max_camiones_usados)) {
        mostrar_resultado(camiones, max_camiones_usados);
    } else {
        cout << endl << "NO TIENE SOLUCION !!" << endl;
    }

    return 0;
}
