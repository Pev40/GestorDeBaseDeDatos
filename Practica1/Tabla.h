#ifndef __TABLA_H__
#define __TABLA_H__
#include "CampoTabla.h"
#include <iostream>
using namespace std;
class Tabla
{
private:
    std::string NombreTabla = "NOMBRETABLA";
    CampoTabla* head = nullptr;
    int cantidadAtributo = 0;
    Tabla* next = nullptr;
public:
    Tabla(string);
    void add(string,string);
    void deleteA(string);
    bool search(string);
    void print();
    void setNext(Tabla*);
    Tabla* getNext();
    CampoTabla* getCampoTabla();
    int getCantidadAtributos();
    string getNombreTabla();
    string exportTabla();
    string viewTabla();
    ~Tabla();
};

Tabla::Tabla(std::string NombreTablaNuevo)
{
    this->NombreTabla = NombreTablaNuevo;
    this->head =nullptr;
}

void Tabla::add(string NombreCampo, string Atributo){
    if(this->head==nullptr){
        CampoTabla* nuevo = new CampoTabla(NombreCampo,Atributo);
        this->head=nuevo;
        this->cantidadAtributo = 1;
        return;
    }
    CampoTabla* auxiliar = head;
    while (true)
    {
        if(auxiliar->getNext() == nullptr){
            CampoTabla* nuevo = new CampoTabla(NombreCampo,Atributo);
            auxiliar->setNext(nuevo);
            this->cantidadAtributo = this->cantidadAtributo + 1;
            return;
        }
        auxiliar = auxiliar->getNext();
    }
    return;
}

bool Tabla::search(string NombreCampo){
    CampoTabla* auxiliar = head;
    while (auxiliar!=nullptr)
    {
        //std::cout<<auxiliar->getDato();
        if(auxiliar->getNombreDato()==NombreCampo){
      //      std::cout<<"Existe";
            return true;}
        auxiliar = auxiliar->getNext();
    }
    //std::cout<<"No existe";
    return false;
}

void Tabla::deleteA(string NombreCampo){
    if(head==nullptr){ return;}
    if(head->getNombreDato()==NombreCampo){
        CampoTabla* auxiliarelim = head;
        head=head->getNext();
        auxiliarelim->eliminar();
        delete[] auxiliarelim;
        return;
    }   
    CampoTabla* auxiliar = head;
    if (search(NombreCampo)==true)
{
    while (auxiliar!=nullptr )
    {
        if(auxiliar->getNext()->getNombreDato()==NombreCampo){
            break;
        }
        if(auxiliar->getNext()==nullptr){return;}
        auxiliar = auxiliar->getNext();
    }

    if(auxiliar->getNext()->getNext()==nullptr){
        CampoTabla* auxiliarelim = auxiliar->getNext();
        auxiliar->eliminar();
        auxiliarelim->eliminar();
        delete[] auxiliarelim;
        return;
    }
    CampoTabla* auxiliarelim = auxiliar->getNext();
    auxiliar->setNext(auxiliar->getNext()->getNext());
    auxiliarelim->eliminar();
    delete[] auxiliarelim;
    return;
}
return;
}

void Tabla::print(){
   // std::cout<<"Aqui en imprimir";
    if (head==nullptr){std::cout<<"No existen atributos en esta tabla"<<std::endl; return; }
    std::cout<<"Tabla "<<this->NombreTabla<<std::endl;
    CampoTabla* auxiliar = head;    
    while (auxiliar!=nullptr)
    {
        std::cout<<(auxiliar->getNombreDato())<<"-"<<(auxiliar->getAtributo())<<std::endl;
        auxiliar=auxiliar->getNext();
    }
    
}

Tabla* Tabla::getNext(){return this->next;}

void Tabla::setNext(Tabla* NuevaTabla){this->next=NuevaTabla;  return;}

string Tabla::getNombreTabla(){return this->NombreTabla;}

string Tabla::exportTabla(){
    CampoTabla* auxiliar = head;
    string cadenaExportable = this->NombreTabla; 
    while (auxiliar!=nullptr)
    {
        cadenaExportable = cadenaExportable + " # "+auxiliar->getNombreDato()+" # "+auxiliar->getAtributo();
        if(auxiliar->getNext() == nullptr){
            return cadenaExportable;
        }
        auxiliar = auxiliar->getNext();
    }
    //std::cout<<"No existe";
    return cadenaExportable;    
}


string Tabla::viewTabla(){
    CampoTabla* auxiliar = head;
    string cadenaExportable = "Nombre De Tabla:  "+this->NombreTabla+"\n"; 
    cadenaExportable = cadenaExportable + "Atributo\tTipo\n";
    while (auxiliar!=nullptr)
    {
        cadenaExportable = cadenaExportable +auxiliar->getNombreDato()+"\t"+auxiliar->getAtributo()+"\t\n";
        if(auxiliar->getNext() == nullptr){
            return cadenaExportable;
        }
        auxiliar = auxiliar->getNext();
    }
    //std::cout<<"No existe";
    return cadenaExportable;    
}

CampoTabla* Tabla::getCampoTabla(){return this->head;}

int Tabla::getCantidadAtributos(){return this->cantidadAtributo;}

Tabla::~Tabla()
{
}



#endif