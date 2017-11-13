#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cargarIntervaloDeHablaTEST, spkr0){
    //inicializacion
    string archivo = "datos/habla_spkr0.txt";
    //ejercicio
    lista_intervalos intervalosCargados = cargarIntervaloDeHabla(archivo);
    bool res = true;
    ifstream entrada;
    entrada.open(archivo, ifstream::in);
    int i = 0;
    while(!entrada.eof()){
        //comparo el contenido de intervalosCargados con contenido de habla_spkr0.txt
        int indice = floor(i / 2);
        float valorReal = 0;
        entrada >> valorReal;
        float valorCargado = 0;
        if(i % 2 == 0) {
            valorCargado = get<0>(intervalosCargados[indice]);
        }
        else {
            valorCargado = get<1>(intervalosCargados[indice]);
        }
        bool condicion = valorCargado == valorReal;
        res &= condicion;
        i++;
    }
    entrada.close();
    //check
    EXPECT_TRUE(res);
}