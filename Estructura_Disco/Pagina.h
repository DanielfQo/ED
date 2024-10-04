#ifndef PAGINA_H
#define PAGINA_H

#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Pagina{
    private:
        int numeroRegistros;
        vector<pair<int,string>> registros;
    public:
        Pagina(int cant){
            numeroRegistros = cant;
        }
        bool insertarRegistro(pair<int,string> registro){
            if(registros.size() < numeroRegistros){
                registros.push_back(registro);
                return true;
            }
            return false;
        }
        bool buscarRegistro(int id){
            for(int i = 0; i < registros.size(); i++){
                if(registros[i].first == id){
                    return true;
                }
            }
            return false;
        }
        void mostrarPagina(){
            for(int i = 0; i < registros.size(); i++){
                cout << "    Registro " << i+1 << ": (" << registros[i].first << ", " << registros[i].second << ")" << endl;
            }
        }
    
};

#endif 