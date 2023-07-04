#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include <vector>
#include <functional>
#include "pagina.h"
#include "disco_duro.h"

class BufferManager {
public:
    // Definición de tipo para la función de reemplazo
    using AlgoritmoReemplazo = std::function<int(const std::vector<Pagina>&)>;

    // Constructor
    BufferManager(int bufferSize, AlgoritmoReemplazo algoritmoReemplazo);

    // Obtener una página del buffer
    Pagina& obtenerPagina(int numeroPagina);

private:
    // Tamaño del buffer
    int bufferSize;

    // Buffer de páginas
    std::vector<Pagina> buffer;

    // Función de reemplazo de páginas
    AlgoritmoReemplazo algoritmoReemplazo;

    // Buscar una página en el buffer
    std::vector<Pagina>::iterator buscarPagina(int numeroPagina);

    // Disco duro asociado al buffer
    DiscoDuro discoDuro;
};

#endif  // BUFFER_MANAGER_H
