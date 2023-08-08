#ifndef __FRAME_H__
#define __FRAME_H__
#include "Pagina.h"
class Frame {
public:
    Pagina* pagina;
    bool referencia;
    bool dirty_bit;

    Frame() ;
};
#endif


Frame::Frame(): pagina(nullptr), referencia(false), dirty_bit(false) {}