#ifndef __BUFFERPOOL_H__
#define __BUFFERPOOL_H__

#include <vector>
#include "Frame.h"

class BufferPool {
private:
    std::vector<Frame> pool;
    int poolSize;
    int clockHand;

public:
    BufferPool(int size);

    void cargarPagina(int pageId, std::string filename);
    void liberarPagina(int pageId);
    std::string leerPagina(int pageId);
    void escribirPagina(int pageId, std::string contenido);
    bool isPageInPool(int pageId);

private:
    Frame getFreeFrame();
    Frame getFrame(int pageId);
};
#endif
