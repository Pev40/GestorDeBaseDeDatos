#ifndef __FRAMEINDIVIDUAL_H__
#define __FRAMEINDIVIDUAL_H__

#include "Pagina.h"

class FrameIndividual {
public:
    Pagina* pagina;
    bool ref_bit;

    FrameIndividual() {
        pagina = nullptr;
        ref_bit = false;
    }
};

#endif