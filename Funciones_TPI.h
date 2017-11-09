//
// Created by Pablo on 01/10/2017.
//

#ifndef UTILES_FUNCIONES_TPI_H
#define UTILES_FUNCIONES_TPI_H

#include <iostream>
#include <vector>
#include <fstream>
#include "definiciones.h"

using namespace std;

void grabarVectorAudio(audio vec, string nombreArchivo);
audio leerVectorAudio(string nombreArchivo, int& frecuencia, int& profundidad, int& duracion);
sala cargarSalaAudio(vector<string> arch, int& frecuencia, int& profundidad, int& duracion);
sala cargarSalaAudio(vector<string> arch, int& frecuencia, int& profundidad, int& duracion,int ini, int longitud);
void calcularEstadisticos(audio vec, float& media, float& std);
audio subAudio(audio in, int ini, int longitud);
float correlacion(audio x, audio y);


#endif //UTILES_FUNCIONES_TPI_H
