#ifndef DISCO_H
#define DISCO_H

#include "Bloque.h"

#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Disco{
    private:
        int numeroBloques;
        vector<Bloque> bloques;
    public:
        Disco(int cantBloques, int cantPaginas, int cantRegistros){
            numeroBloques = cantBloques;
            for(int i = 0; i < cantBloques; i++){
                Bloque bloque(cantPaginas, cantRegistros);
                bloques.push_back(bloque);
            }
        }
        void insertarRegistro(pair<int,string> registro){
            for(int i = 0; i < bloques.size(); i++){
                if(bloques[i].insertarRegistro(registro)){
                    cout << "Registro insertado" << endl;
                    return;
                }
            }
            cout << "No se pudo insertar el registro" << endl;
        }
        void buscarRegistro(int id){
            for(int i = 0; i < bloques.size(); i++){
                if(bloques[i].buscarRegistro(id)){
                    cout << "Registro encontrado" << endl;
                    return;
                }
            }
            cout << "Registro no encontrado" << endl;
        }
        void mostrarDisco(){
            for(int i = 0; i < bloques.size(); i++){
                cout << "Bloque "<< i+1 << endl;
                bloques[i].mostrarBloque();
            }
        }

};



#endif // DISCO_H