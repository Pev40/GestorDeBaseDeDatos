#include "BufferPool.h"
#include <iostream>
BufferPool::BufferPool(int size) : poolSize(size), clockHand(0)
{
    pool.resize(size);
}

bool BufferPool::cargarPagina(int paginaId, std::string filename)
{
    if (isPageInPool(paginaId))
    {
        return true;
    }

    FrameIndividual frame = getFreeFrame();
    if (frame == nullptr)
    {
      return false;
    }
    Pagina *pagina = new Pagina(paginaId);
    pagina->load(filename);

    frame.pagina = pagina;
    frame.pagina->pin_count++;
    frame.ref_bit = true;

    std::cout << "Ver Pagina: " << std::endl;
    frame.pagina->verContenido();

    // Insertar el frame en la posición especificada por el iterador
    this->pool.push_back(frame);
    return true;
}


// Valida que la página esté en el pool
void BufferPool::liberarPagina(int paginaId)
{

    if (!isPageInPool(paginaId))
    {
        throw std::runtime_error("pagina not loaded in buffer pool");
    }

    FrameIndividual frame = getFrame(paginaId);
    frame.pagina->pin_count--;

    if (frame.pagina->pin_count == 0)
    {
        frame.ref_bit = false;
    }
}

std::string BufferPool::leerPagina(int paginaId)
{
    FrameIndividual frame = getFrame(paginaId);
    frame.ref_bit = true;
    return frame.pagina->content;
}

void BufferPool::escribirPagina(int paginaId, std::string contenido)
{
    FrameIndividual frame = getFrame(paginaId);
    frame.pagina->content = contenido;
    frame.pagina->dirty_bit = true;
    frame.ref_bit = true;
}

bool BufferPool::isPageInPool(int paginaId)
{
    for (FrameIndividual frame : pool)
    {
        if (frame.pagina && frame.pagina->pagina_id == paginaId)
        {
            return true;
        }
    }

    return false;
}

// Código previo...

FrameIndividual BufferPool::getFreeFrame()
{

    for (FrameIndividual &frame : pool)
    {
        if (frame.pagina == nullptr)
        {
            std::cout << "Hay" << std::endl;
            return frame;
        }
    }
    // No hay frames libres
    throw std::out_of_range("No free frames");

    return nullptr;
}

FrameIndividual BufferPool::getFrame(int pageId)
{

    for (FrameIndividual &frame : pool)
    {
        if (frame.pagina && frame.pagina->pagina_id == pageId)
        {
            return frame;
        }
    }

    // No encontrada
    throw std::runtime_error("Page not found");
}

// Se quitan métodos de reloj

/*
FrameIndividual BufferPool::getFreeFrame()
{
    for (FrameIndividual &frame : pool)
    {
        if (frame.pagina == nullptr)
        {
            return frame;
        }
    }
    clockAlgorithm();
    return getFreeFrame();
}

// Lanza excepción si no encuentra la página
FrameIndividual BufferPool::getFrame(int paginaId)
{

    for (FrameIndividual &frame : pool)
    {
        if (frame.pagina && frame.pagina->pagina_id == paginaId)
        {
            return frame;
        }
    }

    throw std::runtime_error("pagina not found in buffer pool");
}


FrameIndividual BufferPool::getFreeFrame()
{
    while (true)
    {
        if (!pool[clockHand].pagina || !pool[clockHand].reference_bit)
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

FrameIndividual BufferPool::getFrame(int paginaId)
{
    while (true)
    {
        if (pool[clockHand].pagina && pool[clockHand].pagina->pagina_id == paginaId)
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
*/