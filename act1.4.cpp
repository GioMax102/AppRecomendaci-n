#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Horario {
    public: 
        int mes, dia, hora, minuto, segundo;

        Horario(int m, int d, int h, int min, int seg){
            this->mes = m;
            this->dia = d;
            this->hora = h;
            this->minuto = min;
            this->segundo = seg;
        }
        Horario(){
            this->mes = 0;
            this->dia = 0;
            this->hora = 0;
            this->minuto = 0;
            this->segundo = 0;
        }

        void mostrar(){
            printf("Horario: %d, %d,  %d, %d, %d\n", mes, dia, hora, minuto, segundo);
        }
};

class Plato{
    public: 
        char nombre[50];
        int calorias;

        Plato(const char* nom, int cal) {
            strcpy(this->nombre, nom);
            this->calorias = cal;
        }

        Plato(){
            strcpy(this->nombre, "");
            this->calorias = 0;
        }
        void mostrar(){
            printf("Pirmera letra de plaro= %c, cal: %d\n", nombre[0], calorias);
        }
};

class Restaurante{
    public: 
        Horario horario;
        Plato plato; 
        char nombre[50];

        Restaurante(Horario hor, const char* nom, Plato pl){
            this->horario = hor;
            strcpy(this->nombre, nom); 
            this->plato = pl;
        }

        Restaurante(){
            strcpy(this->nombre, "");
        }
        void mostrar(){
            horario.mostrar();
            printf("Pirmera letra de nombre = %c\n", nombre[0]);
            plato.mostrar();
        }
};

int convertirMes(const char* mesStr) {
    // función para convertir mes a num
    const char* meses[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", 
                          "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
    
    for(int i = 0; i < 12; i++) {
        if(strcmp(mesStr, meses[i]) == 0) {
            return i + 1;
        }
    }
    return 1; // Por defecto Enero
}

int leerDatos(Restaurante datos[], int n){
    ifstream input_file("pordenes.txt");
    if(!input_file.is_open()) {
        cout << "Error: file cannot be opened" << endl;
        return 0;
    }
    
    char linea[200];
    char mesStr[10];
    int dia, hora, minuto, segundo;
    char nombreRestaurante[100];
    char nombrePlato[100];
    int calorias;
    char temp;
    
    while(input_file.getline(linea, 200)) {
        // leer mes
        mesStr[0] = linea[0];
        mesStr[1] = linea[1];
        mesStr[2] = linea[2];
        mesStr[3] = '\0';
        
        int mes = convertirMes(mesStr);
        
        // leer fecha
        sscanf(linea + 4, "%d %d:%d:%d", &dia, &hora, &minuto, &segundo);
        
        // encontrar R: y O:
        char* posR = strstr(linea, "R:");
        char* posO = strstr(linea, "O:");
        
        if(posR && posO) {
            // extrar nombre restaurante (entre R: y O:)
            int inicioR = posR - linea + 2; 
            int finR = posO - linea;
            
            strncpy(nombreRestaurante, linea + inicioR, finR - inicioR);
            nombreRestaurante[finR - inicioR] = '\0';
            
            // info plato
            char* parentesis = strchr(posO, '(');
            char* cierreParentesis = strchr(posO, ')');
            
            if(parentesis && cierreParentesis) {
                // nombre plato
                int inicioPlato = posO - linea + 2;
                int finPlato = parentesis - linea;
                
                strncpy(nombrePlato, linea + inicioPlato, finPlato - inicioPlato);
                nombrePlato[finPlato - inicioPlato] = '\0';
                
                // calorías
                sscanf(parentesis + 1, "%d", &calorias);
                
                // crear objetos y guardar en arreglo
                Horario horario(mes, dia, hora, minuto, segundo);
                Plato plato(nombrePlato, calorias);
                datos[n] = Restaurante(horario, nombreRestaurante, plato);
                n++;
            }
        }
    }
    
    input_file.close();
    return n;
}

void mostrarPrimeros10Datos(Restaurante restaurantes[], int totalRestaurantes) {
    cout << "=== PRIMEROS 10 DATOS DEL ARREGLO ===" << endl;
    
    int cantidadAMostrar = (totalRestaurantes < 10) ? totalRestaurantes : 10;
    
    for(int i = 0; i < cantidadAMostrar; i++) {
        cout << i+1 << ". ";
        restaurantes[i].mostrar();
    }
    
    if(totalRestaurantes == 0) {
        cout << "No hay datos en el arreglo" << endl;
    }
}

int main(){
    Restaurante restaurantes[1000];
    int n_res = leerDatos(restaurantes, n_res);
    if(n_res == 0){ return 0; }
    mostrarPrimeros10Datos(restaurantes, n_res);
}

