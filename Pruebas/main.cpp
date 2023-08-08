#include <iostream>
#include <vector>
#include <memory>

class Pagina {
public:
    int idBloque;
    std::string arraynombrepagina;
    std::string Contenido;

    Pagina(int id, const std::string& nombre, const std::string& contenido) : idBloque(id), arraynombrepagina(nombre), Contenido(contenido) {}
};

class Frame {
public:
    Pagina* pagina;
    bool referenced;
    bool dirty_bit;

    Frame() : pagina(nullptr), referenced(false), dirty_bit(false) {}
};

class BufferManager {
public:
    std::vector<Frame> Frames;
    int hand; // Puntero para el algoritmo CLOCK

    BufferManager(int numFrames) {
        Frames.reserve(numFrames);
        for (int i = 0; i < numFrames; ++i) {
            Frames.push_back(Frame());
        }
        hand = 0; // Inicializamos el puntero en la posición 0
    }

    // Función para obtener el siguiente frame según el algoritmo CLOCK
    Frame& getNextFrame() {
        while (true) {
            if (!Frames[hand].referenced) {
                return Frames[hand];
            } else {
                Frames[hand].referenced = false;
                hand = (hand + 1) % Frames.size(); // Avanzamos el puntero circularmente
            }
        }
    }

    // Función para cargar una página en el buffer usando el algoritmo CLOCK
    void cargarPagina(Pagina* pagina) {
        Frame& frame = getNextFrame();

        if (frame.pagina != nullptr && frame.dirty_bit) {
            // Aquí se podría realizar alguna acción para escribir la página modificada de vuelta al almacenamiento secundario
            // en caso de que el bit dirty_bit esté activo
            // Por simplicidad, en este ejemplo, no lo implementaremos.
        }

        frame.pagina = pagina;
        frame.referenced = true;
        frame.dirty_bit = false;
    }

    // Función para leer el contenido de una página desde el buffer pool
    std::string leerPagina(int idBloque) {
        for (Frame& frame : Frames) {
            if (frame.pagina != nullptr && frame.pagina->idBloque == idBloque) {
                frame.referenced = true; // Marcamos la página como referenciada
                return frame.pagina->Contenido;
            }
        }

        // Si la página no está en el buffer pool, aquí podrías cargarla desde el almacenamiento secundario y luego retornar el contenido.
        return "Página no encontrada en el buffer pool.";
    }

    // Función para escribir el contenido en una página del buffer pool
    void escribirPagina(int idBloque, const std::string& nuevoContenido) {
        for (Frame& frame : Frames) {
            if (frame.pagina != nullptr && frame.pagina->idBloque == idBloque) {
                frame.referenced = true; // Marcamos la página como referenciada
                frame.dirty_bit = true; // Marcamos la página como modificada (bit dirty activo)
                frame.pagina->Contenido = nuevoContenido;
                return;
            }
        }

        // Si la página no está en el buffer pool, aquí podrías cargarla desde el almacenamiento secundario y luego escribir el contenido.
        std::cout << "Página no encontrada en el buffer pool. No se puede escribir." << std::endl;
    }
};

int main() {
    // Ejemplo de uso de las clases con el algoritmo CLOCK y buffer pool de 4 frames
    BufferManager bufferManager(4);

    // Creamos las páginas
    Pagina pagina1(101, "Pagina_101", "Contenido de la página 101");
    Pagina pagina2(102, "Pagina_102", "Contenido de la página 102");
    Pagina pagina3(103, "Pagina_103", "Contenido de la página 103");
    Pagina pagina4(104, "Pagina_104", "Contenido de la página 104");
    Pagina pagina5(105, "Pagina_105", "Contenido de la página 105");
    Pagina pagina6(106, "Pagina_106", "Contenido de la página 106");
    Pagina pagina7(107, "Pagina_107", "Contenido de la página 107");
    Pagina pagina8(108, "Pagina_108", "Contenido de la página 108");

    // Creamos un vector para almacenar todas las páginas
    std::vector<Pagina*> paginas = {&pagina1, &pagina2, &pagina3, &pagina4, &pagina5, &pagina6, &pagina7, &pagina8};

    // Cargamos todas las páginas en el buffer pool
    for (Pagina* pagina : paginas) {
        bufferManager.cargarPagina(pagina);
    }

    // Accedemos al contenido de algunas páginas
    std::cout << "Contenido de la página 101 en el buffer pool: " << bufferManager.leerPagina(101) << std::endl;
    std::cout << "Contenido de la página 106 en el buffer pool: " << bufferManager.leerPagina(106) << std::endl;
    std::cout << "Contenido de la página 107 (segunda lectura) en el buffer pool: " << bufferManager.leerPagina(107) << std::endl;

    // Escribimos contenido en una página del buffer pool (simulando una escritura)
    bufferManager.escribirPagina(102, "Nuevo contenido para la página 102");
    std::cout << "Contenido de la página 102 después de la escritura en el buffer pool: " << bufferManager.leerPagina(102) << std::endl;

    return 0;
}