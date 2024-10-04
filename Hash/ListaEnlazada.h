#include <iostream>

template <typename K, typename V>
class Nodo {
public:
    K clave;
    V valor;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(K c, V v) : clave(c), valor(v), siguiente(nullptr), anterior(nullptr) {}
};

template <typename K, typename V>
class ListaDobleEnlazada {
private:
    Nodo<K, V>* head;

public:
    ListaDobleEnlazada() : head(nullptr) {}

    void insertarNodo(K clave, V valor);
    V* buscarValor(K clave);
    void eliminarNodo(K clave);
    void mostrarLista();
};

template <typename K, typename V>
void ListaDobleEnlazada<K, V>::insertarNodo(K clave, V valor) {
    Nodo<K, V>* nuevoNodo = new Nodo<K, V>(clave, valor);
    if (head == nullptr) {
        head = nuevoNodo;
        return;
    }
    Nodo<K, V>* temp = head;
    while (temp->siguiente != nullptr) {
        temp = temp->siguiente;
    }
    temp->siguiente = nuevoNodo;
    nuevoNodo->anterior = temp;
}

template <typename K, typename V>
V* ListaDobleEnlazada<K, V>::buscarValor(K clave) {
    Nodo<K, V>* temp = head;
    while (temp != nullptr) {
        if (temp->clave == clave) {
            return &(temp->valor); 
        }
        temp = temp->siguiente;
    }
    return nullptr;
}

template <typename K, typename V>
void ListaDobleEnlazada<K, V>::eliminarNodo(K clave) {
    Nodo<K, V>* temp = head;
    while (temp != nullptr) {
        if (temp->clave == clave) {
            if (temp->anterior != nullptr) {
                temp->anterior->siguiente = temp->siguiente;
            } else {
                head = temp->siguiente;
            }
            if (temp->siguiente != nullptr) {
                temp->siguiente->anterior = temp->anterior;
            }
            delete temp;
            return;
        }
        temp = temp->siguiente;
    }
}

template <typename K, typename V>
void ListaDobleEnlazada<K, V>::mostrarLista() {
    Nodo<K, V>* temp = head;
    while (temp != nullptr) {
        std::cout << "[" << temp->clave << ": " << temp->valor << "] ";
        temp = temp->siguiente;
    }
    std::cout << std::endl;
}