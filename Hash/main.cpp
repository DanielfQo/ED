#include<iostream>
#include"Hash.h"

using namespace std;

int main() {

    TablaHash<std::string, int> tabla(10);

    tabla.insertar("Gato", 1);
    tabla.insertar("Perro", 2);
    tabla.insertar("Caballo", 3);
    tabla.insertar("Ave", 4);

    std::cout << "Mostrando tabla" << std::endl;
    tabla.mostrarTabla();

    int* valor = tabla.buscar("Gato");
    if (valor != nullptr) {
        std::cout << "Valor encontrado: " << *valor << std::endl;
    } else {
        std::cout << "Clave no encontrada" << std::endl;
    }

    valor = tabla.buscar("Pez");
    if (valor != nullptr) {
        std::cout << "Valor encontrado: " << *valor << std::endl;
    } else {
        std::cout << "Clave no encontrada" << std::endl;
    }

    tabla.eliminar("Perro");

    std::cout << "Mostrando tabla" << std::endl;
    tabla.mostrarTabla();

    return 0;
}