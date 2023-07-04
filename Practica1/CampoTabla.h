#ifndef __CAMPO_H__
#define __CAMPO_H__
#include <string>
#include <vector>
//#include <iostream>
// Create a string variable
class CampoTabla
{
private:
    std::string NombreDato = "ATRIBUTO";
    std::string AtributoDato = "INT";
    CampoTabla* next = nullptr;
public:
    CampoTabla(std::string,std::string);
    ~CampoTabla();
    std::string  getNombreDato();
    void setNombreDato(std::string);
    std::string  getAtributo();
    void setAtributo(std::string);
    void eliminar();
    CampoTabla* getNext();
    void setNext(CampoTabla*);
};

CampoTabla::CampoTabla(std::string NombreNuevo,std::string AtributoNuevo)
{
      for (int i = 0; i < NombreNuevo.length(); i++) {
            NombreNuevo[i] = toupper(NombreNuevo[i]);
        }
    this->NombreDato=NombreNuevo;
      for (int i = 0; i < AtributoNuevo.length(); i++) {
            AtributoNuevo[i] = toupper(AtributoNuevo[i]);
        }
    this->AtributoDato=AtributoNuevo;
}
void CampoTabla::setNombreDato(std::string DatoNuevo){this->NombreDato=DatoNuevo;  return;}

void CampoTabla::setAtributo(std::string AtributoNuevo){this->AtributoDato=AtributoNuevo;  return;}

void CampoTabla::setNext(CampoTabla* NuevoCampo){this->next=NuevoCampo;  return;}

std::string CampoTabla::getNombreDato(){return this->NombreDato;}

std::string CampoTabla::getAtributo(){return this->AtributoDato;}

CampoTabla* CampoTabla::getNext(){return this->next;}

void CampoTabla::eliminar(){this->next=nullptr;return;}

CampoTabla::~CampoTabla()
{}

#endif