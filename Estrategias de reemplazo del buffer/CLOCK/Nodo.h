#ifndef _NODO_
#define _NODO_
template<typename T>
class Nodo{
    private:
        T dato;
        int ref = 0;
        Nodo<T> *anterior;
        Nodo<T> *siguiente;
    public:
        Nodo();
        Nodo(T dato);
        Nodo<T>* get_sig();
        Nodo<T>* get_ant();
        void set_sig(Nodo<T>*);
        void set_ant(Nodo<T>*);
        T get_dato();
        int get_ref();
        void set_dato(T);
        void set_ref(int);
        ~Nodo();
};

template <typename T>
Nodo<T>::Nodo(){
    this->dato = NULL;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

template <typename T>
Nodo<T>::Nodo(T dato){
    this->dato = dato;
    this->ref = 1;
    this->anterior = nullptr;
    this->siguiente = nullptr;
}

template <typename T>
Nodo<T>* Nodo<T>::get_sig(){
    return this->siguiente;
}

template <typename T>
Nodo<T>* Nodo<T>::get_ant(){
    return this->anterior;
}

template <typename T>
void Nodo<T>::set_sig(Nodo<T>* nuevo){
    this->siguiente = nuevo;
    return;
}

template <typename T>
void Nodo<T>::set_ant(Nodo<T>* nuevo){
    this->anterior = nuevo;
    return;
}

template<typename T>
T Nodo<T>::get_dato(){
    return this->dato;   
}

template<typename T>
int Nodo<T>::get_ref(){
    return this->ref;
}

template<typename T>
void Nodo<T>::set_dato(T dato){
    this->dato = dato;
    return;
}

template<typename T>
void Nodo<T>::set_ref(int ref){
    this->ref = ref;
    return;
}

template <typename T>
Nodo<T>::~Nodo(){
}

#endif
