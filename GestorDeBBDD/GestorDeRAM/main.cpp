#include "BuferManager.h"
#include "BPlusTree/BTree.h"

int main() {

    BTree arbol;
    std::string archivoEstructura = "../diccionario.txt"; // Cambiar por el nombre de tu archivo

    arbol.cargarArchivoEnArbol(archivoEstructura); // Llama al nuevo método del árbol
    std::cout << "Valor Buscado: " << arbol.search_values_get_idPage(1) << std::endl;
    std::cout << "Valor Buscado: " << arbol.search_values_get_directPage(2) << std::endl;
                    


  BufferManager manager(3); // Pool de 3 frames

  manager.cargarPagina(999);
  manager.cargarPagina(2);
  
  std::cout << manager.leerPagina(1) << std::endl;

  manager.escribirPagina(2, "Nuevo contenido");
  std::cout << manager.leerPagina(2) << std::endl;

  manager.liberarPagina(1);
  manager.liberarPagina(2);

  // Intentar cargar una cuarta página
  try {
    manager.cargarPagina(4); 
  } catch(std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl; 
  }

  return 0;
}