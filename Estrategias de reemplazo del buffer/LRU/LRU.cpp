#include<iostream>
#include "Linked_List.h"
#include<string>
#include<fstream>
#include<vector>
using namespace std;
Linked_List<char> Frames;
int j = 0; //para avanzar por la entrada de requisitos
int const fr = 3;
char fila[fr];

void llenar(vector<char> &Req){
    ifstream file("../Req.txt");
    string texto;
    getline(file,texto);
    for(int i=0;i<texto.size();i++){
        if(texto[i]!=' ' && texto[i]!=','){
            Req.push_back(texto[i]);
        }
    }
}

//verifica si esta en la fila y devuelve su posicion
int verificar(char letra){ 
    for(int i=0;i<Frames.get_size();i++){
        if(fila[i] == letra){
            return i;
        }
    }
    return -1;
}

void LRU(vector<char> Req){
    while(j < Req.size()){
        int num = verificar(Req[j]); // si simbolo ya se encuentra del frame o no
        if(num != -1){ // si se encuentra en el frame
            for(int i =num ; i <Frames.get_size()-1;i++){
                swap(fila[i],fila[i+1]); //le coloca al final de la fila
            }
            Frames.set_hit();
        }
        //Si no se encuentra entre los frames
        else{
            //Si no se llenaron todos los frames
            if(Frames.get_size() < fr){  //k < 4
                fila[Frames.get_size()] = Req[j];
                Frames.push_back(Req[j]);
            }
            //Si estan llenos todos los frames
            else{
                for(int i = 0 ; i <Frames.get_size()-1;i++){
                    swap(fila[i],fila[i+1]); //le coloca al final de la fila
                }
                Frames.cambiar(fila[fr-1],Req[j]);
                fila[fr-1] = Req[j];
                Frames.set_miss();
            }
        }
        j++;
    }
}

int main(){
    vector<char> Req;
    llenar(Req);
    LRU(Req);
    Nodo<char> *tmp = Frames.get_head();
    for(int i=0;i<Frames.get_size();i++){
        cout << tmp->get_dato() <<" ";
        tmp = tmp->get_sig();
    }

    cout<<"\nHit: "<<Frames.get_hit() << " / "<< Req.size() <<endl; // Acierto
    cout<<"Miss: "<<Frames.get_miss() << " / "<< Req.size() <<endl; // Fallo
    
    return 0;
}
