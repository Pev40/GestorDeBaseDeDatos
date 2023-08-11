#include "BufferPool.h"
#include "BufferPool.cpp"

#include <iostream>
int main() {

  BufferPool pool(3); // Tamaño 3
  std::cout<<"Holas"<<std::endl;
  // Cargar páginas
  pool.cargarPagina(1, "discoDuro/1/1/1/1.txt",0); 
  pool.cargarPagina(2, "discoDuro/1/1/1/2.txt",1); 

  // Leer páginas  
  std::string contenido1 = pool.leerPagina(1);
  std::cout<<"discoDuro/1/1/1/1.txt" << std::endl;
  std::cout<<pool.pool[0].pagina->content << std::endl;
  std::cout << contenido1 << std::endl;

  std::string contenido2 = pool.leerPagina(2);
  std::cout << contenido2 << std::endl;

  // Escribir páginas
  std::string nuevoContenido = "Nuevo contenido página 1";
  pool.escribirPagina(1, nuevoContenido);

  // Leer de nuevo
  contenido1 = pool.leerPagina(1);
  std::cout << contenido1 << std::endl;

  // Liberar páginas
  pool.liberarPagina(1);
  pool.liberarPagina(2);

  return 0;
}