#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

template <typename K, typename V>
class Buckets {
private:
    int profundidadLocal;
    std::vector<std::pair<K, V>> datos;

public:
    Buckets(int profundidadLocal) : profundidadLocal(profundidadLocal) {}

    bool estaLleno(int tamanoBucket) {
        return datos.size() >= tamanoBucket;
    }

    void insertar(const K& clave, const V& valor) {
        datos.push_back({clave, valor});
    }

    bool buscar(const K& clave) {
        for (const auto &par : datos) {
            if (par.first == clave) {
                return true;
            }
        }
        return false;
    }

    void eliminar(const K& clave) {
        for (auto it = datos.begin(); it != datos.end(); ++it) {
            if (it->first == clave) {
                datos.erase(it);
                return;
            }
        }
    }

    int size() const {
        return datos.size();
    }

    const std::vector<std::pair<K, V>>& getDatos() const {
        return datos;
    }

    void clear() {
        datos.clear();
    }

    int getProfundidadLocal() const {
        return profundidadLocal;
    }

    void incrementarProfundidadLocal() {
        profundidadLocal++;
    }
};

template <typename K, typename V>
class ExtendibleHash {
private:
    int profundidadGlobal;
    int tamanoBucket;
    std::vector<Buckets<K, V>> buckets;
    std::vector<int> directorio;

    int hash(const K& clave) {
        return std::hash<K>{}(clave) & ((1 << profundidadGlobal) - 1);
    }

    void dividirBucket(int indiceBucket) {
        int profundidadLocal = buckets[indiceBucket].getProfundidadLocal();
        buckets[indiceBucket].incrementarProfundidadLocal();
        int nuevoIndiceBucket = buckets.size();
        buckets.push_back(Buckets<K, V>(profundidadLocal + 1));

        auto &datosViejos = buckets[indiceBucket].getDatos();
        std::vector<std::pair<K, V>> datosNuevos;

        for (const auto &par : datosViejos) {
            if (hash(par.first) != indiceBucket) {
                buckets[nuevoIndiceBucket].insertar(par.first, par.second);
            } else {
                datosNuevos.push_back(par);
            }
        }

        buckets[indiceBucket].clear();
        for (const auto &par : datosNuevos) {
            buckets[indiceBucket].insertar(par.first, par.second);
        }

        for (int i = 0; i < directorio.size(); ++i) {
            if (directorio[i] == indiceBucket && (i & (1 << profundidadLocal))) {
                directorio[i] = nuevoIndiceBucket;
            }
        }

        if (profundidadLocal == profundidadGlobal) {
            profundidadGlobal++;
            directorio.resize(1 << profundidadGlobal);
            for (int i = 0; i < (1 << (profundidadGlobal - 1)); ++i) {
                directorio[i + (1 << (profundidadGlobal - 1))] = directorio[i];
            }
        }
    }

public:
    ExtendibleHash(int tamanoBucket) : profundidadGlobal(1), tamanoBucket(tamanoBucket) {
        buckets.push_back(Buckets<K, V>(1));
        buckets.push_back(Buckets<K, V>(1));
        directorio.push_back(0);
        directorio.push_back(1);
    }

    void insertar(const K& clave, const V& valor) {
        int indiceBucket = directorio[hash(clave)];
        if (buckets[indiceBucket].estaLleno(tamanoBucket)) {
            dividirBucket(indiceBucket);
            indiceBucket = directorio[hash(clave)];
        }
        buckets[indiceBucket].insertar(clave, valor);
    }

    bool buscar(const K& clave) {
        int indiceBucket = directorio[hash(clave)];
        return buckets[indiceBucket].buscar(clave);
    }

    void eliminar(const K& clave) {
        int indiceBucket = directorio[hash(clave)];
        buckets[indiceBucket].eliminar(clave);
    }

    void imprimir() {
        for (int i = 0; i < buckets.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto &par : buckets[i].getDatos()) {
                std::cout << "(" << par.first << ", " << par.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};
