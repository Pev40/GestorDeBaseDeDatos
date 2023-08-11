#ifndef __BUFFERMANAGER_H__
#define __BUFFERMANAGERH__
#include "BufferPool.cpp"
#include "BPlusTree/BTree.h"
class BufferManager {
private:
    BufferPool bufferPool;
    BTree tree;
public:
    BufferManager(int poolSize);
    
    void cargarRegistro(int pageId);
    void liberarPagina(int pageId);
    std::string leerPagina(int pageId);
    void escribirPagina(int pageId, std::string contenido);

private:
    void clockAlgorithm();
};
#endif

BufferManager::BufferManager(int poolSize) : bufferPool(poolSize) {
    BTree arbol;
    std::string archivoEstructura = "../diccionario.txt"; // Cambiar por el nombre de tu archivo

    arbol.cargarArchivoEnArbol(archivoEstructura); // Llama al nuevo método del árbol
    tree = arbol;
}

void BufferManager::cargarPagina(int numeroDelRegistro) {
    
    int pageId = tree.search_values_get_idPage(numeroDelRegistro);
    std::string filename = tree.search_values_get_directPage(numeroDelRegistro);
    clockAlgorithm();
    bufferPool.cargarPagina(pageId, filename);
}

void BufferManager::liberarPagina(int pageId) {
    bufferPool.liberarPagina(pageId);
}

std::string BufferManager::leerPagina(int pageId) {
    return bufferPool.leerPagina(pageId);
}

void BufferManager::escribirPagina(int pageId, std::string contenido) {
    bufferPool.escribirPagina(pageId, contenido);
}

void BufferManager::clockAlgorithm() {
    while (true) {
        FrameIndividual& frame = bufferPool.pool[bufferPool.clockHand];
        if (!frame.ref_bit) {
            if (frame.pagina && frame.pagina->pin_count == 0) {
                frame.pagina->dirty_bit = false;
                frame.pagina = nullptr;
                frame.ref_bit = false;
                return;
            }
        } else {
            frame.ref_bit = false;
        }
        bufferPool.clockHand = (bufferPool.clockHand + 1) % bufferPool.poolSize;
    }
}