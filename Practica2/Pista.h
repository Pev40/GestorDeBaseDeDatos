#ifndef __PISTA_H__
#define __PISTA_H__
#include "Sector.h"
class Pista {
private:
    int numero;
    int num_sectores;
    Sector* sectores;

public:
    Pista();
    Pista(int,int,int);
    ~Pista();

    int getNumero();
    int getNumSectores();
    Sector* getSectores(int index);
};

Pista::Pista(int num, int num_sec, int tamano) {
    numero = num;
    num_sectores = num_sec;
    sectores = new Sector[num_sec];
    for (int i = 0; i < num_sec; i++) {
        sectores[i] = Sector(i+1, tamano);
    }
}

Pista::~Pista() {
    delete[] sectores;
}

int Pista::getNumero() {
    return numero;
}

int Pista::getNumSectores() {
    return num_sectores;
}

Sector* Pista::getSectores(int index) {
    return &sectores[index];
}

#endif
