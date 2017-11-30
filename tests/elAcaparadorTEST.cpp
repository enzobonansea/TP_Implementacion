#include "../ejercicios.h"
#include "gtest/gtest.h"

TEST(elAcaparadorTEST, prueba1){
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

TEST(elAcaparadorTEST, prueba2){
    sala m = {  {0,1,3,4,6,7,8,2,4,10},      //4.5
                {1,2,4,5,6,7,4,7,2,5},      //4.3
                {1,2,4,5,2,5,3,1,3,2}  };   //2.8
    int freq = 4;
    int prof = 4;
    int res = elAcaparador(m, freq, prof);
    EXPECT_EQ(0, res);
}