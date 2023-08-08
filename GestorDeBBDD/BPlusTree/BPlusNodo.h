#ifndef BPLUSNODO_H
#define BPLUSNODO_H

#include <iostream>
#include <vector>

using namespace std;

class BPlusNodo {
private:
    // Vector de direcciones a nodos internos
    //string: direccion_nodo_interno
    std::vector<string> direccionesNodosInternos;

    // Vector de claves
    //string: keys
    std::vector<string> keys;

    // Vector de direcciones a registros
    //string: direccion_registro
    std::vector<string> direccionesRegistros;

    // Booleano que indica si el nodo es hoja
    bool esHoja;

    // Dirección del siguiente nodo hoja
    //string: direccion_nodo_hoja
    string direcSiguienteHoja;

public:
    BPlusNodo(int _grado, bool _esHoja, string _direcSiguienteNodoHoja);
    ~BPlusNodo();

};


#endif