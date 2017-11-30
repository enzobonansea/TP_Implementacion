//
// Created by jose ampuero on 06/11/2017.
//

#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>


using namespace std;

TEST (flashElPerezosoTEST, prueba1){
    int freq = 4;
    int prof = 16;

    sala m = {  {1,0,2,1,0,1},
                {2,1,0,1,2,3},
                {4,5,1,7,1,9},
                {1,1,1,1,1,1}   };
    sala res = {    {1,0,0,1,2,1,1,0,0,0,1},
                    {2,1,1,0,0,0,1,1,2,2,3},
                    {4,4,5,3,1,4,7,4,1,5,9},
                    {1,1,1,1,1,1,1,1,1,1,1}    };

    EXPECT_EQ (flashElPerezoso(m, freq, prof), res);
}

TEST(flashElPerezosoTEST, prueba2){
    int freq = 4;
    int prof = 16;
    sala m = {  {5,11,2,3},
                {1,3,5,1},
                {4,1,2,5}  };
    sala exp = {  {5, 8, 11, 6, 2, 2, 3},
                  {1, 2, 3, 4, 5, 3, 1},
                  {4, 2, 1, 1, 2, 3, 5}  };
    sala res = flashElPerezoso(m, freq, prof);
    EXPECT_EQ(res, exp);

}