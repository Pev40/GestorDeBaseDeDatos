#include "BPlusTree.h"

BPlusTree::BPlusTree(int _grado, string _name_tabla, string _direccion_raiz){
    this->grado=_grado;
    if (this->direccionRaiz==("-1"))
    {
        cout<<"- Reparame - Verificar exitencia del B+Tree"<<endl;
        //ayudate con el nombre
    }
    else
    {
        this->nameTabla=_name_tabla;
        this->direccionRaiz=_direccion_raiz;
        //el this->finalbplustree se define mientras se realiza el arbol en el sector
        BPlusNodo bplusnodo(this->grado,true,0);
        (*ptrBplusNodoRaiz)=bplusnodo;
    }
}

BPlusTree::~BPlusTree(){}