#include "../ejercicios.h"
#include "gtest/gtest.h"

TEST(elAcaparadorTEST, prueba){
    sala m = {
            {1,2,3,4,5,6},
            {0,0,8,6,7,8},
            {10,0,0,9,4,5},
            {5,7,8,9,2,1},
    };
    int freq = 3;
    int prof = 4;
    EXPECT_EQ(3, elAcaparador(m, freq, prof));
}