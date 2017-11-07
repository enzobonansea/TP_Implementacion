#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(silenciosTEST, unAudio) {
    int prof = 16;
    int freq = 35;
    audio a = {0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 5, 6, 0, 0, 3};
    lista_intervalos ts = {{0,   0.1142},
                           {0.2, 0.3428}};

    lista_intervalos t_out = silencios(a, prof, freq, 1);
    cout << "encontrados " << ts.size() << " intervalos" << endl;
    ASSERT_EQ(ts.size(), t_out.size());
    for (int i = 0; i < ts.size(); i++) {
        intervalo t1 = ts[i];
        intervalo t2 = t_out[i];
        EXPECT_NEAR(get<0>(t1), get<0>(t2), 0.1);
        EXPECT_NEAR(get<1>(t1), get<1>(t2), 0.1);
    }
}

