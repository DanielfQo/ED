#ifndef BLOQUE_H
#define BLOQUE_H

#include "Pagina.h"
#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Bloque{
    private:
        int numeroPaginas;
        vector<Pagina> paginas;
    public:
        Bloque(int cantPaginas, int cantRegistros){
            numeroPaginas = cantPaginas;
            for(int i = 0; i < cantPaginas; i++){
                Pagina pagina(cantRegistros);
                paginas.push_back(pagina);
            }
        }
        bool insertarRegistro(pair<int,string> registro){
            for(int i = 0; i < paginas.size(); i++){
                if(paginas[i].insertarRegistro(registro)){
                    return true;
                }
            }
            return false;
        }
        bool buscarRegistro(int id){
            for(int i = 0; i < paginas.size(); i++){
                if(paginas[i].buscarRegistro(id)){
                    return true;
                }
            }
            return false;
        }
        void mostrarBloque(){
            for(int i = 0; i < paginas.size(); i++){
                cout << "  Pagina "<< i+1 << endl;
                paginas[i].mostrarPagina();
            }
        }
    
};

#endif 