//
// Created by Pablo on 01/10/2017.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "Funciones_TPI.h"

using namespace std;

void grabarVectorAudio(vector<int> vec, string nombreArchivo) {
    ofstream miArchivo;
    miArchivo.open(nombreArchivo.c_str());
    if(miArchivo.is_open()) {
        miArchivo << vec[0];
        for(int i = 1; i < vec.size() ; i++) {
            miArchivo << " " << vec[i];
        }
    }
    else{
        cout << "Error grabando el archivo." << endl;
    }
    miArchivo.close();
}

audio leerVectorAudio(string nombreArchivo, int& frecuencia, int& profundidad, int& duracion) {
    ifstream miArchivo;
    int val;
    audio vec;
    int contador = 0;

    miArchivo.open(nombreArchivo.c_str(), ifstream::in);
    if(miArchivo.is_open()) {
        while(!miArchivo.eof()) {
            if(contador == 0)
                miArchivo >> frecuencia;
            else {
                if(contador == 1) {
                    miArchivo >> profundidad;
                }
                else {
                    if(contador == 2)
                        miArchivo >> duracion;
                    else
                    {
                        miArchivo >> val;
                        vec.push_back(val);
                    }
                }
            }
            contador++;
        }
        if(contador == 0)
            cout << "Archivo vacio." << endl;
    }
    else
        cout << "Error leyendo el archivo." << endl;

    miArchivo.close();
    return vec;
}


sala cargarSalaAudio(vector<string> archivos, int& frecuencia, int& profundidad, int& duracion) {
    sala m;
    // recorro los nombres de los archivos y cargo cada uno de los vectores al objeto sala
    for(int i=0;i < archivos.size();i++) {
        audio spkr = leerVectorAudio(archivos[i], frecuencia, profundidad, duracion);
        m.push_back(spkr);
    }
    return m;
}

sala cargarSalaAudio(vector<string> archivos, int& frecuencia, int& profundidad, int& duracion,int ini, int longitud) {
    sala m;
    // recorro los nombres de los archivos y cargo cada uno de los vectores al objeto sala
    for(int i=0;i < archivos.size();i++) {
        audio spkr = leerVectorAudio(archivos[i], frecuencia, profundidad, duracion);
        m.push_back(subAudio(spkr,ini,longitud));
    }
    return m;
}

void calcularEstadisticos(audio vec, float& media, float& std) {
    int i;
    float cum_val = 0, mult;
    // inicializo las salidas
    media = 0;
    std = 0;
    // calculo media
    for(i=0;i<vec.size();i++)
        cum_val += vec[i];
    media = cum_val / vec.size();
    // calculo std
    cum_val = 0;
    for(i=0;i<vec.size();i++) {
        mult = vec[i] - media;
        cum_val += mult * mult;
    }
    std = sqrt(cum_val / vec.size());
}

audio subAudio(audio in, int ini, int longitud) {
    audio out;
    if(ini+longitud < in.size())
        out = audio(in.begin()+ini,in.begin()+ini+longitud);
    else
        out = audio(in.begin()+ini,in.end());
    return out;
}

float correlacion(audio x, audio y) {
    int y_nelem = y.size();
    float x_media, y_media, x_std, y_std;
    float corr = 0;
    // actualizo los estadisticos de la seccion de x
    calcularEstadisticos(x,x_media,x_std);
    calcularEstadisticos(y,y_media,y_std);
    for(int j=0;j<y_nelem;j++)
        corr += (x[j] - x_media) * (y[j] - y_media);
    // calculo ahora la esperanza y normalizo por el desvio estandar
    corr = y_std > 0 && x_std > 0 ? corr / y_nelem / (y_std * x_std) : 0;
    return corr;
}

