#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(sacarPausasTEST,pausasEnELMedio){
    audio a = {2,2,2,0,0,0,0,2,4,0,0,0,0,2,4,5,6};
    int freq = 4; // => en a[i] transcurrieron 0.25s
    int prof = 16;
    int umbral = 0; // => ( esSilencio(a[i]) <=> a[i] < 0 )
    vector<int> res = sacarPausas(a,freq,prof,umbral);
    vector<int> exp = {2,2,2,2,4,2,4,5,6};
    EXPECT_EQ(res,exp);

}

TEST(sacarPausasTEST, noPasa) {
    int freq = 40;
    int prof = 16;
    int umbral = 10;
    audio a = {17, 1, 2, 11, 4, 5, 6, 7, 8, 8, 9, 12};
    vector<int> res = sacarPausas(a, freq, prof, umbral);
    vector<int> exp = {17, 1, 2, 11, 12};
    EXPECT_EQ(res, exp);
}