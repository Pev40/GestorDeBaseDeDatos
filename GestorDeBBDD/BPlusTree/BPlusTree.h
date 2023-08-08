#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "BPlusNodo.h"
#include "BPlusNodo.cpp"

#include <iostream>
#include <string>

using namespace std;

class BPlusTree
{
private:
    string nameTabla;  //tabla a la que pertenece el B+
    int grado; // Rango del árbol
    string direccionRaiz; // Puntero a la raíz del árbol
    string finalBPlusTree;
    BPlusNodo *ptrBplusNodoRaiz;

public:
    BPlusTree(int _grado, string _name_tabla, string _direccion_raiz);
    ~BPlusTree();
    void agregarNodo();
    void eliminarNodo();
    void reemplazarNodo();
};

#endif