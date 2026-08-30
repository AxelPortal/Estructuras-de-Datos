//
// Created by axelr on 30/08/2026.
//

#ifndef ESTRUCTURAS_VECTOR_H
#define ESTRUCTURAS_VECTOR_H

// Guarda datos iguales (del mismo tipo)
// Ocupa posiciones contiguas de memoria
// Dinámico (hasta cierto punto)

// Vector -- Funciones soportadas
// - Inserción/Eliminación:
//   * Al inicio: O(n)
//   * Al "medio": O(n)
//   * Al final: O(1)
// - Acceso: Con Arreglo[indice] O(1)
// - Búsqueda: O(n)
//

#include<iostream>
using namespace::std;

template<typename T>
struct Vector {
    int sz;
    int cap;
    T* data;

    Vector() {
        sz = 0;
        cap = 1;
        data = new T[1];
    }

    ~Vector() {
        delete[] data;
    }

    void resize(int len) {
        int new_cap = cap; // Nueva capacidad
        while (new_cap < len) new_cap <<= 1; // Para crecer
        while (new_cap >= 2 and (new_cap >> 1) >= len) new_cap >>= 1; // Para decrecer
        T* new_data = new T[new_cap];
        for (int i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        cap = new_cap;
    }

    void push_back(T value) {
        if (sz == cap) {
            resize(2 * cap);
        }
        // Inserción sin redimensionamiento
        data[sz++] = value;
    }

    void pop_back() {
        --sz;
        if (cap > 1 and sz <= cap / 4) {
            resize(cap / 2);
        }
    }

    int size() {
        return sz;
    }

    int capacity() {
        return cap;
    }

    T& operator [] (const int &idx) const {
        return data[idx];
    }
};

void print(Vector<int> &a) {
    for (int i = 0; i < a.size(); ++i) {
        cout << a[i] << " \n"[i + 1 == a.size()];
    }
}


#endif //ESTRUCTURAS_VECTOR_H