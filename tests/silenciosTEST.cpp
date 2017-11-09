#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(silenciosTEST,unAudio){
    int prof = 16;
    int freq = 35;
    audio a = {0,0,0,0,1,2,3,0,0,0,0,0,5,6,0,0,3};
    lista_intervalos ts = {make_tuple(0,0.1143), make_tuple(0.2,0.3429)} ;

    lista_intervalos t_out = silencios(a,prof,freq,1);
    cout << "encontrados " << ts.size() << " intervalos" << endl;
    ASSERT_EQ(ts.size(),t_out.size());
    for(int i=0;i<ts.size();i++){
        intervalo t1 = ts[i];
        intervalo t2 = t_out[i];

        // test inicio del intervalo
        int m1 = floor(get<0>(t1) * freq);
        int m2 = floor(get<0>(t2) * freq);

        EXPECT_EQ(m1,m2);
        // test fin de intervalo
        m1 = floor(get<1>(t1) * freq);
        m2 = floor(get<1>(t2) * freq);

        EXPECT_EQ(m1,m2);

    }
}
