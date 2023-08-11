#ifndef __PAGINA_H__
#define __PAGINA_H__

#include <fstream>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

class Pagina {
public:
  int pagina_id;
  std::string content = "";

  bool dirty_bit;
  int pin_count;
  bool ref_bit;

  Pagina(int id) : pagina_id(id) {
    dirty_bit = false;
    pin_count = 0;
    ref_bit = false;
  }

  void load(std::string filename) {
    // Verificar si el archivo existe
    if (!fs::exists(filename)) {
      std::cout << "El archivo " << filename << " no existe." << std::endl;
      return;
    }

    // Abrir archivo 
    std::ifstream file(filename); 
    if (!file.is_open()) {
      std::cout << "No se pudo abrir el archivo " << filename << std::endl;
      return;
    }

    // Leer contenido
    std::string txt((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::cout<<txt<<std::endl;
    content = txt;
  }

  void verContenido(){
    std::cout<<"Contenido : "<<this->content<<std::endl;
  }
};

#endif
