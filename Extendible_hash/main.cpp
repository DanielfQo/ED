#include <iostream>
#include "EHash.h"

using namespace std;

int main(){
    ExtendibleHash<char,int> ehash(3);

    ehash.insertar('A', 10);
    ehash.insertar('B', 20);
    ehash.insertar('C', 30);
    ehash.insertar('D', 40);
    ehash.insertar('E', 50);
    ehash.insertar('F', 60);
    ehash.insertar('G', 70);
    ehash.insertar('H', 80);
    ehash.insertar('I', 90);
    ehash.insertar('J', 100);

    std::cout << ehash.buscar('A') << std::endl;

    ehash.imprimir();

    ehash.eliminar('A');

    std::cout << ehash.buscar('A') << std::endl;

    ehash.imprimir();
    cout << "-------------------" << endl;

    ehash.insertar('A', 10);
    ehash.insertar('K', 110);
    ehash.insertar('L', 120);
    ehash.insertar('M', 130);
    ehash.insertar('M', 140);
    ehash.insertar('N', 150);
    ehash.insertar('R', 160);

    ehash.imprimir();



    return 0;
}