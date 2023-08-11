#ifndef __DISCODURO__
#define __DISCODURO__
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <map>
#include <regex>
namespace fs = std::filesystem;
class DiscoDuro
{
private:
    int numPlatos;
    int pistasPorSuperficie;
    int sectoresPorPista;
    int bytesPorSector;
    int sectoresPorBloque = 5;
    int sectoresUsados = 0;

public:
    DiscoDuro();
    DiscoDuro(int, int, int, int);
    void crearEstructuraDisco();
    void guardarTextoEnSectores(const std::string &);
    void leerSectores(const std::string *, int);
    void crearCarpeta(const std::string &);
    void crearArchivo(const std::string &);
    void guardarEnArchivo(const std::string &, const std::string &);
    bool leerSector(const std::string &, std::string &);
    void leerSectoresDinamico();
    // void configurarBloques();
    //  void leerBloque();
    void leerSector();
    void capacidadDisco();
    void setnumPlatos(int);
    void setpistasPorSuperficie(int);
    void setsectoresPorPista(int);
    void setbytesPorSector(int);
    int getpistasPorSuperficie();
    int getsectoresPorPista();
    int getbytesPorSector();
    int buscarId(const std::string &id);
    bool sectorDisponible(const std::string &sector);
    void guardarDiccionarioEnArchivo(const std::string &archivo, const std::map<int, std::string> &diccionario, std::vector<std::string> bloques);
    ~DiscoDuro();
};

DiscoDuro::DiscoDuro() {}

DiscoDuro::DiscoDuro(int platos, int pistas, int sectores, int bytes)
    : numPlatos(platos),
      pistasPorSuperficie(pistas),
      sectoresPorPista(sectores),
      bytesPorSector(bytes) {

       
      }

void DiscoDuro::capacidadDisco()
{
    std::cout << "Capacidad total: " << this->bytesPorSector * this->sectoresPorPista * 2 * this->pistasPorSuperficie * this->numPlatos << "bytes" << std::endl;
}

void DiscoDuro::setnumPlatos(int platos)
{
    this->numPlatos = platos;
    return;
}

void DiscoDuro::setpistasPorSuperficie(int pistasPorSuperfi)
{
    this->pistasPorSuperficie = pistasPorSuperfi;
    return;
}

void DiscoDuro::setsectoresPorPista(int SecPorPista)
{
    this->sectoresPorPista = SecPorPista;
    return;
}

void DiscoDuro::setbytesPorSector(int bytes)
{
    this->bytesPorSector = bytes;
    return;
}

void DiscoDuro::crearEstructuraDisco()
{

    std::string carpeta = "discoDuro";
    fs::remove_all(carpeta);
    crearCarpeta(carpeta);
    for (int plato = 1; plato <= numPlatos; plato++)
    {
        std::string carpetaPlato = carpeta + "/" + std::to_string(plato);
        crearCarpeta(carpetaPlato);

        for (int superficie = 1; superficie <= 2; superficie++)
        {
            std::string carpetaSuperficie = carpetaPlato + "/" + std::to_string(superficie);
            crearCarpeta(carpetaSuperficie);

            for (int pista = 1; pista <= pistasPorSuperficie; pista++)
            {
                std::string carpetaPista = carpetaSuperficie + "/" + std::to_string(pista);
                crearCarpeta(carpetaPista);

                for (int sector = 1; sector <= sectoresPorPista; sector++)
                {
                    std::string archivoSector = carpetaPista + "/" + std::to_string(sector) + ".txt";
                    crearArchivo(archivoSector);
                }
            }
        }
    }

    std::cout << "La estructura del disco ha sido creada exitosamente." << std::endl;
}

bool DiscoDuro::sectorDisponible(const std::string &sector) {
  std::ifstream archivo(sector);

  if (!archivo.is_open()) {
    std::cout << "No existe ese sector" << std::endl;
    // manejar error
  }

  std::string linea;
  while (getline(archivo, linea)) {
    if (!linea.empty() && linea.find("#") != std::string::npos) {
      // El archivo contiene contenido y ya está ocupado
      archivo.close();
      return false;
    }
  }

  // Terminó el archivo sin encontrar contenido, está disponible
  archivo.close();
  return true;
}


