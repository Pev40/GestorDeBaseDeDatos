#ifndef INFOFRAMEVECTOR_H
#define INFOFRAMEVECTOR_H

#include <vector>
#include <list>
#include <iostream>

using namespace std;

class InfoFrameVector
{
public:
        int page_id;
        bool dirty_bit;
        int pin_count;
        bool ref_bit;
public:
    InfoFrameVector();
    ~InfoFrameVector();

    //otras funciones:
    
    bool pinning(); //Indica si la página esta en uso
    void unpinning();   //Libera y si hay Dirty Bit (Guarda cambios))
    void print_info_obj_vector();

    //Setters
    void set_page_id(int _input);
    void set_dirty_bit(bool _input);
    void set_pin_count(int _input);
    void set_ref_bit(bool _input);

    //Getters
    int get_page_id();
    bool get_dirty_bit();
    int get_pin_count();
    bool get_ref_bit();
    friend class TablaMetadata;

};

#endif