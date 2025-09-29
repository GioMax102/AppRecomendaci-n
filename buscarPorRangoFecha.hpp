#pragma once
#include <iostream>
#include "Orden.hpp"


inline int claveDesdeFecha(int mes, int dia, int hora, int minuto=0, int segundo=0) {
    return segundo + minuto*60 + hora*3600 + dia*24*3600 + mes*28*24*3600;
}


//primer índice con clave
inline int buscarInicio(const Orden* A, int n, int target) {
    int l=0, r=n-1, ans=n;
    while (l<=r) {
        int m=(l+r)/2;
        if (A[m].claveSeg() >= target) { ans=m; r=m-1; }
        else l=m+1;
    }
    return ans;
}


//último índice con clave
inline int buscarFin(const Orden* A, int n, int target) {
    int l=0, r=n-1, ans=-1;
    while (l<=r) {
        int m=(l+r)/2;
        if (A[m].claveSeg() <= target) { ans=m; l=m+1; }
        else r=m-1;
    }
    return ans;
}


inline void mostrarRango(const Orden* A, int i, int j) {
    if (i>j) {
        std::cout << "(sin resultados)\n"; 
        return; 
    }
    for (int k=i; k<=j; ++k) {
        std::cout << (k+1) << ". " << A[k].mes() << ' ' << A[k].dia() << ' '
                << A[k].hora() << ':' << A[k].minuto() << ':' << A[k].segundo()
                << " R:" << A[k].restaurante() << " O:" << A[k].platillo()
                << " (" << A[k].precio() << ")\n";
    }
}