void DiscoDuro::guardarTextoEnSectores(const std::string &archivoTxt)
{
    std::ifstream archivo(archivoTxt);
    if (!archivo.is_open())
    {
        std::cout << "Error al abrir el archivo " << archivoTxt << std::endl;
        return;
    }

    const int maxSectores = numPlatos * 2 * pistasPorSuperficie * sectoresPorPista;
    const int maxTamanoSector = bytesPorSector;
    std::string sectores[maxSectores];
    int numSectores = 0;
    std::map<int, std::string> diccionarioDePunteros;
    std::string linea;
    std::string contenido;
    std::vector<std::string> ids;
    bool fisrt = true;
    while (std::getline(archivo, linea))
    {
        if (!contenido.empty())
        {
            contenido += "#";
        }
        contenido += linea;

        if (contenido.length() > maxTamanoSector)
        {
            sectores[numSectores] = contenido;
            contenido = "";
            ids.push_back(sectores[numSectores]);
            numSectores++;
        }
    }

    if (!contenido.empty())
    {
        contenido.pop_back();
        sectores[numSectores] = contenido;

        ids.push_back(sectores[numSectores]);
        numSectores++;
    }

    archivo.close();

    int numSectoresNecesarios = numSectores;

    int numSectoresDisponibles = numPlatos * 2 * pistasPorSuperficie * sectoresPorPista - this->sectoresUsados;
    std::cout << "Necesarios: " << numSectoresNecesarios << " Disponibles: " << numSectoresDisponibles << std::endl;
    if (numSectoresNecesarios > numSectoresDisponibles)
    {
        std::cout << "No hay suficientes sectores disponibles para guardar el texto." << std::endl;
        return;
    }

    int indiceSector = 0;
    int idBloque = 0;
    std::vector<int> bloques;

    for (int plato = 1; plato <= numPlatos; plato++)
    {
        for (int superficie = 1; superficie <= 2; superficie++)
        {
            for (int pista = 1; pista <= pistasPorSuperficie; pista++)
            {
                for (int sector = 1; sector <= sectoresPorPista; sector++)
                {

                    std::string archivoSector = "discoDuro/" + std::to_string(plato) + "/" + std::to_string(superficie) + "/" + std::to_string(pista) + "/" + std::to_string(sector) + ".txt";

                    if (sectorDisponible(archivoSector))
                    {

                       // std::cout<<"Disponible"<<archivoSector<<sectorDisponible(archivoSector)<<std::endl;
                        if (indiceSector < numSectoresNecesarios)
                        {

                            diccionarioDePunteros.insert({indiceSector + 1, archivoSector});
                            bloques.push_back(idBloque);



                            guardarEnArchivo(archivoSector, sectores[indiceSector]);
                            indiceSector++;
                        }
                        else
                        {

                            // Guardar el diccionario en un archivo
                            //guardarDiccionarioEnArchivo("diccionario.txt", diccionarioDePunteros, ids);
                           // return;
                        }
                    }
                    if ((sector * pista * superficie * plato) % this->sectoresPorBloque == 0)
                    {
                        idBloque++;
                    }
                }
            }
        }
    }

    guardarDiccionarioEnArchivo("diccionario.txt", diccionarioDePunteros, ids);

    std::cout << "Archivo Guardado" << std::endl;
}

void DiscoDuro::leerSectores(const std::string *sectoresALeer, int numSectores)
{
    for (int i = 0; i < numSectores; ++i)
    {
        std::string contenido;
        if (leerSector(sectoresALeer[i], contenido))
        {
            std::cout << "Contenido del sector " << i + 1 << ":" << std::endl;
            std::cout << contenido << std::endl;
        }
        else
        {
            std::cout << "No se pudo leer el sector " << i + 1 << std::endl;
        }
    }
}

void DiscoDuro::leerSectoresDinamico()
{
    int PlatoAmostrar, SuperficieAMostrar, PistaaMostrar, SectorAmostrar;
    std::cout << "Plato : ";
    std::cin >> PlatoAmostrar;
    std::cout << "Superficie: ";
    std::cin >> SuperficieAMostrar;
    std::cout << "Pista: ";
    std::cin >> PistaaMostrar;
    std::cout << "Sector: ";
    std::cin >> SectorAmostrar;
    std::string sectorALeer = "discoDuro/" + std::to_string(PlatoAmostrar) + "/" + std::to_string(SuperficieAMostrar) + "/" + std::to_string(PistaaMostrar) + "/" + std::to_string(SectorAmostrar) + ".txt";
    std::string contenido;
    if (leerSector(sectorALeer, contenido))
    {
        std::cout << "Contenido del sector P: " << PlatoAmostrar << "S: " << SuperficieAMostrar << " P: " << PistaaMostrar << " Se: " << SectorAmostrar << ":" << std::endl;
        std::cout << contenido << std::endl;
    }
    else
    {
        std::cout << "No se pudo leer el sector " << PlatoAmostrar << "S: " << SuperficieAMostrar << " P: " << PistaaMostrar << " Se: " << SectorAmostrar << std::endl;
    }
}

void DiscoDuro::crearCarpeta(const std::string &rutaCarpeta)
{
    fs::create_directories(rutaCarpeta);
    std::cout << "Creando carpeta: " << rutaCarpeta << std::endl;
    // Lógica para crear una carpeta en el sistema de archivos
}

void DiscoDuro::crearArchivo(const std::string &rutaArchivo)
{
    std::ofstream archivo(rutaArchivo);
    std::cout << "Creando archivo: " << rutaArchivo << std::endl;
    // Lógica para crear un archivo en el sistema de archivos
}

