#include <iostream>
#include <vector>
#include <algorithm>

const int MAXNODOS = 3;

class NodoBPTree {
public:
    bool esHoja;
    std::vector<int> claves;
    std::vector<NodoBPTree*> hijos;
    NodoBPTree* siguiente;

    NodoBPTree(bool hoja);
    void insertarNoLleno(int clave);
    void dividirHijo(int i, NodoBPTree* y);
    NodoBPTree* buscar(int clave);
};

class BPTree {
public:
    NodoBPTree* raiz;
    BPTree();
    void insertar(int clave);
    NodoBPTree* buscar(int clave);
};

NodoBPTree::NodoBPTree(bool hoja) {
    esHoja = hoja;
    siguiente = nullptr;
}

void NodoBPTree::insertarNoLleno(int clave) {
    int i = claves.size() - 1;

    if (esHoja) {
        claves.push_back(0);
        while (i >= 0 && claves[i] > clave) {
            claves[i + 1] = claves[i];
            i--;
        }
        claves[i + 1] = clave;
    } else {
        while (i >= 0 && claves[i] > clave) {
            i--;
        }
        i++;
        if (hijos[i]->claves.size() == MAXNODOS) {
            dividirHijo(i, hijos[i]);
            if (claves[i] < clave) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(clave);
    }
}

void NodoBPTree::dividirHijo(int i, NodoBPTree* y) {
    NodoBPTree* z = new NodoBPTree(y->esHoja);
    z->claves.resize(MAXNODOS / 2);

    for (int j = 0; j < MAXNODOS / 2; j++) {
        z->claves[j] = y->claves[j + MAXNODOS / 2 + 1];
    }

    if (!y->esHoja) {
        z->hijos.resize(MAXNODOS / 2 + 1);
        for (int j = 0; j < MAXNODOS / 2 + 1; j++) {
            z->hijos[j] = y->hijos[j + MAXNODOS / 2 + 1];
        }
    }

    y->claves.resize(MAXNODOS / 2);
    hijos.insert(hijos.begin() + i + 1, z);
    claves.insert(claves.begin() + i, y->claves[MAXNODOS / 2]);
}

NodoBPTree* NodoBPTree::buscar(int clave) {
    int i = 0;
    while (i < claves.size() && clave > claves[i]) {
        i++;
    }

    if (i < claves.size() && claves[i] == clave) {
        return this;
    }

    if (esHoja) {
        return nullptr;
    }

    return hijos[i]->buscar(clave);
}

BPTree::BPTree() {
    raiz = new NodoBPTree(true);
}

void BPTree::insertar(int clave) {
    if (raiz->claves.size() == MAXNODOS) {
        NodoBPTree* s = new NodoBPTree(false);
        s->hijos.push_back(raiz);
        s->dividirHijo(0, raiz);
        int i = 0;
        if (s->claves[0] < clave) {
            i++;
        }
        s->hijos[i]->insertarNoLleno(clave);
        raiz = s;
    } else {
        raiz->insertarNoLleno(clave);
    }
}

NodoBPTree* BPTree::buscar(int clave) {
    if (raiz == nullptr) {
        return nullptr;
    } else {
        return raiz->buscar(clave);
    }
}

int main() {
    BPTree arbol;
    arbol.insertar(10);
    arbol.insertar(20);
    arbol.insertar(5);
    arbol.insertar(6);
    arbol.insertar(12);
    arbol.insertar(30);
    arbol.insertar(7);
    arbol.insertar(17);

    int clave = 6;
    if (arbol.buscar(clave) != nullptr) {
        std::cout << "\nPresente";
    } else {
        std::cout << "\nNo Presente";
    }

    clave = 15;
    if (arbol.buscar(clave) != nullptr) {
        std::cout << "\nPresente";
    } else {
        std::cout << "\nNo Presente";
    }

    return 0;
}
