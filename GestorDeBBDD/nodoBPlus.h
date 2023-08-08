#ifndef __NODOBPLUS_H__
#define __NODEBPLUS_H__

#include "arbolBPlus.h"
#include <iostream>
#include <vector>


// Clase para representar un nodo del árbol B+
class NodeBPlus {
public:
    // Constructor
    NodeBPlus();

private:
    bool is_leaf_; // Indica si el nodo es una hoja o no
    int order_; // Orden del árbol B+
    std::vector<int> keys_; // Claves almacenadas en el nodo
    std::vector<NodeBPlus*> children_; // Punteros a los nodos hijos (nodos internos)
    std::vector<std::string*> values_; // Punteros a los valores (solo en nodos hoja)

    friend class ArbolBPlus;
};

#endif