void extraerNumeros(const std::string &cadena, std::vector<int> &numeros)
{
    std::regex patron("#(\\d+)");

    std::smatch coincidencias;

    auto inicio = cadena.cbegin();
    while (std::regex_search(inicio, cadena.cend(), coincidencias, patron))
    {
        if (coincidencias[1].matched)
        {
            numeros.push_back(std::stoi(coincidencias[1].str()));
            std::cout<<coincidencias[1].str()<<std::endl;
        }
        else if (coincidencias[2].matched)
        {
            numeros.push_back(std::stoi(coincidencias[2].str()));
            std::cout<<coincidencias[2].str()<<std::endl;
        }
        inicio = coincidencias.suffix().first;
    }
}

void DiscoDuro::guardarEnArchivo(const std::string &rutaArchivo, const std::string &contenido)
{
    std::ofstream archivo(rutaArchivo);
    if (archivo.is_open())
    {
        archivo << contenido;
        archivo.close();
    }
    else
    {
        std::cout << "Error al guardar en el archivo " << std::endl;
    }
}


void DiscoDuro::guardarDiccionarioEnArchivo(const std::string &nombreArchivo, const std::map<int, std::string> &diccionario, std::vector<std::string> bloques) {

  std::ofstream archivoDiccionario;

  // Verificar si archivo ya existe
  if(fs::exists(nombreArchivo)) {
    archivoDiccionario.open(nombreArchivo, std::ios_base::app); // Append
  } else { 
    archivoDiccionario.open(nombreArchivo); // Truncate
  }

  if (archivoDiccionario.is_open()) {

    for (auto const& entrada : diccionario) {

      int indice = entrada.first;
      std::string sector = entrada.second;
      
      std::vector<int> numeros;
      std::string cadena = "#" + bloques[indice-1];

      extraerNumeros(cadena, numeros);

      for (int num : numeros) {
      
        archivoDiccionario << num << " " << indice << " " << sector << "\n";
      
      }

    }
    
    archivoDiccionario.close();

  } else {
        std::cout << "Error al abrir el archivo de diccionario." << std::endl;
  }

}




bool DiscoDuro::leerSector(const std::string &sector, std::string &contenido)
{
    std::ifstream archivo(sector);
    if (archivo.is_open())
    {
        std::stringstream buffer;
        buffer << archivo.rdbuf();
        contenido = buffer.str();
        archivo.close();
        return true;
    }
    return false;
}

void DiscoDuro::leerSector()
{
    std::cout << "Ingrese numero del sector: ";
    int bloqueSector;
    std::cin >> bloqueSector;

    // 1 -> (1*3)-3+1 = 3 -2
    // 2 -> (2*3)-3+1 = 6-3+1 = 4
    int contadorSector = 0;
    for (int plato = 1; plato <= numPlatos; plato++)
    {
        for (int superficie = 1; superficie <= 2; superficie++)
        {
            for (int pista = 1; pista <= pistasPorSuperficie; pista++)
            {
                for (int sector = 1; sector <= sectoresPorPista; sector++)
                {
                    contadorSector++;
                    if (contadorSector == bloqueSector)
                    {
                        std::string sectorALeer = "discoDuro/" + std::to_string(plato) + "/" + std::to_string(superficie) + "/" + std::to_string(pista) + "/" + std::to_string(sector) + ".txt";
                        std::string contenido;
                        std::cout << "Mostrando Sector: " << bloqueSector << std::endl;
                        if (leerSector(sectorALeer, contenido))
                        {
                            std::cout << contenido << std::endl;
                        }
                        else
                        {
                            std::cout << "No se pudo leer el sector " << std::endl;
                        }
                        return;
                    }
                }
            }
        }
    }
    return;
}

int DiscoDuro::buscarId(const std::string &id)
{
    std::string carpeta = "discoDuro";
    int posicion = 1;

    for (int plato = 1; plato <= numPlatos; plato++)
    {
        for (int superficie = 1; superficie <= 2; superficie++)
        {
            for (int pista = 1; pista <= pistasPorSuperficie; pista++)
            {
                for (int sector = 1; sector <= sectoresPorPista; sector++)
                {
                    std::string archivoSector = carpeta + "/" + std::to_string(plato) + "/" + std::to_string(superficie) + "/" + std::to_string(pista) + "/" + std::to_string(sector) + ".txt";
                    std::string contenido;

                    if (leerSector(archivoSector, contenido))
                    {
                        // Buscar el ID en el contenido del sector
                        if (contenido.find(id) != std::string::npos)
                        {

                            std::cout << "Encontrado en: " << plato << "_S: " << superficie << " Pista: ";
                            return posicion;
                        }
                    }
                    else
                    {
                        std::cout << "No se pudo leer el sector: " << archivoSector << std::endl;
                    }

                    posicion++;
                }
            }
        }
    }

    return -1; // No se encontró el ID en ningún sector
}

DiscoDuro::~DiscoDuro() {}

#endif