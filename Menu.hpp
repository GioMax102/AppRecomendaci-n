#pragma once
#include <iostream>

class Menu {
public:
    Menu();                        
    void mostrar();                 
private:
    void cargarArchivo();           
    void ordenarPorFecha();         
    void buscarPorRangoFechas();    
    void guardarOrdenamiento();     
};
