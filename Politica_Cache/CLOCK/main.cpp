#include<iostream>
#include "Clock.h"

int main() {
    Clock<char> cache(3);

    cache.insertar('A');
    cache.insertar('B');
    cache.insertar('C');
    cache.imprimirBuffer();

    cache.insertar('D');
    cache.imprimirBuffer();

    cache.insertar('E');
    cache.imprimirBuffer();

    cache.insertar('C');
    cache.imprimirBuffer();

    cache.insertar('A');
    cache.imprimirBuffer();

    return 0;
}