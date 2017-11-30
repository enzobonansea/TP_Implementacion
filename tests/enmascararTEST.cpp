#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(enmascararTEST, testDeLasConsignas){
    //inicializacion
    lista_intervalos tiempos = {    {0.02, 0.04},
                                    {0.07, 0.11},
                                    {0.12, 0.13}    };
    tiempo dur = 0.15;
    //ejercicio
    vector<bool> resultadoDelAlgoritmo = enmascarar(dur, tiempos);
    //check
    vector<bool> resultadoReal = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0};
    EXPECT_EQ(resultadoDelAlgoritmo, resultadoReal);
}

TEST(enmascararTEST, testPropio) {
    //inicializacion
    lista_intervalos tiempos = {{0.00, 0.03},
                                {0.05, 0.07},
                                {0.08, 0.09}};
    tiempo dur = 0.10;
    //ejercicio
    vector<bool> resultadoDelAlgoritmo = enmascarar(dur, tiempos);
    //check
    vector<bool> resultadoReal = {1, 1, 1, 0, 0, 1, 1, 0, 1, 0};
    EXPECT_EQ(resultadoDelAlgoritmo, resultadoReal);
}