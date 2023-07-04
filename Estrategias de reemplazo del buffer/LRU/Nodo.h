#ifndef _NODO_
#define _NODO_
template<typename T>
class Nodo{
    private:
        T dato;
        Nodo<T> *siguiente;
    public:
        Nodo();
        Nodo(T dato);
        Nodo<T>* get_sig();
        void set_sig(Nodo<T>*);
        T get_dato();
        void set_dato(T);
        ~Nodo();
};

template <typename T>
Nodo<T>::Nodo(){
    this->dato = NULL;
    this->siguiente = nullptr;
}

template <typename T>
Nodo<T>::Nodo(T dato){
    this->dato = dato;
    this->siguiente = nullptr;
}

template <typename T>
Nodo<T>* Nodo<T>::get_sig(){
    return this->siguiente;
}

template <typename T>
void Nodo<T>::set_sig(Nodo<T>* nuevo){
    this->siguiente = nuevo;
    return;
}

template<typename T>
T Nodo<T>::get_dato(){
    return this->dato;   
}

template<typename T>
void Nodo<T>::set_dato(T dato){
    this->dato = dato;
    return;
}

template <typename T>
Nodo<T>::~Nodo(){
}

#endif
