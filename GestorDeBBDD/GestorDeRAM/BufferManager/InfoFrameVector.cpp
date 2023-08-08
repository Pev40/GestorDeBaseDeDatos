#include "InfoFrameVector.h"

InfoFrameVector::InfoFrameVector(){
    this->page_id=0;
    this->dirty_bit=false;
    this->pin_count=0;
    this->ref_bit=false;
}

InfoFrameVector::~InfoFrameVector(){}

bool InfoFrameVector::pinning(){
    if (this->pin_count>0)
    {
        return true;//esta en uso
    }
    else
    {
        return false;
    }

}

void InfoFrameVector::unpinning(){
    if (this->dirty_bit==true)
    {
        cout<<"Dirty_bit = 1"<<endl;
    }
    else
    {
        cout<<"Dirty_bit = 0"<<endl;
    }
}

void InfoFrameVector::print_info_obj_vector(){
    cout<<"page_id: "<<this->page_id<<" | dirty_bit: "<<this->dirty_bit<<" | pin_count"<<
        this->pin_count<<" | ref_bit: "<<this->ref_bit<<endl;
}

//Setters
void InfoFrameVector::set_page_id(int _input){
    this->page_id=_input;
}
void InfoFrameVector::set_dirty_bit(bool _input){
    this->dirty_bit=_input;
}
void InfoFrameVector::set_pin_count(int _input){
    this->pin_count=_input;
}
void InfoFrameVector::set_ref_bit(bool _input){
    this->ref_bit=_input;
}

//Getters
int InfoFrameVector::get_page_id(){
    return this->page_id;
}
bool InfoFrameVector::get_dirty_bit(){
    return this->dirty_bit;
}
int InfoFrameVector::get_pin_count(){
    return this->pin_count;
}
bool InfoFrameVector::get_ref_bit(){
    return this->ref_bit;
}