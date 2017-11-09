//
// Created by Pablo on 03/10/2017.
//

#ifndef UTILES_DEFINICIONES_H
#define UTILES_DEFINICIONES_H

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


// CONSTANTES
#define UMBRAL_SILENCIO                7500
#define POS_SMP_TEST_DISTANCIA       402000
#define QUANT_SMP_TEST_DISTNACIA      14600

#define VELOCIDAD_SONIDO                340.29 // metro/seg

// DEFINICIONES DE TIPO
typedef vector<int> audio;
typedef vector<audio> sala;
typedef float tiempo;
typedef tuple<tiempo,tiempo> intervalo;
typedef vector<intervalo> lista_intervalos;
typedef vector<float> lista_distancias;
typedef tuple<int,lista_distancias> locutor;

#endif //UTILES_DEFINICIONES_H
