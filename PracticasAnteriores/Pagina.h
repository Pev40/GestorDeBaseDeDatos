#ifndef __PAGINA_H__
#define __PAGINA_H__

#include <iostream>
#include <vector>
#include <memory>
class Pagina {
public:
    int idBloque;
    std::string arraynombrepagina;
    std::string Contenido;

    Pagina(int id, const std::string& nombre, const std::string& contenido);
};
#endif

Pagina::Pagina(int id, const std::string& nombre, const std::string& contenido) : idBloque(id), arraynombrepagina(nombre), Contenido(contenido) {}