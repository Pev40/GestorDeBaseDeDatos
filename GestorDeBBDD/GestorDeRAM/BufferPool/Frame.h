#ifndef __FRAME_H__
#define __FRAME_H__

#include "Pagina.h"

class Frame {
public:
    Page* page;
    bool ref_bit;

    Frame() {
        page = nullptr;
        ref_bit = false;
    }
};

#endif