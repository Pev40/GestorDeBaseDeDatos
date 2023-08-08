#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include "Pagina.h"
#include "Pagina.cpp"

#include <iostream>
#include <map>

using namespace std;

class BufferPool
{
private:
    int num_frames;
    map<int,Pagina> MapFramesBufPool;
public:
    BufferPool(int num_frames);
    BufferPool();
    ~BufferPool();

    //Otras funciones:
    Pagina& get_pagina(int id_pag);
    void agregar_pagina(Pagina &pagina,int id_pag);
    void eliminar_pagina(int id_pag);
    void replace_pagina(Pagina &pagina,int id_pag);
    void mostrarBufferPool();
};

#endif