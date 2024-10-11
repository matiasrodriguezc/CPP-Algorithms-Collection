#include <iostream>
#include <string>
#include <list>
#include <map>
#include "materia.h"

using namespace std;

struct Estado
{
    Materia materia;
    int comision;
};

bool son_compatibles(Estado materia_1, Estado materia_2, int c1,int c2)
{
    list<comision> lista_com1;
    materia_1.materia.getComisiones(lista_com1);
    typename list<comision>::iterator it = lista_com1.begin();
    while (it->nroComision < c1)
    {
        it++;
    }

    list<comision> lista_com2;
    materia_2.materia.getComisiones(lista_com2);
    typename list<comision>::iterator it2 = lista_com2.begin();
    while (it->nroComision < c1)
    {
        it2++;
    }

    if (*it1.comienzoDeLaClase == *it2.comienzoDeLaClase)
        return false;
    return true;
}

bool Hoja(Estado materia_Actual, list<Materia> materias)
{
    if (materia_Actual.materia.getNombreMateria() == materias.front().getNombreMateria())
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Hijos(Estado materia_Actual, int nroHijo, Estado & siguiente, list<Materia> materias)
{
    list<comision> lista_comisiones;
    materia_Actual.materia.getComisiones(lista_comisiones);
    if (nroHijo > lista_comisiones.size()-1)
    {
        return false; // ya no hay hijos disponibles (se acabaron las comisiones)
    }
    else
    {
        typename list<Materia>::iterator it = materias.begin();
        while (it != materias.end() && *it.getNombreMateria() != materia_Actual.materia.getNombreMateria())
        {
            it++;
        }
        it++;
        if (it != materias.end())
        {
            siguiente.materia = *it; // asi obtenemos el siguiente estado
            siguiente.comision = nroHijo;
        }
    }
}

int backtracking(list<map<string,comision>> & combinacionesPosibles, list<Materia> materias, map<string, comision> & combinacionPosible, Estado materia_Actual)
{
    if (Hoja(materia_Actual, materias))
        combinacionesPosibles.push_back(combinacionPosible);
    else
    {
        int nroHijo = 0;
        Estado materia_Siguiente;
        while (Hijos(materia_Actual, nroHijo, materia_Siguiente, materias, nro_comision))
        {
            combinacionPosible.insert(pair<string, comision> (materia_Siguiente.materia.getNombreMateria(), ))
            if (son_compatibles(materia_Actual, materia_Siguiente, materia_Actual.comision, materia_Siguiente.comision))
            {
                backtracking(combinacionesPosibles, materias, combinacionPosible, materia_Siguiente);
            }
            combinacionPosible.erase(materia_Siguiente.materia.getNombreMateria());
            nroHijo++
        }
    }
}

void imprimirSolucion(list<map<string,comision>> solucion){
    list<map<string,comision>>::iterator iteradorLista = solucion.begin();
    map<string,comision> combinacion;
    map<string,comision>::iterator iteradorMateria;
    comision c;
    while(iteradorLista != solucion.end()){
        combinacion = *iteradorLista;
        iteradorMateria = combinacion.begin();
        cout << "Combinacion Posible :" << endl;
        while(iteradorMateria != combinacion.end()){
            c = iteradorMateria->second;
            cout << "Materia: " << iteradorMateria->first << " -- Comision :" << c.nroComision << endl;
            iteradorMateria++;
        }
        cout << "------------------" << endl;
        iteradorLista++;
    }
}

void imprimirMenu(){
    cout << "Organizador de comisiones : " << endl;
    cout << "--------------------------" << endl;
    cout << "1. Imprimir las materias con sus respectivas comisiones" << endl;
    cout << "2. Imprimir todas las combinaciones posibles para cursar sin superposicion de horarios" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "----------------------" << endl;
    cout << "Elija una de las siguientes opciones : ";
}

void imprimirMaterias(list<Materia> materias){
    list<Materia>::iterator iterador = materias.begin();
    cout << "Materias : " << endl;
    cout << "-----------------------" << endl;
    while(iterador != materias.end()){
        Materia m = *iterador;
        cout << m.getNombreMateria() << endl;
        m.imprimirComisiones();
        cout << "-----------------------" << endl;
        iterador++;
    }
}

int main()
{
    /*
    Instancias de la clase Materia
    */

    Materia m1 = Materia("Programacion 1");
    Materia m2 = Materia("Web 1");
    Materia m3 = Materia("Ingles 1");
    Materia m4 = Materia("Taller de Matematica Computacional");

    /*
    Agrego comisiones
    */

    //Programacion 1
    comision c;
    c.dia = "Lunes";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1500;
    c.finDeLaClase = 1800;
    m1.agregarComision(c);

    c.dia = "Lunes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1800;
    c.finDeLaClase = 2100;
    m1.agregarComision(c);

    c.dia = "Miercoles";
    c.nroComision = 2;
    c.comienzoDeLaClase = 1500;
    c.finDeLaClase = 1800;
    m1.agregarComision(c);

    //Web 1
    c.dia = "Lunes";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1700;
    c.finDeLaClase = 1900;
    m2.agregarComision(c);

    c.dia = "Lunes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1000;
    c.finDeLaClase = 1200;
    m2.agregarComision(c);

    //Ingles 1
    c.dia = "Jueves";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1000;
    c.finDeLaClase = 1200;
    m3.agregarComision(c);

    c.dia = "Martes";
    c.nroComision = 1;
    c.comienzoDeLaClase = 1400;
    c.finDeLaClase = 1600;
    m3.agregarComision(c);

    //Taller de Matematica Computacional
    c.dia = "Jueves";
    c.nroComision = 0;
    c.comienzoDeLaClase = 1100;
    c.finDeLaClase = 1300;
    m4.agregarComision(c);



    list<map<string,comision>> combinacionesPosibles; //donde voy a devolver las soluciones del BACK
    list<Materia> materias;

    materias.push_back(m1);
    materias.push_back(m2);
    materias.push_back(m3);
    materias.push_back(m4);

    list<Materia>::iterator it = materias.begin();

    /*
    Menu
    */

    int opcion = -1;
    string auxiliar;
    while(opcion != 0){
        system("cls");
        imprimirMenu();
        cin >> opcion;
        system("cls");
        switch (opcion)
        {
            case 1:
                imprimirMaterias(materias);
                cout << "Ingrese cualquier caracter para volver al menu: " ;
                cin >> auxiliar;
                break;
            case 2:
                map<string, comision> combinacionPosible;
                Estado materia_Actual;
                backtracking(combinacionesPosibles, materias, combinacionPosible, materia_Actual);
                imprimirSolucion(combinacionesPosibles);
                combinacionesPosibles.clear();
                cout << "Ingrese cualquier caracter para volver al menu: ";
                cin >> auxiliar;
                break;
            case 0:
                cout << "Cerrando programa" << endl;
                break;
            default:
                cout << "Ha ingresado una opcion incorrecta" << endl;
                cout << "Ingrese cualquier caracter para volver al menu: ";
                cin >> auxiliar;
                break;
        }
    }

    return 0;
}

