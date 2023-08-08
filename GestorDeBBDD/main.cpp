#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <experimental/filesystem>
#include <stdio.h>
#include <map>
#include <iomanip> // Para std::setw()
#include "DiscoDuro.h"
namespace fs = std::filesystem;

void convertir_csv(const std::string &archivo_csv, const std::string &archivo_salida)
{
    std::ifstream archivo_entrada(archivo_csv);
    std::ofstream archivo_salida_stream(archivo_salida); // Cambia el nombre de la variable aquí

    if (archivo_entrada && archivo_salida_stream)
    {
        std::string linea;

        while (std::getline(archivo_entrada, linea))
        {
            std::stringstream ss(linea);
            std::string campo;
            bool primer_campo = true;
            while (std::getline(ss, campo, ','))
            {

                if (!primer_campo)
                {
                    archivo_salida_stream << "";
                }
                else
                {
                    primer_campo = false;
                }

                archivo_salida_stream << campo ;
            }
            archivo_salida_stream << std::endl;
        }

        std::cout << "El archivo ha sido convertido exitosamente." << std::endl;
    }
    else
    {
        std::cout << "Error al abrir el archivo de entrada o salida." << std::endl;
    }
}

const int MAX_ENCABEZADOS = 12; // Máximo número de encabezados permitidos

bool convertir_csv2(const std::string &archivo_csv, const std::string &archivo_salida)
{
    std::ifstream archivo_entrada(archivo_csv);
    std::ofstream archivo_salida_stream(archivo_salida, std::ios::binary);
    std::ofstream esquema_stream("esquema.txt");
    
    if (archivo_entrada && archivo_salida_stream && esquema_stream)
    {
        std::string linea;
        std::getline(archivo_entrada, linea); // Leer la primera línea como encabezados

        std::stringstream encabezados_ss(linea);
        std::string encabezado;
        std::string tipo_dato;
        int tamanos[MAX_ENCABEZADOS] = {0}; // Arreglo para almacenar los tamaños de los encabezados
        int num_encabezados = 0;

        while (std::getline(encabezados_ss, encabezado, ';'))
        {
            if (num_encabezados >= MAX_ENCABEZADOS)
            {
                std::cout << "Se ha excedido el número máximo de encabezados permitidos." << std::endl;
                return false;
            }

            std::cout << "Ingrese el tipo de dato ('int', 'float', o 'str') para el encabezado '" << encabezado << "': ";
            std::cin >> tipo_dato;

            if (tipo_dato == "str")
            {
                std::cout << "Ingrese el tamaño en bytes para el encabezado '" << encabezado << "': ";
                std::cin >> tamanos[num_encabezados];
            }
            else
            {
                tamanos[num_encabezados] = (tipo_dato == "int" || tipo_dato == "float") ? sizeof(float) : 0;
            }

            esquema_stream << encabezado << "#" << tipo_dato << "#" << tamanos[num_encabezados] << std::endl;
            num_encabezados++;
        }

        archivo_salida_stream << std::endl;
        
        while (std::getline(archivo_entrada, linea))
        {
            std::stringstream ss(linea);
            std::string campo;
            bool primer_campo = true;
            int indice = 0;

            while (std::getline(ss, campo, ';'))
            {
                if (!primer_campo)
                {
                    archivo_salida_stream << "";
                }
                else
                {
                    primer_campo = false;
                }

                std::string campo_rellenado;
                if (indice == 3) // Indice del campo 'name'
                {
                    campo_rellenado = "\"" + campo + "\"";
                }
                else
                {
                    campo_rellenado = campo;
                }

                if (campo_rellenado.length() < tamanos[indice])
                {
                    campo_rellenado.resize(tamanos[indice], ' '); // Rellenar con espacios en blanco si es necesario
                }

                archivo_salida_stream.write(campo_rellenado.c_str(), tamanos[indice]);
                indice++;
            }
            archivo_salida_stream << std::endl;
        }

        std::cout << "El archivo ha sido convertido exitosamente." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error al abrir el archivo de entrada, salida o esquema." << std::endl;
        return false;
    }
}

void obtener_tamano_registro(const std::string &archivo)
{
    std::ifstream archivo_txt(archivo);
    if (!archivo_txt)
    {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    std::string renglon;
    // Leer el segundo renglón
    for (int i = 0; i < 2; ++i)
    {
        if (!std::getline(archivo_txt, renglon))
        {
            std::cerr << "Error al leer el archivo" << std::endl;
            return;
        }
    }

    archivo_txt.close();

    // Calcular el tamaño del registro
    std::stringstream ss(renglon);
    std::string campo;
    int tamano_registro = 0;
    while (std::getline(ss, campo, '$'))
    {
        tamano_registro++;
    }

    std::cout << "El tamaño del registro del segundo renglón es: " << tamano_registro << std::endl;

    return;
}

void obtenerTamañoArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo, std::ios::binary | std::ios::ate);
    if (!archivo) {
        // Error al abrir el archivo
        return;
    }

    // Obtiene la posición actual del archivo, que es el tamaño en bytes
    std::streampos tamaño = archivo.tellg();
    archivo.close();
    std::cout<<"El tamaño es: "<<static_cast<long>(tamaño)<<" bytes"<<std::endl;
    return ;
}

