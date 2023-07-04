#ifndef __ESQUEMA_H__
#define __ESQUEMA_H__
#include "Tabla.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
class Esquema
{
private:
    Tabla* head=nullptr;
public:
    Esquema();
    Esquema(std::string);
    void addTable(std::string);
    void addAtributo(std::string,std::string,std::string);
    Tabla* search(std::string NombreTabla);
    string exportString();    
    void exportEsquema(std::string);
    void viewSchemas();
    ~Esquema();
};

Esquema::Esquema()
{
    this->head =nullptr;
}

Esquema::Esquema(std::string NombreTabla)
{
    Tabla* nuevo = new Tabla(NombreTabla);
    this->head=nuevo;
    return;
}

void Esquema::addTable(string NombreTabla){
    if(this->head==nullptr){
        Tabla* nuevo = new Tabla(NombreTabla);
        this->head=nuevo;
        return;
    }
    Tabla* auxiliar = head;
    while (true)
    {
        if(auxiliar->getNext() == nullptr){
            Tabla* nuevo = new Tabla(NombreTabla);
            auxiliar->setNext(nuevo);
            return;
        }
        auxiliar = auxiliar->getNext();
    }
    return;
}

Tabla* Esquema::search(std::string NombreTabla){
    Tabla* auxiliar = head;
    while (auxiliar!=nullptr)
    {
        //std::cout<<auxiliar->getDato();
        if(auxiliar->getNombreTabla()==NombreTabla){
      //      std::cout<<"Existe";
            return auxiliar;}
        auxiliar = auxiliar->getNext();
    }
    //std::cout<<"No existe";
    return nullptr;
}

void Esquema::addAtributo(std::string NombreTabla,std::string NombreCampo,std::string Atributo){
    if(this->head==nullptr){
        Tabla* nuevo = new Tabla(NombreTabla);
        this->head=nuevo;
        this->head->add(NombreCampo,Atributo);
        return;
    }
    Tabla* auxiliar = search(NombreTabla);
    if (auxiliar != nullptr)
    {
        auxiliar->add(NombreCampo,Atributo);
        return;
    }
    else
    {
        std::cout<<"No existe esa Tabla"<<std::endl;
        return;
    }
}

string Esquema::exportString(){
    string salida = "";
    if (head==nullptr)
    {
        return salida;
    }
    Tabla* aux = this->head;
    while (true)
    {
       salida = salida+aux->exportTabla()+"\n";
        if(aux->getNext() == nullptr){
            return salida;
        }       
       aux = aux->getNext();
    }
    return salida;
}

void Esquema::viewSchemas(){
    string salida = "";
    if (head==nullptr)
    {

        return;
    }
    Tabla* aux = this->head;
    bool bandera = true;
    while (bandera)
    {
       salida = salida+aux->viewTabla()+"\n";
        if(aux->getNext() == nullptr){
            bandera = false;
        }       
       aux = aux->getNext();
    }
    std::cout<<"Vista"<<std::endl;
    std::cout<<salida<<std::endl;
    return ;
}

void Esquema::exportEsquema(std::string nombreArchivo){
    if (head==nullptr)
    {
        std::cout<<"No hay tablas en este esquema"<<std::endl;
        return;
    }
    
  ofstream file;
  string nombreA = "./"+nombreArchivo+".txt";
  file.open(nombreA);
  string data = this->exportString();
  file << data;
  file.close();
  std::cout<<"Exportado"<<std::endl;
  system("esquema.txt");
  return;
}


Esquema::~Esquema()
{
}



#endif
