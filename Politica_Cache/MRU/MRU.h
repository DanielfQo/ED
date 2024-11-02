#pragma once

#include <iostream>
#include <unordered_map>
#include "ListaDobleEnlazada.h"

template <typename K>
class MRU{
private:

    int maxSize;
    std::unordered_map<K, Nodo<K>*> cache;

    ListaDobleEnlazada<K> pila;

public:

    MRU(int maxSize) : maxSize(maxSize) {}

    void insertar(K clave){

        if(cache.find(clave) != cache.end()){
            Nodo<K>* nodo = cache[clave];
            pila.eliminarNodoDirecto(nodo);
            cache.erase(clave);     
        }        

        if(pila.getSize() == maxSize){
            K clave_a_eliminar = pila.top()->clave; 
            pila.pop();
            cache.erase(clave_a_eliminar);
        }


        Nodo<K>* nodo = pila.push(clave);
        cache[clave] = nodo;
    }

    void mostrarCache(){
        pila.mostrarLista();
    }



};