#include "BPlusNodo.h"

BPlusNodo::BPlusNodo(int grado, bool esHoja, string direc_siguienteNodoHoja)
{
    this->es_hoja = esHoja;
    this->direc_siguiente_nodo_hoja = direc_siguienteNodoHoja;

    // Inicializar vectores según el rango
    if (this->es_hoja)
    {
        // Si es un nodo hoja, inicializar los vectores de registros
        this->direcciones_registros.reserve(grado-1); // Reservar espacio para 'grado-1' registros
        this->keys.reserve(grado-1);                  // Reservar espacio para 'grado-1' claves
    }
    else
    {
        // Si es un nodo interno, inicializar los vectores de direcciones a nodos internos y claves
        this->direcciones_nodos_internos.reserve(grado); // Reservar espacio para 'grado' direcciones de nodos internos
        this->keys.reserve(grado-1);                           // Reservar espacio para 'grado-1' claves
    }
}

BPlusNodo::~BPlusNodo(){}