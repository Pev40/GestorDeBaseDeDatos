#ifndef __SUPERFICIE_H__
#define __SUPERFICIE_H__
#include "Pista.h"
class Superficie {
private:
    int numero;
    int num_pistas;
    Pista* pistas;

public:
    Superficie();
    Superficie(int, int, int, int);
    ~Superficie();

    int getNumero();
    int getNumPistas();
    Pista* getPistas(int index);
};

Superficie::Superficie(int num, int num_pistas,int num_sectores, int num_bytes_sector) {
    numero = num;
    this->num_pistas = num_pistas;
    pistas = new Pista[num_pistas];
    for (int i = 0; i < num_pistas; i++) {
        pistas[i] = Pista(i+1, num_sectores,num_bytes_sector);
    }
}

Superficie::~Superficie() {
    delete[] pistas;
}

int Superficie::getNumero() {
    return numero;
}

int Superficie::getNumPistas() {
    return num_pistas;
}

Pista* Superficie::getPistas(int index) {
    return &pistas[index];
}

#endif