#include "MRU.h"

using namespace std;

int main(){

    MRU<char> cache(4);
    cache.insertar('c');
    cache.mostrarCache();
    cache.insertar('a');
    cache.mostrarCache();
    cache.insertar('d');
    cache.mostrarCache();
    cache.insertar('b');
    cache.mostrarCache();
    cache.insertar('e');
    cache.mostrarCache();
    cache.insertar('b');
    cache.mostrarCache();
    cache.insertar('a');
    cache.mostrarCache();
    cache.insertar('b');
    cache.mostrarCache();
    cache.insertar('c');
    cache.mostrarCache();
    cache.insertar('d');
    cache.mostrarCache();

    // c a d b e b a b c d

}