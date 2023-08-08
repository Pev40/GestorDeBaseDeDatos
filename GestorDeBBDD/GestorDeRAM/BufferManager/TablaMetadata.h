#ifndef TABLAMETADATA_H
#define TABLAMETADATA_H

#include "InfoFrameVector.h"
#include "InfoFrameVector.cpp"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class TablaMetadata
{
private:
    int num_frames_tabla;
    bool full_frames;   //para avisarnos si está lleno
    map<int,InfoFrameVector> mapFramesTabla;
public:
    TablaMetadata(int num_frames);
    TablaMetadata();
    ~TablaMetadata();

    //Otras funciones
    bool tabla_vacia();
    void agregar_frame_tabla(InfoFrameVector &vect_metadata,int id_frame);
    void imprimir_toda_tabla_metadata();
    void imprimir_un_frame(int id_frame);
    void increment_pinCount_pagina(int  idPagina);
    bool comprobar_existe_frame(int id_frame);
    bool comprobar_existe_pagina(int id_pag);
    void agregar_pagina_tabla_metadata(int id_pag);
    void decrement_pinCount_pagina(int idPagina);
    int get_id_frame_segun_idPagina(int idPagina);
    
    bool dirtyBit_clean(int idPagina);
    bool pinCount_clean(int idPagina);
    bool refBit_clean(int idPagina);
    void eliminar_pagina_metadata(int idPagina);
    void reemplazar_pagina_metadata(int idPaginaOld, int idPaginaNew);
    void update_dirtyBit(int idPagina);
    void update_refBit(int idPagina);

    void Reset_allRefBit_tablaMetadata();
    int CLOCK();
    
};

#endif