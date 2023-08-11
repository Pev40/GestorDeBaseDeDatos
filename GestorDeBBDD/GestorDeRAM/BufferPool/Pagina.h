#ifndef __PAGINA_H__
#define __PAGINA_H__

#include <fstream>

class Page {
public:
  int page_id;
  std::string content;

  bool dirty_bit;
  int pin_count;
  bool ref_bit;

  Page(int id) : page_id(id) {
    dirty_bit = false;
    pin_count = 0;
    ref_bit = false;
  }

  void load(std::string filename) {
    // Abrir archivo 
    std::ifstream file(filename); 
    // Leer contenido
    std::string txt((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    content = txt;
  }
};

#endif
