#include "TablaMetadata.h"

TablaMetadata::TablaMetadata(int num_frames)
{
    this->num_frames_tabla=num_frames;
    this->full_frames=false;
}

TablaMetadata::TablaMetadata(){
    this->num_frames_tabla=0;
    this->full_frames=false;
}


TablaMetadata::~TablaMetadata(){}

bool TablaMetadata::tabla_vacia(){
    if ((this->mapFramesTabla).empty()==true) {
        return true;
    } 
    else 
    {
        return false;
    }
}

void TablaMetadata::agregar_frame_tabla(InfoFrameVector& vect_metadata,int id_frame){
    bool tablaVacia=tabla_vacia();
    if (tablaVacia==true)
    {
        this->mapFramesTabla[id_frame]=vect_metadata;
        imprimir_toda_tabla_metadata();
        return;
    }
    else{
        bool existe_frame=comprobar_existe_frame(id_frame);
        if (existe_frame==false && this->full_frames==false)
        {
            if (id_frame <= this->num_frames_tabla)
            {
                (this->mapFramesTabla)[id_frame]=vect_metadata;
            }
            else
            {
                this->full_frames=true;
                cout<<"No puede crear mas frames"<<endl;
            }
        }
    }
}

void TablaMetadata::imprimir_toda_tabla_metadata(){
    // Recorremos el mapa e imprimimos los elementos
    for (auto elemento : (this->mapFramesTabla)) {
        int clave = elemento.first;
        InfoFrameVector objeto = elemento.second;
        std::cout << "Clave: " << clave << ", ";
        objeto.print_info_obj_vector();
        std::cout << std::endl;
    }
}

void TablaMetadata::imprimir_un_frame(int id_frame){
    // Buscar el id_frame en el mapa
    auto it = (this->mapFramesTabla).find(id_frame);
    if (it != (this->mapFramesTabla).end()) {
        int clave = it->first; // clave es el frame
        cout << "Frame: " << clave << ", ";
        InfoFrameVector& objeto = it->second;
        objeto.print_info_obj_vector();
        cout << endl;
    } else {
        cout << "El frame con el id " << id_frame << " no se encontro en la tabla metadata." << endl;
    }
}

void TablaMetadata::increment_pinCount_pagina(int  idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina)
            {
                objeto.set_pin_count(objeto.get_pin_count()+1);
            }
            else{
                continue;
            }
        }
    }
}

bool TablaMetadata::comprobar_existe_frame(int id_frame){
    // Recorremos el mapa e imprimimos los elementos
    for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
    {
        int clave = it->first;//clave es el frame
        if (clave==id_frame)
        {
            return true;
        }
        else
        {
            continue;
        }
        
    }
    return false;
}

bool TablaMetadata::comprobar_existe_pagina(int idPagina){
    for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
    {
        int clave = it->first;//clave es el frame
        InfoFrameVector& objeto = it->second;
        if (objeto.page_id==idPagina)
        {
            return true;
            break;
        }
        else{
            continue;
        }
    }
    return false;
}

void TablaMetadata::agregar_pagina_tabla_metadata(int id_pag){
    bool _tabla_vacia=tabla_vacia();
    if (_tabla_vacia==true)//en caso este vacía
    {
        InfoFrameVector *ptr_objeto_vector=new InfoFrameVector();
        (*ptr_objeto_vector).set_page_id(id_pag);
        agregar_frame_tabla((*ptr_objeto_vector),1);
        cout<<"pagina_id agregada a la tabla metadata"<<endl;
    }
    else
    {
        
        bool existe_frame=comprobar_existe_pagina(id_pag);
        if (existe_frame==false && this->full_frames==false)
        {
            for (int i = 1; i <= this->num_frames_tabla; i++)
            {
                auto it = (this->mapFramesTabla).find(i);
                if (it != (this->mapFramesTabla).end()) 
                {
                    cout<<"La pagina_id existe en el frame: "<<i<<endl;
                    break;
                } 
                else 
                {
                    int clave = it->first; // clave es el frame
                    InfoFrameVector objeto_vector;
                    objeto_vector.set_page_id(id_pag);
                    agregar_frame_tabla(objeto_vector,i);
                    cout<<"pagina_id agregada a la tabla metadata"<<endl;
                    break;
                }
            }
        }
        else if(existe_frame==true)
        {
            cout<<"Su pagina ya existe, no se puede agregar"<<endl;
        }
        else if (existe_frame==false && this->full_frames==true)
        {
            int idPagina_retirar=CLOCK();
        }
    }
    
    
}

void TablaMetadata::decrement_pinCount_pagina(int idPagina){
    for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
    {
        int clave = it->first;//clave es el frame
        InfoFrameVector& objeto = it->second;
        if (objeto.page_id==idPagina)
        {
            objeto.set_pin_count(objeto.get_pin_count()-1);
        }
        else{
            continue;
        }
    }
}

int TablaMetadata::get_id_frame_segun_idPagina(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina)
            {
                return clave;
            }
            else{
                continue;
            }
        }
    }
    else
    {
        cout<<"Su pagina no existe en la tabla metadata - obtencion idFrame fallida -"<<endl;
    }
}

