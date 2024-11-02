#pragma once

#include <iostream>

template <typename K>
class Nodo {
public:
    K clave;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(K c) : clave(c), siguiente(nullptr), anterior(nullptr) {}
};

template <typename K>
class ListaDobleEnlazada {
private:
    Nodo<K>* head;
    Nodo<K>* tail;
    int size;

public:
    ListaDobleEnlazada() : head(nullptr), tail(nullptr), size(0) {}

    Nodo<K>* push(K clave);
    void pop();
    Nodo<K>* top();
    void mostrarLista();
    void eliminarNodoDirecto(Nodo<K>* nodo);
    int getSize() { return size; }
};

template <typename K>
Nodo<K>* ListaDobleEnlazada<K>::push(K clave) {
    Nodo<K>* nuevoNodo = new Nodo<K>(clave);
    if (head == nullptr) {
        head = tail = nuevoNodo;
    } else {
        nuevoNodo->siguiente = head;
        head->anterior = nuevoNodo;
        head = nuevoNodo;
    }
    size++;
    return nuevoNodo;
}

template <typename K>
void ListaDobleEnlazada<K>::pop() {
    if (head == nullptr) {
        std::cerr << "Stack vacio" << std::endl;
        return;
    }
    Nodo<K>* temp = head;
    head = head->siguiente;
    if (head != nullptr) {
        head->anterior = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    size--;
}

template <typename K>
Nodo<K>* ListaDobleEnlazada<K>::top() {
    if (head == nullptr) {
        throw std::out_of_range("Stack vacio");
    }
    return head;
}

template <typename K>
void ListaDobleEnlazada<K>::mostrarLista() {
    Nodo<K>* temp = head;
    while (temp != nullptr) {
        std::cout << "[" << temp->clave << "] ";
        temp = temp->siguiente;
    }
    std::cout << std::endl;
}

template <typename K>
void ListaDobleEnlazada<K>::eliminarNodoDirecto(Nodo<K>* nodo) {
    if (nodo == nullptr) {
        std::cerr << "Nodo nulo" << std::endl;
        return;
    }
    if (nodo->anterior != nullptr) {
        nodo->anterior->siguiente = nodo->siguiente;
    } else {
        head = nodo->siguiente;
    }
    if (nodo->siguiente != nullptr) {
        nodo->siguiente->anterior = nodo->anterior;
    } else {
        tail = nodo->anterior;
    }
    delete nodo;
    size--;
}