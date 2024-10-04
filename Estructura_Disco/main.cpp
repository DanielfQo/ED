#include<iostream>

#include "Disco.h"

using namespace std;

int main(){
    Disco disco(3, 2, 2);
    int opcion;

    int id;
    string nombre;
    do{
        cout << "1. Insertar registro" << endl;
        cout << "2. Buscar registro" << endl;
        cout << "3. Mostrar disco" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        switch(opcion){
            case 1:
                cout << "Ingrese el id del registro: ";
                cin >> id;
                cout << "Ingrese el nombre del registro: ";
                cin >> nombre;
                disco.insertarRegistro(make_pair(id, nombre));
                break;
            case 2:
                cout << "Ingrese el id del registro a buscar: ";
                int idBuscar;
                cin >> idBuscar;
                disco.buscarRegistro(idBuscar);
                break;
            case 3:
                disco.mostrarDisco();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while(opcion != 4);
    
    return 0;
}