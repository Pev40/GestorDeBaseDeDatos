#ifndef __PLATO_H__
#define __PLATO_H__
#include "Superficie.h"

class Plato {
private:
    int num_superficies;
    Superficie* superficies;

public:
    Plato();
    Plato(int,int,int);
    ~Plato();
    Superficie& getSuperficie(int num_superficie);
};


Plato::Plato(int num_pistas, int num_sectores,int tamano) {
    this->num_superficies = 2;
    superficies = new Superficie[this->num_superficies];
    for (int i = 0; i < num_superficies; i++) {
        superficies[i] = Superficie(i,num_pistas, num_sectores,tamano);
    }
}

Plato::~Plato() {
    delete[] superficies;
}

Superficie& Plato::getSuperficie(int num_superficie) {
    return superficies[num_superficie];
}

#endif
