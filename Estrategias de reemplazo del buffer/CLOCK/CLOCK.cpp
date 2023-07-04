#include<iostream>
#include "Double_Linked_List.h"
#include<vector>
#include<fstream>
#include<string>
using namespace std;
int const fr = 4;
int j = 0,hit = 0;
Double_Linked_List<char> Frames;

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

bool todo_1(){
    Nodo<char> *tmp = Frames.get_puntero();
    for(int i=0;i<Frames.get_size();i++){
        if(tmp->get_ref() == 0){
            return false;
        }
        tmp = tmp->get_sig();
    }
    return true;
}

void CLOCK(vector<char> Req){
    while(j < Req.size()){
        if(Frames.buscar(Req[j])){ //Si se encuentra en los frames
            Nodo<char> *tmp = Frames.get_head();
            for(int i=0;i<Frames.get_size();i++){
                if(tmp->get_dato() == Req[j]){
                    tmp->set_ref(1);
                    break;
                }
                tmp = tmp->get_sig();
            }
            hit++;
        }
        //Si no se encuentra en el frame
        else{
            //Si no se llenaron los frames
            if(Frames.get_size() < fr){
                Frames.push_back(Req[j]);
            }
            //si estan llenos todos los frames
            else{
                Nodo<char> *tmp = Frames.get_puntero();
                // si todos tienen referencia 1
                if(todo_1()){
                    for(int i=0;i<Frames.get_size();i++){
                        tmp->set_ref(0);
                        tmp = tmp->get_sig();
                    }
                    tmp = tmp->get_sig();
                    tmp->set_dato(Req[j]);
                    tmp->set_ref(1);
                    Frames.set_puntero(tmp);
                }
                //caso : *1 1 0 0
                else{
                    for(int i=0;i<Frames.get_size();i++){
                        if(tmp->get_ref() == 0){
                            tmp->set_ref(1);
                            tmp->set_dato(Req[j]);
                            Frames.set_puntero(tmp);
                            break;
                        }
                        tmp = tmp->get_sig();
                    }
                }
            }
        }
        j++;
    }
}

int main(){
    vector<char> Req;
    llenar(Req);
    CLOCK(Req);
    Nodo<char> *tmp = Frames.get_head();
    for(int i=0;i<Frames.get_size();i++){
        cout << tmp->get_dato() <<" ";
        tmp = tmp->get_sig();
    }
    
    cout<<"\nHit: "<<hit<<endl;

    return 0;
}
