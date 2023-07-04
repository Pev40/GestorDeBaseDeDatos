#include<iostream>
#include "Linked_Listt.h"
#include<string>
#include<fstream>
#include<vector>
using namespace std;
Linked_List<char> Frames;
int j = 0;
int const fr = 3;

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
bool verificar(char letra){ 
    Nodo<char> *tmp = Frames.get_head();
    for(int i=0;i<Frames.get_size();i++){
        if(tmp->get_dato() == letra){
            Frames.set_actualizado(tmp);
            return true;
        }
        tmp = tmp->get_sig();
    }
    return false;
}

void MRU(vector<char> Req){
    while(j < Req.size()){
        //si el simbolo ya se encuentra del frame o no
        if(verificar(Req[j])){ // si se encuentra en el frame
            Frames.set_hit();
        }
        //Si no se encuentra entre los frames
        else{
            //Si no se llenaron todos los frames
            if(Frames.get_size() < fr){  //k < 4
                Frames.push_back(Req[j]);
            }
            //Si estan llenos todos los frames
            else{
                Frames.get_actualizado()->set_dato(Req[j]);
                Frames.set_miss();
            }
        }
        j++;
    }
}

int main(){
    vector<char> Req;
    llenar(Req);
    MRU(Req);
    Nodo<char> *tmp = Frames.get_head();
    for(int i=0;i<Frames.get_size();i++){
        cout << tmp->get_dato() <<" ";
        tmp = tmp->get_sig();
    }
    cout<<"\nHit: "<<Frames.get_hit() << " / "<< Req.size() <<endl;
    cout<<"Miss: "<<Frames.get_miss() << " / "<< Req.size() <<endl;
    
    return 0;
}
