#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>
#include "ListaEnlazada.h"

template <typename K, typename V>
class TablaHash {
private:
    std::vector<ListaDobleEnlazada<K, V>> tabla;
    int capacidad;

    int hashFunc(K clave);

public:
    TablaHash(int cap);
    void insertar(K clave, V valor);
    V* buscar(K clave);
    void eliminar(K clave);
    void mostrarTabla();
};

template <typename K, typename V>
int TablaHash<K, V>::hashFunc(K clave) {
    return std::hash<K>{}(clave) % capacidad;
}

template <typename K, typename V>
TablaHash<K, V>::TablaHash(int cap) : capacidad(cap) {
    tabla.resize(capacidad);
}

template <typename K, typename V>
void TablaHash<K, V>::insertar(K clave, V valor) {
    int indice = hashFunc(clave);
    tabla[indice].insertarNodo(clave, valor);
}

template <typename K, typename V>
V* TablaHash<K, V>::buscar(K clave) {
    int indice = hashFunc(clave);
    return tabla[indice].buscarValor(clave);
}

template <typename K, typename V>
void TablaHash<K, V>::eliminar(K clave) {
    int indice = hashFunc(clave);
    tabla[indice].eliminarNodo(clave);
}

template <typename K, typename V>
void TablaHash<K, V>::mostrarTabla() {
    for (int i = 0; i < capacidad; ++i) {
        std::cout << "Indice " << i << ": ";
        tabla[i].mostrarLista();
    }
}
#endif