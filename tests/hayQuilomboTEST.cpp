#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;


TEST(hayQuilomboTEST, quilombo1){
    //inicializacion
    sala m = { {1, 0},
               {1, 0} };
    int prof = 16;
    int freq = 10;
    int umbral = 0;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_TRUE(res);
}

TEST(hayQuilomboTEST, sinQuilombo1){
    //inicializacion
    sala m = { {1, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0 },
               {0, 0, 0, 0, 0, 1, 0, 2, 3, 0, 0} };
    int prof = 16;
    int freq = 10;
    int umbral = 0;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_FALSE(res);
}

TEST(hayQuilomboTEST, quilombo2){
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

TEST(hayQuilomboTEST, sinQuilombo2){
    //inicializacion
    sala m = {  {1, 0, 0, 0, 3, 4, 0, 0, 0, 1, 1, 1},
                {0, 0, 0, 1, 0, 0, 0, 3, 1, 0, 0, 0}  };
    int prof = 16;
    int freq = 10; //en 10 muestras transcurre 1s sii en 1 muestra transcurren 0.1 s
    int umbral = 0;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_FALSE(res);
}

TEST(hayQuilomboTEST, quilombo3){
    //inicializacion
    sala m = {  {6, 0, 2, 4, 1, 10},
                {0, 1, 0, 3, 3, 0},
                {0, 0, 9, 9, 9, 3}  };
    int prof = 16;
    int freq = 19;
    int umbral = 2;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_TRUE(res);
}

TEST(hayQuilomboTEST, sinQuilombo3){
    //inicializacion
    sala m = {  {1, 1, 1, 1, 1, 1},
                {0, 1, 0, 0, 2, 0},
                {0, 0, 9, 9, 9, 3}  };
    int prof = 16;
    int freq = 19;
    int umbral = 2;
    //ejercicio
    bool res = hayQuilombo(m, prof, freq, umbral);
    //check
    EXPECT_FALSE(res);
}


