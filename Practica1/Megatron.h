#ifndef __MEGATRON_H__
#define __MEGATRON_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include "Esquema.h"
#include "Tabla.h"
class Megatron
{
private:
    Esquema schema = Esquema();
public:
    Megatron(/* args */);
    ~Megatron();
    void importarEsquema(std::string);
    void insertRegistro(std::string, vector<std::string>);
    Esquema start();
};

Megatron::Megatron(/* args */)
{
}

Megatron::~Megatron()
{
}

void Megatron::importarEsquema(std::string nombreArchivo){
    std::map<std::string, std::map<std::string, std::string>> map1;

    // Abrir el archivo de texto para leer
    std::ifstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo" << std::endl;
        return ;
    }

    // Leer cada línea del archivo
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Crear un flujo de cadena a partir de la línea leída
        std::stringstream ss(linea);

        // Leer la clave exterior del mapa
        std::string clave_exterior;
        if (!std::getline(ss, clave_exterior, '#')) {
            std::cerr << "Error al leer la clave exterior" << std::endl;
            return;
        }
        clave_exterior.erase(remove_if(clave_exterior.begin(), clave_exterior.end(), ::isspace), clave_exterior.end());
        // Crear un mapa interior para la clave exterior actual
        std::map<std::string, std::string> mapa_interior;

        // Leer cada par clave-valor del mapa interior
        std::string clave, valor;
        while (std::getline(ss, clave, '#') && std::getline(ss, valor, '#')) {
            // Eliminar espacios en blanco de cada palabra
            clave.erase(remove_if(clave.begin(), clave.end(), ::isspace), clave.end());
            valor.erase(remove_if(valor.begin(), valor.end(), ::isspace), valor.end());

            // Agregar el par clave-valor al mapa interior
            mapa_interior[clave] = valor;
        }

        // Agregar el mapa interior al mapa exterior
        map1[clave_exterior] = mapa_interior;
    }

    // Mostrar el mapa de mapas leído
    //Esquema schema = Esquema();
    for (auto const& exterior : map1) {
        this->schema.addTable(exterior.first);
        for (auto const& interior : exterior.second) {
            this->schema.addAtributo(exterior.first,interior.first,interior.second);
        }
    }
    std::cout<<"Importado"<<std::endl;
    // Cerrar el archivo
    archivo.close();
    
    //ReferenciaEsquema = schema;
    return ;
}

void Megatron::insertRegistro(std::string NombreTabla,  vector<std::string> ListaDeIngreso){
    //std::cout<<"---INICIANDO---"<<std::endl;
    vector<std::string> ListaDeAtributos;
    Tabla* aux = schema.search(NombreTabla);
    //std::cout<<aux<<std::endl;
    if (aux==nullptr)
    {
        std::cout<<"No existe esa tabla"<<std::endl;
    }
    //bool bandera = true;
    CampoTabla* auxCampo = aux->getCampoTabla();
    for (int i = 0; i < aux->getCantidadAtributos(); i++)
    {
       ListaDeAtributos.push_back(auxCampo->getNombreDato());
      // std::cout<<auxCampo->getNombreDato()<<std::endl;
       auxCampo = auxCampo->getNext();
      // std::cout<<"---bucle---"<<std::endl;       
    }       

    if (ListaDeAtributos.size() < ListaDeIngreso.size())
    {
        std::cout<<"Error de Ingreso de Datos"<<std::endl;
        return;
    }
    std::string nombreArchivo = "./"+aux->getNombreTabla()+".txt"; 
   // std::cout<<nombreArchivo<<std::endl;
    std::ifstream archivo(nombreArchivo);
    std::string contenido;

    std::getline(archivo, contenido, '\0');
    contenido = contenido + "\n";
    for (const auto& elem : ListaDeIngreso) {
        contenido = contenido + elem + " # ";
    }
    contenido.pop_back();
    contenido.pop_back();
    contenido.pop_back();
    
    std::ofstream file;
    //string nombreA = "./"+nombreArchivo+".txt";
    file.open(nombreArchivo);
    std::string data = contenido;
    file << data;
    file.close();
    //system(nombreArchivo);
    
    

    return;
}


Esquema Megatron::start(){return this->schema;}

#endif