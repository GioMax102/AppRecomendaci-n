#pragma once
#include <fstream>
#include <iostream>
#include "Orden.hpp"

inline bool guardarRango(const char* filename, const Orden* A, int i, int j)
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cout << "No se pudo crear '" << filename << "'\n";
        return false;
    }
    if (i > j) {
        out << "(sin resultados)\n";
        out.close();
        return true;
    }

    for (int k = i; k <= j; ++k) {
        out << A[k].mes() << ' ' << A[k].dia() << ' '
            << A[k].hora() << ':' << A[k].minuto() << ':' << A[k].segundo()
            << " R:" << A[k].restaurante()
            << " O:" << A[k].platillo()
            << '(' << A[k].precio() << ")\n";
    }
    out.close();
    return true;
}