#include "BufferPool.h"
#include "Pagina.h"
#include "Frame.h"
BufferPool::BufferPool(int size) : poolSize(size), clockHand(0)
{
    pool.resize(size);
}

void BufferPool::cargarPagina(int pageId, std::string filename)
{
    if (isPageInPool(pageId))
    {
        return;
    }

    Frame frame = getFreeFrame();
    Page *page = new Page(pageId);
    page->load(filename);

    frame.page = page;
    frame.page->pin_count++;
    frame.ref_bit = true;
}

// Valida que la página esté en el pool
void BufferPool::liberarPagina(int pageId)
{

    if (!isPageInPool(pageId))
    {
        throw std::runtime_error("Page not loaded in buffer pool");
    }

    Frame frame = getFrame(pageId);
    frame.page->pin_count--;

    if (frame.page->pin_count == 0)
    {
        frame.ref_bit = false;
    }
}

std::string BufferPool::leerPagina(int pageId)
{
    Frame frame = getFrame(pageId);
    frame.ref_bit = true;
    return frame.page->content;
}

void BufferPool::escribirPagina(int pageId, std::string contenido)
{
    Frame frame = getFrame(pageId);
    frame.page->content = contenido;
    frame.page->dirty_bit = true;
    frame.ref_bit = true;
}

bool BufferPool::isPageInPool(int pageId)
{
    for (Frame frame : pool)
    {
        if (frame.page && frame.page->page_id == pageId)
        {
            return true;
        }
    }

    return false;
}

BufferPool::Frame BufferPool::getFreeFrame()
{
    for (Frame &frame : pool)
    {
        if (frame.page == nullptr)
        {
            return frame;
        }
    }
    clockAlgorithm();
    return getFreeFrame();
}

// Lanza excepción si no encuentra la página
BufferPool::Frame BufferPool::getFrame(int pageId)
{

    for (Frame &frame : pool)
    {
        if (frame.page && frame.page->page_id == pageId)
        {
            return frame;
        }
    }

    throw std::runtime_error("Page not found in buffer pool");
}
Frame BufferPool::getFreeFrame()
{
    while (true)
    {
        if (!pool[clockHand].page || !pool[clockHand].reference_bit)
        {
            return pool[clockHand];
        }
        else
        {
            pool[clockHand].reference_bit = false;
            clockHand = (clockHand + 1) % poolSize;
        }
    }
}

Frame BufferPool::getFrame(int pageId)
{
    while (true)
    {
        if (pool[clockHand].page && pool[clockHand].page->page_id == pageId)
        {
            return pool[clockHand];
        }
        else
        {
            pool[clockHand].reference_bit = false;
            clockHand = (clockHand + 1) % poolSize;
        }
    }
}
