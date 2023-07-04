#ifndef __PAGINA_H__
#define __PAGINA_H__

class Pagina
{
private:
    int sectoresPorBloque = 1;
    int cantidadBloques = 0;
public:
    Pagina();
    ~Pagina();
    void leerBloque();
};

Pagina::Pagina(/* args */)
{

}

Pagina::~Pagina()
{
}

/*void Pagina::leerBloque()
{
    std::cout << "Ingrese numero del bloque: ";
    int bloqueLector;
    std::cin >> bloqueLector;
    if (bloqueLector > cantidadBloques)
    {
        std::cout << "Error, no es un bloque valido" << std::endl;
        return;
    }
    // 1 -> (1*3)-3+1 = 3 -2 
    // 2 -> (2*3)-3+1 = 6-3+1 = 4
    int numeroSector = (bloqueLector * sectoresPorBloque)-sectoresPorBloque+1;
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
                    if (contadorSector == numeroSector)
                    {
                        for (int lectorDeBloque = 0; lectorDeBloque < sectoresPorBloque; lectorDeBloque++)
                        {
                            std::string sectorALeer = "discoDuro/" + std::to_string(plato) + "/" + std::to_string(superficie) + "/" + std::to_string(pista) + "/" + std::to_string(sector) + ".txt";   
                            std::string contenido;
                            std::cout<<"Mostrando Sector: "<<"Plato: "<<plato<<" Superficie: "<<superficie<<"Pista: "<<pista<<"Sector: "<<sector<<std::endl;
                            if (leerSector(sectorALeer, contenido))
                            {
                                 std::cout << contenido << std::endl;
                            }
                            else
                            {
                                std::cout << "No se pudo leer el sector " << std::endl;
                            }

                        }
                        return;
                    }
                }
            }
        }
    }
return;
}
