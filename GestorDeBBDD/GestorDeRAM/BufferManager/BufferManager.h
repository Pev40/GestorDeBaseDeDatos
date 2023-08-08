#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

// #include "../BufferPool/Pagina.h"
// #include "../BufferPool/Pagina.cpp"

#include "../BufferPool/BufferPool.h"
#include "../BufferPool/BufferPool.cpp"

#include "TablaMetadata.h"
#include "TablaMetadata.cpp"

// #include "../../DiskManager/DiskManager.h"
#include "../../DiskManager/DiskManager.cpp"


#include <list>
#include <queue>
#include <iostream>
#include <unordered_map>

using namespace std;

class BufferManager
{
private:
    BufferPool bufferPool;
    TablaMetadata tablaMetadata;
    Pagina paginaRetornar;
    int num_frames; // Tamaño máximo del Buffer Pool
    DiskManager diskManager;
public:
    BufferManager(int input);
    BufferManager();
    ~BufferManager();

    void set_num_frames(int input);
    void apuntar_buffPool();
    void apuntar_tablaMetadata();
    void apuntar_diskManager();

    Pagina& get_pagina_retornar();
    void agregarPagina_BuffPool_tablaMetadata(int id_pag);
    void mostrar_tabla_metadata();


    // /*-------------LRU--------------*/
    // void inicializar_buffer_pool(vector<Pagina> &Buffer_pool_vect);
    // void LRU(vector<Pagina> &Buffer_pool_vect,int page_id);
    // int encontrar_page_Buffer_Pool(vector<Pagina> _Buffer_pool_vect,int page_id);

    // vector<Pagina>& get_buffer_pool();
    // friend class Programa;
    
};

#endif