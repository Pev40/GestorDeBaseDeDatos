#ifndef __BUFFERPOOL_H__
#define __BUFFERPOOL_H__

#include <vector>
#include "FrameIndividual.h"
#include "Pagina.h"

class BufferPool {
private:

    std::vector<FrameIndividual> pool;
    int poolSize;
    int clockHand;
public:
    BufferPool(int size);

    bool cargarPagina(int pageId, std::string filename, int slock);
    void liberarPagina(int pageId);
    std::string leerPagina(int pageId);
    void escribirPagina(int pageId, std::string contenido);
    bool isPageInPool(int pageId);

private:
   FrameIndividual getFreeFrame(); 
   FrameIndividual getFrame(int pageId);

};
#endif
