#ifndef __SECTOR_H__
#define __SECTOR_H__
#include <string>
class Sector {
private:
    int numero;
    int tamano;
    char* datos;

public:
    Sector();
    Sector(int num, int size);
    ~Sector();

    int getNumero();
    int getTamano();
    char* getDatos();
    void setDatos(char* data);
};

Sector::Sector(int num, int size) {
    numero = num;
    tamano = size;
    datos = new char[tamano];
}

Sector::~Sector() {
    delete[] datos;
}

int Sector::getNumero() {
    return numero;
}

int Sector::getTamano() {
    return tamano;
}

char* Sector::getDatos() {
    return datos;
}

void Sector::setDatos(char* data) {
    memcpy(datos, data, tamano);
}


#endif