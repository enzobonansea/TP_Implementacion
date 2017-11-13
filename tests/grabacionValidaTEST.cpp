#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(grabacionValidaTEST, unaValida) {
    int freq = 4;
    int prof = 16;
    audio a = {1,2,3,4,5,6};

    EXPECT_EQ(true,grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, otraValida) {
    int freq = 12;
    int prof = 32;
    audio a = {1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};
    EXPECT_EQ(true,grabacionValida(a,32,12));
}

TEST(grabacionValidaTEST, NoValidaCon0) {
    int freq = 4;
    int prof = 16;
    audio a = {0,0,0,0,0,0,0};

    EXPECT_EQ(false,grabacionValida(a,prof,freq));
}
TEST(grabacionValidaTEST, NoValidaConProf) {
    int freq = 4;
    int prof = 16;
    audio a = {1,70000,0,5,0,1};

    EXPECT_EQ(false,grabacionValida(a,prof,freq));
}
