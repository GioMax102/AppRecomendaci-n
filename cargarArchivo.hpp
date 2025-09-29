#pragma once
#include <fstream>
#include <iostream>
#include <cstdio>    // esta libreria es para poder usar sscanf y sprintf
#include "Orden.hpp"

// Esta función cuenta cuántas líneas tiene el archivo
inline int contarLineas(const char* filename) {
    std::ifstream archivo(filename);
    if (!archivo.is_open()) return -1;
    
    char linea[1024];
    int numLineas = 0;
    while (archivo.getline(linea, sizeof(linea))) {
        numLineas++;
    }
    return numLineas;
}

// Esta función carga los datos del archivo a un arreglo de órdenes
inline bool cargarArchivo(const char* filename, Orden*& arr, int& n) {
    std::cout << "Abriendo archivo: " << filename << std::endl;
    
    // Ahora contaremos cuántas líneas tiene el archivo
    n = contarLineas(filename);
    if (n <= 0) {
        std::cout << "Error: No se pudo abrir el archivo o está vacio" << std::endl;
        return false;
    }
    std::cout << "El archivo tiene " << n << " lineas" << std::endl;

    // Abrimos el archivo para leerlo
    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo" << std::endl;
        return false;
    }

    // Creamos el arreglo donde guardaremos las órdenes
    arr = new Orden[n];

    // Variables para leer cada línea
    char linea[1024];
    char mes[4], restaurante[100], platillo[100];
    int dia, hora, minuto, segundo, precio;
    int ordenesLeidas = 0;

    // Leemos el archivo línea por línea
    while (ordenesLeidas < n && archivo.getline(linea, sizeof(linea))) {

        // Leemos los datos de la línea
        int leidos = sscanf(
            linea,
            "%3s %d %d:%d:%d R:%[^O]O:%[^(](%d)",
            mes, &dia, &hora, &minuto, &segundo, 
            restaurante, platillo, &precio
        );

        // Si pudimos leer los 8 datos que esperábamos
        if (leidos == 8) {
            // Quitamos espacios al final
            int len = strlen(restaurante);
            while (len > 0 && restaurante[len-1] == ' ') {
                restaurante[--len] = '\0';
            }
            
            len = strlen(platillo);
            while (len > 0 && platillo[len-1] == ' ') {
                platillo[--len] = '\0';
            }
            
            // Convertimos los números a texto
            char diaStr[8], horaStr[8], minStr[8], segStr[8], precioStr[16];
            sprintf(diaStr, "%d", dia);
            sprintf(horaStr, "%d", hora);
            sprintf(minStr, "%d", minuto);
            sprintf(segStr, "%d", segundo);
            sprintf(precioStr, "%d", precio);

            // Guardamos los datos en el arreglo
            arr[ordenesLeidas].setFromTokens(
                mes, diaStr, horaStr, minStr, segStr,
                restaurante, platillo, precioStr
            );
            ordenesLeidas++;
        }
    }

    // Si no pudimos leer ninguna línea, hay un error
    if (ordenesLeidas == 0) {
        std::cout << "Error: No se pudo leer ninguna linea" << std::endl;
        delete[] arr;
        arr = nullptr;
        archivo.close();
        return false;
    }
    
    // Si leímos menos líneas de las esperadas
    if (ordenesLeidas < n) {
        std::cout << "Aviso: Solo se leyeron " << ordenesLeidas << " lineas de " << n << std::endl;
        n = ordenesLeidas;
    }
    
    archivo.close();
    return true;
}
