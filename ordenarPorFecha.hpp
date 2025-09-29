#pragma once
#include "Orden.hpp"


inline void swapOrden(Orden& a, Orden& b) { Orden t=a; a=b; b=t; }


// QuickSort 
inline int partitionEnd(Orden* A, int l, int r) {
    int pivot = A[r].claveSeg(); // pivote al final
    int i = l - 1; // i: última posición < pivot
    for (int j=l; j<r; ++j) {
        if (A[j].claveSeg() <= pivot) {
            ++i; swapOrden(A[i], A[j]);
        }
    }
    swapOrden(A[i+1], A[r]);
    return i+1; 
}


inline void quickSort(Orden* A, int l, int r) {
    if (l < r) {
        int p = partitionEnd(A, l, r);
        quickSort(A, l, p-1);
        quickSort(A, p+1, r);
    }
}