int main()
{

/*
            3 platos
            2 superficies
            4 pistas
            1024 bytes 
*/ 

    bool discoCreado = false;
    DiscoDuro disco;
    int opcion;
    do
    {
        std::cout << "----- MENÚ -----" << std::endl;
        std::cout << "1. Crear disco" << std::endl;
        std::cout << "2. Convertir datos de CSV" << std::endl;
        std::cout << "3. Tamaño del archivo" << std::endl;
        std::cout << "4. Guardar texto en sectores" << std::endl;
        std::cout << "5. Leer sectores" << std::endl;
        std::cout << "6. Leer Bloques" << std::endl;
        std::cout << "7. Leer Sector Por Numeracion" << std::endl;
        std::cout << "8. Tamaño del Disco" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Elije una opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            if (!discoCreado)
            {
                int numPlatos;
                int pistasPorSuperficie;
                int sectoresPorPista;
                int bytesPorSector;

                std::cout << "Ingrese la cantidad de platos: ";
                std::cin >> numPlatos;

                std::cout << "Ingrese la cantidad de pistas por superficie: ";
                std::cin >> pistasPorSuperficie;

                std::cout << "Ingrese la cantidad de sectores por pista: ";
                std::cin >> sectoresPorPista;

                std::cout << "Ingrese la cantidad de bytes por sector: ";
                std::cin >> bytesPorSector;

                disco.setnumPlatos(numPlatos);
                disco.setpistasPorSuperficie(pistasPorSuperficie);
                disco.setsectoresPorPista(sectoresPorPista);
                disco.setbytesPorSector(bytesPorSector);
                disco.crearEstructuraDisco();
                discoCreado = true;
                std::cout << "Disco creado exitosamente." << std::endl;
            }
            else
            {
                std::cout << "El disco ya ha sido creado anteriormente." << std::endl;
            }
            break;
        case 2:
        {
            if (discoCreado)
            {
                std::string archivoCSV, archivoSalida;
                std::cout << "Ingrese el nombre del archivo CSV: ";
                std::cin >> archivoCSV;
                std::cout << "Ingrese el nombre del archivo de salida: ";
                std::cin >> archivoSalida;
                convertir_csv2(archivoCSV, archivoSalida);
            }
            else
            {
                std::cout << "Debe crear el disco antes de convertir los datos de CSV." << std::endl;
            }
            break;
        }
        case 3:
        {
            if (discoCreado)
            {
                std::string archivoleer;
                std::cout << "Ingrese el nombre a leer: ";
                std::cin >> archivoleer;
                obtenerTamañoArchivo(archivoleer);
            }
            else
            {
                std::cout << "Debe crear el disco antes de convertir los datos de CSV." << std::endl;
            }
            break;
        }
        case 4:
        {
            if (discoCreado)
            {
                std::string archivoTxt;
                std::cout << "Ingrese el nombre del archivo de texto: ";
                std::cin >> archivoTxt;
                disco.guardarTextoEnSectores(archivoTxt);
            }
            else
            {
                std::cout << "Debe crear el disco antes de guardar el archivo." << std::endl;
            }
            break;
        }
        case 5:
            if (discoCreado)
            {
                disco.leerSectoresDinamico();
            }
            else
            {
                std::cout << "Debe crear el disco antes de leer los sectores." << std::endl;
            }
            break;

        case 6:
            if (discoCreado)
            {
                disco.configurarBloques();
                //disco.leerBloque();
            }
            else
            {
                std::cout << "Debe crear el disco antes de leer los sectores." << std::endl;
            }
            break;
        case 7:
            if (discoCreado)
            {
                disco.leerSector();
            }
            else
            {
                std::cout << "Debe crear el disco antes de leer los sectores." << std::endl;
            }
            break;
        case 8:
            if (discoCreado)
            {
                disco.capacidadDisco();
            }
            else
            {
                std::cout << "Debe crear el disco antes de leer los sectores." << std::endl;
            }
            break;
        case 9:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción inválida. Intente nuevamente." << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (opcion != 9);

    /*std::string sectoresALeer[] = {
        "discoDuro/1/1/1/1.txt",
        "discoDuro/1/1/1/2.txt",
        "discoDuro/1/1/1/3.txt"};
    */
    // disco.leerSectores(sectoresALeer, sizeof(sectoresALeer) / sizeof(sectoresALeer[0]));
    // disco.leerSectoresDinamico();

    // std::string textoLeido = disco.leerTextoDeSectores();
    // std::cout << "Texto leído de los sectores: " << textoLeido << std::endl;

    return 0;
}
