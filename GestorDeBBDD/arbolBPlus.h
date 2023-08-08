#ifndef __ARBOLBPLUS_H__
#define __ARBOLBPLUS_H__

#include "nodoBPlus.h"
#include <iostream>
#include <vector>


// Clase para representar el árbol B+
class ArbolBPlus {
public:
    // Constructor
    ArbolBPlus(int order);

    // Destructor
    ~ArbolBPlus();

    // Método para insertar una clave y valor en el árbol
    void insert(int key, const std::string& value);

    // Método para buscar una clave en el árbol
    bool search(int key, std::string& value) const;

private:
    int order_; // Orden del árbol B+
    NodeBPlus* root_; // Puntero a la raíz del árbol

    // Métodos auxiliares para la inserción y búsqueda
    void insertNonFull(NodeBPlus* node, int key, const std::string& value);
    void splitChild(NodeBPlus* parent, int child_index);
    bool searchInNode(const NodeBPlus* node, int key, std::string& value) const;
};

