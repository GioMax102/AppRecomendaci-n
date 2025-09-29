#pragma once
#include <iostream>
#include <limits>
#include "Orden.hpp"
#include "cargarArchivo.hpp"
#include "ordenarPorFecha.hpp"
#include "guardarOrdenamiento.hpp"
#include "buscarPorRangoFecha.hpp"

// Función auxiliar para leer números con validación
inline int leerEntero(const char* mensaje, int min, int max) {
    int numero;
    while (true) {
        std::cout << mensaje;
        if (std::cin >> numero && numero >= min && numero <= max) {
            return numero;
        }
        std::cout << "Por favor ingresa un numero entre " << min << " y " << max << "\n";
        std::cin.clear();
    }
}

// Esta clase maneja el menú principal del programa
class Menu {
private:
    Orden* datos;        // Arreglo donde guardamos las órdenes
    int numOrdenes;      // Cuántas órdenes tenemos
    int ultimoInicio;    // Para recordar el inicio del último rango buscado
    int ultimoFin;       // Para recordar el fin del último rango buscado

public:
    Menu() : datos(nullptr), numOrdenes(0), ultimoInicio(0), ultimoFin(-1) {}
    ~Menu() { if (datos) delete[] datos; }

    // Función principal que muestra el menú y procesa las opciones
    void run() {
        int opcion;
        do {
            // Mostrar las opciones al usuario
            std::cout << "\n=== MENU PRINCIPAL ===\n";
            std::cout << "1. Cargar archivo y ordenar\n";
            std::cout << "2. Mostrar ordenes\n";
            std::cout << "3. Buscar por rango de fecha\n";
            std::cout << "4. Guardar resultado en archivo\n";
            std::cout << "0. Salir\n";
            std::cout << "Elige una opcion: ";
            std::cin >> opcion;

            // Procesar la opción elegida
            switch (opcion) {
                case 1: {
                    // Limpiamos memoria por si habia datos
                    delete[] datos;
                    datos = nullptr;
                    numOrdenes = 0;

                    std::cout << "Cargando archivo orders.txt...\n";
                    if (cargarArchivo("orders.txt", datos, numOrdenes)) {
                        std::cout << "Archivo cargado Ordenando " << numOrdenes << " ordenes...\n";
                        quickSort(datos, 0, numOrdenes-1);
                        std::cout << "Ordenamiento completado\n";
                    }
                    break;
                }
                case 2: {
                    if (!datos) {
                        std::cout << "Primero carga el archivo\n";
                        break;
                    }
                    int cuantas = leerEntero("Cuantas ordenes quieres ver? ", 1, numOrdenes);
                    mostrarRango(datos, 0, cuantas-1);
                    break;
                }
                case 3: {
                    if (!datos) {
                        std::cout << "Primero carga el archivo\n";
                        break;
                    }
                    std::cout << "\n== Fecha de INICIO ==\n";
                    int mesInicio = leerEntero("Mes (1-12): ", 1, 12);
                    int diaInicio = leerEntero("Dia (1-28): ", 1, 28);
                    int horaInicio = leerEntero("Hora (0-23): ", 0, 23);

                    std::cout << "\n== Fecha de FIN ==\n";
                    int mesFin = leerEntero("Mes (1-12): ", 1, 12);
                    int diaFin = leerEntero("Dia (1-28): ", 1, 28);
                    int horaFin = leerEntero("Hora (0-23): ", 0, 23);

                    int claveInicio = claveDesdeFecha(mesInicio, diaInicio, horaInicio);
                    int claveFin = claveDesdeFecha(mesFin, diaFin, horaFin, 59, 59);

                    ultimoInicio = buscarInicio(datos, numOrdenes, claveInicio);
                    ultimoFin = buscarFin(datos, numOrdenes, claveFin);

                    if (ultimoInicio <= ultimoFin) {
                        std::cout << "\nSe encontraron " << (ultimoFin-ultimoInicio+1) << " ordenes:\n";
                        mostrarRango(datos, ultimoInicio, ultimoFin);
                    } else {
                        std::cout << "No hay ordenes en ese rango de fechas.\n";
                    }
                    break;
                }
                case 4: {
                    if (!datos) {
                        std::cout << "Primero carga el archivo\n";
                        break;
                    }
                    if (ultimoInicio > ultimoFin) {
                        std::cout << "Primero haz una búsqueda\n";
                        break;
                    }
                    if (guardarRango("output.txt", datos, ultimoInicio, ultimoFin)) {
                        std::cout << "Se guardaron " << (ultimoFin-ultimoInicio+1) << " ordenes en un archivo!\n";
                    }
                    break;
                }
                case 0:
                    std::cout << "Gracias por usar el programa\n";
                    break;
                default:
                    std::cout << "Opcion no válida, intenta de nuevo\n";
            }
        } while (opcion != 0);
    }
};
