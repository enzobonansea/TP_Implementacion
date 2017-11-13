#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(negacionLogicaTEST, negarMascaraDeLasConsignas){
    //inicializacion
    vector<bool> res = {0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0};
    //ejercicio
    negacionLogica(res);
    //check
    vector<bool> esperado = {1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1};
    EXPECT_EQ(res, esperado);
}