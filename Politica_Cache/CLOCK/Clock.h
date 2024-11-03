#pragma once

#include <iostream>
#include <new>

template <typename T>
struct Nodo {
    T dato;
    int pin;
    Nodo* siguiente;
};

template <typename T>
class Clock {
    
private:

    Nodo<T>* buffer;
    Nodo<T>* pos;
    int size;
    int espacio;

public:

    Clock(int size) : size(size), buffer(NULL), pos(NULL), espacio(size) {}

    void insertar(T dato) {
        Nodo<T>* temp = buffer;
        bool found = false;

        if (buffer != NULL) {
            do {
                if (temp->dato == dato) {
                    temp->pin = 1;
                    found = true;
                    break;
                }
                temp = temp->siguiente;
            } while (temp != buffer);
        }

        if (!found) {
            if (espacio > 0) {
                Nodo<T>* nuevo = new Nodo<T>;
                nuevo->dato = dato;
                nuevo->pin = 1;

                if (buffer == NULL) {
                    nuevo->siguiente = nuevo;
                    buffer = nuevo;
                    pos = nuevo;
                } else {
                    nuevo->siguiente = buffer->siguiente;
                    buffer->siguiente = nuevo;
                    buffer = nuevo;
                }
                espacio--;
            } else {
                while (pos->pin == 1) {
                    pos->pin = 0;
                    pos = pos->siguiente;
                }
                pos->dato = dato;
                pos->pin = 1;
                pos = pos->siguiente;
            }
        }
    }

    void imprimirBuffer() {
        if (buffer == NULL) {
            std::cout << "Buffer vacio" << std::endl;
            return;
        }
        Nodo<T>* temp = buffer->siguiente;
        do {
            std::cout << "Dato: " << temp->dato << ", pin: " << temp->pin << std::endl;
            temp = temp->siguiente;
        } while (temp != buffer->siguiente);
        std::cout << std::endl;
    }

};

