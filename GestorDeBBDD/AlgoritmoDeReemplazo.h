#ifndef ALGORITMO_DE_REEMPLAZO_H
#define ALGORITMO_DE_REEMPLAZO_H

#include <functional>

class AlgoritmoDeReemplazo {
public:
    virtual int reemplazarPagina() = 0;
};

class FIFO : public AlgoritmoDeReemplazo {
public:
    int reemplazarPagina() override;
};

class LRU : public AlgoritmoDeReemplazo {
public:
    int reemplazarPagina() override;
};

class Clock : public AlgoritmoDeReemplazo {
public:
    int reemplazarPagina() override;
};

int FIFO::reemplazarPagina() {
    int numeroPaginaReemplazada = listaPaginas.front();  // Obtener el número de página más antiguo
    listaPaginas.pop();  // Eliminar el número de página más antiguo de la lista
    return numeroPaginaReemplazada;
}

int MRU::reemplazarPagina() {
    int numeroPaginaReemplazada = listaPaginas.back();  // Obtener el número de página más reciente
    listaPaginas.pop_back();  // Eliminar el número de página más reciente de la lista
    return numeroPaginaReemplazada;
}

int LRU::reemplazarPagina() {
    int numeroPaginaReemplazada = listaPaginas.front();  // Obtener el número de página menos reciente
    listaPaginas.pop_front();  // Eliminar el número de página menos reciente de la lista
    return numeroPaginaReemplazada;
}

int Clock::reemplazarPagina() {
    while (true) {
        int numeroPaginaActual = listaPaginas[manoReloj];  // Obtener el número de página actual
        if (!marcas[numeroPaginaActual]) {  // Si la página actual no está marcada
            listaPaginas[manoReloj] = -1;  // Marcar la página actual como disponible
            avanzarManoReloj();  // Avanzar la mano del reloj
            return numeroPaginaActual;  // Retornar el número de página a reemplazar
        } else {
            marcas[numeroPaginaActual] = false;  // Desmarcar la página actual
            avanzarManoReloj();  // Avanzar la mano del reloj
        }
    }
}

void Clock::avanzarManoReloj() {
    manoReloj = (manoReloj + 1) % listaPaginas.size();  // Avanzar la mano del reloj circularmente
}



#endif  // ALGORITMO_DE_REEMPLAZO_H
