#include "Disco.h"

int main() {
    Disco disco(2,16,8, 32); // Crear un disco de 8 sectores, 16 pistas, 2 superficies y 32 sectores por pista
    char datos[512] = "Hola, mundo!"; // Datos a escribir en el disco

    // Escribir los datos en el sector 3 de la pista 5 de la superficie 1
    disco.escribir(3, 5, 1, datos);

    // Leer los datos del sector 3 de la pista 5 de la superficie 1
    char datos_leidos[512];
    disco.leer(3, 5, 1, datos_leidos);

    // Imprimir los datos del sector 3 de la pista 5 de la superficie 1
    disco.imprimir(3, 5, 1);

    return 0;
}
