#ifndef __DISCODURO_H__
#define __DISCODURO_H__

#include "Plato.h"

class DiscoDuro {
private:
    int num_platos;
    Plato* platos;

public:
    DiscoDuro(int num_platos, int num_pistas, int num_sectores);
    ~DiscoDuro();
    Plato& getPlato(int num_plato);
};

DiscoDuro::DiscoDuro(int num_platos, int num_pistas, int num_sectores) {
    this->num_platos = num_platos;
    platos = new Plato[num_platos];
    for (int i = 0; i < num_platos; i++) {
        platos[i] = Plato(num_pistas, num_sectores);
    }
}

DiscoDuro::~DiscoDuro() {
    delete[] platos;
}

Plato& DiscoDuro::getPlato(int num_plato) {
    return platos[num_plato];
}

#endif
