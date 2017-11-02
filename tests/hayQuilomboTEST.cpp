#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(hayQuilomboTEST, quilombo){
    //inicializacion
    sala m = {  {1, 0, 3, 4, 1, 0},
                {0, 1, 0, 0, 3, 0}  };
    int prof = 16;
    int freq = 10; //en 10 muestras transcurre 1s sii en 1 muestra transcurren 0.1 s
    int umbral = 0;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_TRUE(res);
}

TEST(hayQuilomboTEST, sinQuilombo){
    //inicializacion
    sala m = {  {1, 0, 3, 4, 0, 1},
                {0, 1, 0, 0, 3, 0}  };
    int prof = 16;
    int freq = 10; //en 10 muestras transcurre 1s sii en 1 muestra transcurren 0.1 s
    int umbral = 0;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_FALSE(res);
}