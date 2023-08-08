#ifndef __BUFFERMANAGER_H__
#define __BUFFERMANAGERH__
#include "Frame.h"
class BufferManager {
public:
    std::vector<Frame> Frames;
    int manecilla; // Puntero para el algoritmo CLOCK
    BufferManager(int);
    Frame& getNextFrame();
    void cargarPagina(Pagina*);
    std::string leerPagina(int);
    void escribirPagina(int, const std::string&);
};
#endif

BufferManager::BufferManager(int numFrames) {
    Frames.reserve(numFrames);
    for (int i = 0; i < numFrames; ++i) {
        Frames.push_back(Frame());
    }
    manecilla = 0; // Inicializamos el puntero en la posición 0
}
// Función para obtener el siguiente frame según el algoritmo CLOCK
Frame& BufferManager::getNextFrame() {
    while (true) {
        if (!Frames[manecilla].referencia) {
            return Frames[manecilla];
        } else {
            Frames[manecilla].referencia = false;
            manecilla = (manecilla + 1) % Frames.size(); // Avanzamos el puntero circularmente
        }
    }
}
// Función para cargar una página en el buffer usando el algoritmo CLOCK
void BufferManager::cargarPagina(Pagina* pagina) {
    Frame& frame = getNextFrame();
    if (frame.pagina != nullptr && frame.dirty_bit) {
        // Aquí se podría realizar alguna acción para escribir la página modificada de vuelta al almacenamiento secundario
        // en caso de que el bit dirty_bit esté activo
        // Por simplicidad, en este ejemplo, no lo implementaremos.
    }
    frame.pagina = pagina;
    frame.referencia = true;
    frame.dirty_bit = false;
}
// Función para leer el contenido de una página desde el buffer pool
std::string BufferManager::leerPagina(int idBloque) {
    for (Frame& frame : Frames) {
        if (frame.pagina != nullptr && frame.pagina->idBloque == idBloque) {
            frame.referencia = true; // Marcamos la página como referenciada
            return frame.pagina->Contenido;
        }
    }
    // Si la página no está en el buffer pool, aquí podrías cargarla desde el almacenamiento secundario y luego retornar el contenido.
    return "Página no encontrada en el buffer pool.";
}
// Función para escribir el contenido en una página del buffer pool
void BufferManager::escribirPagina(int idBloque, const std::string& nuevoContenido) {
    for (Frame& frame : Frames) {
        if (frame.pagina != nullptr && frame.pagina->idBloque == idBloque) {
            frame.referencia = true; // Marcamos la página como referenciada
            frame.dirty_bit = true; // Marcamos la página como modificada (bit dirty activo)
            frame.pagina->Contenido = nuevoContenido;
            return;
        }
    }
    // Si la página no está en el buffer pool, aquí podrías cargarla desde el almacenamiento secundario y luego escribir el contenido.
    std::cout << "Página no encontrada en el buffer pool. No se puede escribir." << std::endl;
}