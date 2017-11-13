#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(sacarPausasTEST,pausasEnELMedio){
    audio a = {2,2,2,0,0,0,0,2,4,0,0,0,0,2,4,5,6};
    vector<int> res = sacarPausas(a,4,16,0);
    vector<int> exp = {2,2,2,2,4,2,4,5,6};
    EXPECT_EQ(res,exp);

}
