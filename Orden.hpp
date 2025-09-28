#pragma once
#include <cstring>
#include <cstdlib>

class Orden {
private:
    char mes_[4]; 
    int dia_{};
    int hora_{};
    int minuto_{};
    int segundo_{};
    char restaurante_[64]{};
    char platillo_[64]{};
    int precio_{};


    int mesInt_{}; 
    int claveSeg_{}; 


    static int parseMesEsp(const char* m) {
        if (!m || !m[0]) return 0;

        // Convertir a mayúsculas
        char a = m[0];
        if (a >= 'a' && a <= 'z') a = a - 32;
        char b = m[1];
        if (b >= 'a' && b <= 'z') b = b - 32;
        char c = m[2];
        if (c >= 'a' && c <= 'z') c = c - 32;


        if (a=='E' && b=='N') return 1; // Ene
        if (a=='F') return 2; // Feb
        if (a=='M' && c=='R') return 3; // Mar
        if (a=='A' && b=='B') return 4; // Abr
        if (a=='M' && c=='Y') return 5; // May
        if (a=='J' && c=='N') return 6; // Jun
        if (a=='J' && c=='L') return 7; // Jul
        if (a=='A' && b=='G') return 8; // Ago
        if (a=='S') return 9; // Sep
        if (a=='O') return 10; // Oct
        if (a=='N') return 11; // Nov
        if (a=='D') return 12; // Dic
        return 0;
    }

    static int toInt(const char* s) { return s ? std::atoi(s) : 0; }


    static void copyStr(char* dst, const char* src, int max) {
    if (!dst) return;
    if (!src) { dst[0]='\0'; return; }
    std::strncpy(dst, src, max-1); dst[max-1]='\0';
    }


    static int claveDesde(int mes, int dia, int h, int m, int s) {
    // Usamos meses de 28 días para conseguir una cronología simple y estable
    return s + m*60 + h*3600 + dia*24*3600 + mes*28*24*3600;
    }


public:
    Orden() { mes_[0]='\0'; }
    // Cargar desde tokens ya extraídos (char*)
    void setFromTokens(const char* mes, const char* dia, const char* hora,
                        const char* minuto, const char* segundo,
                        const char* restaurante, const char* platillo,
                        const char* precio) {

    copyStr(mes_, mes, 4);
    dia_ = toInt(dia);
    hora_ = toInt(hora);
    minuto_ = toInt(minuto);
    segundo_ = toInt(segundo);
    // ignoramos R antes del nomnre del restaurante y O antes del platillo,
    // pero por simplicidad asumimos que el token ya viene limpio.
    copyStr(restaurante_, restaurante, 64);
    copyStr(platillo_, platillo, 64);
    precio_ = toInt(precio);
    mesInt_ = parseMesEsp(mes_);
    claveSeg_ = claveDesde(mesInt_, dia_, hora_, minuto_, segundo_);
}

    // Getters sencillos
    const char* mes() const { return mes_; }
    int dia() const { return dia_; }
    int hora() const { return hora_; }
    int minuto() const { return minuto_; }
    int segundo() const { return segundo_; }
    const char* restaurante() const { return restaurante_; }
    const char* platillo() const { return platillo_; }
    int precio() const { return precio_; }
    int mesInt() const { return mesInt_; }
    int claveSeg() const { return claveSeg_; }
};