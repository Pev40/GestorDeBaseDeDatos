#ifndef _LINKED_LIST_
#define _LINKED_LIST_
#include "Nodo.h"
#include "iostream"
using namespace std;
template<typename T>
class Linked_List{
    private:
        Nodo<T> *head;
        Nodo<T> *actualizado;
        int miss; //fallos
        int hit; //aciertos
        int size;
    public:
        Linked_List();
        void push_back(T);
        void pop_back();
        int get_size();
        int get_miss();
        int get_hit();
        void set_miss();
        void set_hit();
        void set_actualizado(Nodo<T>*);
        Nodo<T>* get_actualizado();
        Nodo<T>* get_head();
        ~Linked_List();
};

template<typename T>
Linked_List<T>::Linked_List(){
    this->head = nullptr;
    this->actualizado = nullptr;
    this->miss = 0;
    this->hit = 0;
    this->size = 0;
}

template<typename T>
void Linked_List<T>::push_back(T dato){
    Nodo<T> *nuevo = new Nodo<T>(dato);
    if(!this->head){
        this->head = nuevo;
    }
    else{
        Nodo<T> *aux = this->head;
        for(int i=1;i<size;++i){
            aux = aux->get_sig();
        }
        aux->set_sig(nuevo);
    }
    this->actualizado = nuevo;
    miss++;
    size++;
}

template<typename T>
void Linked_List<T>::pop_back(){
    if(!this->head){
        return;
    }else if(this->size == 1){
        delete head;
        this->head = nullptr;
    }
    else{
        Nodo<T> *aux = this->head;
        for(int i=1;i<size-1;++i){
            aux = aux->get_sig();
        }
        Nodo<T> *aux2 = aux;
        aux2= aux2->get_sig();
        aux->set_sig(nullptr);
        delete aux2;
    }
    size--;
    return;
}

template<typename T>
int Linked_List<T>::get_size(){
    return this->size;
}

template<typename T>
int Linked_List<T>::get_hit(){
    return this->hit;
}

template<typename T>
int Linked_List<T>::get_miss(){
    return this->miss;
}

template<typename T>
void Linked_List<T>::set_miss(){
    this->miss += 1;
}

template<typename T>
void Linked_List<T>::set_hit(){
    this->hit += 1;
}

template<typename T>
void Linked_List<T>::set_actualizado(Nodo<T> * tmp){
    this->actualizado = tmp;
}

template<typename T>
Nodo<T>* Linked_List<T>::get_head(){
    return this->head;
}

template<typename T>
Nodo<T>* Linked_List<T>::get_actualizado(){
    return this->actualizado;
}

template<typename T>
Linked_List<T>::~Linked_List(){
    while(this->size){
        this->pop_back();
    }
    delete head;
}

#endif
