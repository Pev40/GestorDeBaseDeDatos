#ifndef __BUFFERMANAGER_H__
#define __BUFFERMANAGERH__
#include "BufferPool.cpp"
#include "BPlusTree/BTree.h"
#include "../GestorDeMemoriaFisica/DiscoDuro.h"
class BufferManager {
private:
    BufferPool bufferPool;
    BTree tree;
    DiscoDuro& disco;

public:
    BufferManager(int poolSize);
    
    void cargarRegistro(int IdRegistro);
    void liberarPagina(int pageId);
    std::string leerPagina(int pageId);
    void escribirPagina(int pageId, std::string contenido);

private:
    void clockAlgorithm();
};
#endif

BufferManager::BufferManager(int poolSize, DiscoDuro& discoDuro) : bufferPool(poolSize), disco(discoDuro) {
    // Resto del código del constructor
    BTree arbol;
    std::string archivoEstructura = "../diccionario.txt"; // Cambiar por el nombre de tu archivo

    arbol.cargarArchivoEnArbol(archivoEstructura); // Llama al nuevo método del árbol
    std::cout << "Valor Buscado: " << arbol.search_values_get_idPage(1) << std::endl;
    std::cout << "Valor Buscado: " << arbol.search_values_get_directPage(2) << std::endl;

    tree = arbol; // Asignación del árbol
}


void BufferManager::cargarRegistro(int IdRegistro) {
    std::cout<<IdRegistro<<std::endl;
    int pageId = tree.search_values_get_idPage(IdRegistro);
    if (pageId == 0)
    {
       std::cout << "No se encontro ese valor";
       return;

    }
    
    std::cout<<pageId<<std::endl;
    std::string filename = tree.search_values_get_directPage(IdRegistro);
     std::cout<<filename<<std::endl;
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
    int originalClockHand = bufferPool.clockHand; // Almacenar la posición original

    do {
        FrameIndividual& frame = bufferPool.pool[bufferPool.clockHand];
        std::cout << "Aqui en Clock" << std::endl;

        if (!frame.ref_bit) {
            if (frame.pagina && frame.pagina->pin_count == 0) {
                frame.pagina->dirty_bit = false;
                frame.pagina = nullptr;
                frame.ref_bit = false;
                return; // Encontramos una página para liberar, salimos del bucle
            }
        } else {
            frame.ref_bit = false;
        }

        bufferPool.clockHand = (bufferPool.clockHand + 1) % bufferPool.poolSize;
    } while (bufferPool.clockHand != originalClockHand); // Volvemos al punto de partida

    // Si llegamos aquí, no encontramos ninguna página para liberar
    // en el bucle completo, lo que significa que todas las páginas están fijadas o con bit de referencia
}