bool TablaMetadata::dirtyBit_clean(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina && objeto.get_dirty_bit()==true)
            {
                return true;
            }
            else if (objeto.page_id==idPagina && objeto.get_dirty_bit()==false)
            {
                return false;
            }
            else{
                continue;
            }
        }
    }
    
}

bool TablaMetadata::pinCount_clean(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina && objeto.get_pin_count()==0)
            {
                return true;
            }
            else if (objeto.page_id==idPagina && objeto.get_pin_count()!=0)
            {
                return false;
            }
            else{
                continue;
            }
        }
    }
}

bool TablaMetadata::refBit_clean(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina && objeto.get_ref_bit()==0)
            {
                return true;
            }
            else if (objeto.page_id==idPagina && objeto.get_ref_bit()!=0)
            {
                return false;
            }
            else{
                continue;
            }
        }
    }
}

void TablaMetadata::eliminar_pagina_metadata(int idPagina){

    bool pagina_existe=comprobar_existe_pagina(idPagina);

    if (pagina_existe==true)
    {
        int id_frame_dePagina_a_eliminar=get_id_frame_segun_idPagina(idPagina);

        if ((mapFramesTabla).find(id_frame_dePagina_a_eliminar) != (mapFramesTabla).end()) 
        {
            // Eliminar el elemento con la clave especificada
            (mapFramesTabla).erase(id_frame_dePagina_a_eliminar);
            cout << "Se elimino el elemento con clave " << id_frame_dePagina_a_eliminar << " del mapa." << endl;
        } 
        else 
        {
            cout << "La clave " << id_frame_dePagina_a_eliminar << " no se encontro en el mapa." << endl;
        }
    }
    else
    {
        cout<<"Su pagina no existe en la tabla metadata - eliminacion fallida -"<<endl;
    }
    
}


void TablaMetadata::reemplazar_pagina_metadata(int idPaginaOld, int idPaginaNew){
    bool paginaOld_existe=comprobar_existe_pagina(idPaginaOld);
    if (paginaOld_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPaginaOld)
            {
                objeto.set_page_id(idPaginaNew);
                objeto.set_dirty_bit(false);
                objeto.set_pin_count(1);
                objeto.set_ref_bit(1);
            }
            else{
                continue;
            }
        }
    }
    
}

void TablaMetadata::update_dirtyBit(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina)
            {
                objeto.set_dirty_bit(!objeto.get_dirty_bit());
                break;
            }
            else{
                continue;
            }
        }
    }
}

void TablaMetadata::update_refBit(int idPagina){
    bool pagina_existe=comprobar_existe_pagina(idPagina);
    if (pagina_existe==true)
    {
        for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
        {
            int clave = it->first;//clave es el frame
            InfoFrameVector& objeto = it->second;
            if (objeto.page_id==idPagina)
            {
                objeto.set_ref_bit(!objeto.get_ref_bit());
                break;
            }
            else{
                continue;
            }
        }
    }
}


int TablaMetadata::CLOCK()
{
    int cantidadFrames=this->num_frames_tabla;
    bool alguna_paginaPor_liberar=false;
    for (int i = 1; i <= cantidadFrames; i++)
    {
        map<int, InfoFrameVector>::iterator manecilla_ptr_frames = (this->mapFramesTabla).find(i);
        // Verificar si la clave existe antes de acceder
        if (manecilla_ptr_frames != (mapFramesTabla).end()) {
            // Acceder al valor asociado a la clave deseada utilizando el puntero al iterador
            InfoFrameVector& objeto = manecilla_ptr_frames->second;
            if (objeto.get_ref_bit()==false && objeto.get_pin_count()==0)
            {
                if (objeto.get_dirty_bit()==true)
                {
                    //escribir cambios en el disco
                    cout<<"Escribir cambios en el disco por dirtyBit..."<<endl;
                    return objeto.get_page_id();
                    bool alguna_paginaPor_liberar=true;
                }
                else
                {
                    return objeto.get_page_id();
                    alguna_paginaPor_liberar=true;
                }
            
            }
            else
            {
                continue;
            }
        } 
        else 
        {
            cout << "Llegamos al final del ciclo del CLOCK" << endl;
        }
    }
    if (alguna_paginaPor_liberar==false)
    {
        Reset_allRefBit_tablaMetadata();
        CLOCK();
    }
    else{
        cout<<"CLOCK ejecutado con exito"<<endl;
    }
    

}

void TablaMetadata::Reset_allRefBit_tablaMetadata(){
    // Recorremos el mapa e imprimimos los elementos
    for (map<int, InfoFrameVector>::iterator it = ((this->mapFramesTabla)).begin(); 
            it != ((this->mapFramesTabla)).end(); ++it) 
    {
        int clave = it->first;//clave es el frame
        // cout << "Frame: " << clave << ", ";
        InfoFrameVector& objeto = it->second;
        objeto.set_ref_bit(false);
    }
}
