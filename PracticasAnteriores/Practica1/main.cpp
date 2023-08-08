#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "Megatron.h"
#include "Esquema.h"
using namespace std;

int main(){

/*
    Esquema schema = Esquema();
    string nombresTablas[] = {"students","depts"};
    string atributos1[] = {"name","str" ,"id","int" ,"dept","str"};
    string atributos2[] = {"name","str" ,"office","int"};
    schema.addTable(nombresTablas[0]);
    //cout<<""<<atributos[0]<<atributos1[1]<<endl;
    for (int i = 0; i < (sizeof atributos1/sizeof atributos1[0]); i=i+2)
    {
        schema.addAtributo(nombresTablas[0],atributos1[i],atributos1[i+1]);
    }
    schema.addTable(nombresTablas[1]);
        for (int i = 0; i < (sizeof atributos2/sizeof atributos2[0]); i=i+2)
    {
        schema.addAtributo(nombresTablas[1],atributos2[i],atributos2[i+1]);
    }
    schema.viewSchemas();
    */
    //schema.exportEsquema("esquema");
    //Esquema schema2 = Esquema();
    //importarEsquema("esquem.txt",schema2);
    //schema2.exportEsquema("esquema");
    Megatron dbms = Megatron();
    dbms.importarEsquema("esquema.txt");
    //dbms.start().viewSchemas();
    //cout<<dbms.start().search("students");
    std::vector<std::string> data1 = {"Piero","200","CS"};
    dbms.insertRegistro("students",data1);

    std::vector<std::string> data2 = {"CS","Pabellon Alan Turing"};
    dbms.insertRegistro("depts",data2);
    
   /* 
    string select_in = "SELECT";
    string input; 
    cout << "Ingrese una sentencia SQL: ";
    getline(cin, input);
    string caracter_de_inicio = "&";
    string caracter_de_fin = "#";
    if (caracter_de_inicio.compare(&input[0]) && caracter_de_inicio.compare(&input[input.length()-1]))
    {
       std::cout<<"Ingresa";
    }
    */



    return 0;
}
