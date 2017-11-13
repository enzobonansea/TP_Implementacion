
#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(distanciasTEST, testBEEP) {
    int frecuencia, profundidad,duracion;
    int startPOINT, endPOINT;
    lista_distancias dst_spk;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr4.dat"};

    audio pzm = leerVectorAudio("datos/pzm.dat",frecuencia,profundidad,duracion);
    audio frase = subAudio(pzm,POS_SMP_TEST_DISTANCIA,QUANT_SMP_TEST_DISTNACIA);

    startPOINT = POS_SMP_TEST_DISTANCIA - 3000;
    endPOINT = QUANT_SMP_TEST_DISTNACIA + 2 * 3000;
    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion,startPOINT,endPOINT);

    locutor spk = medirLaDistancia(m,frase,frecuencia,profundidad);
    dst_spk = get<1>(spk);

    cout << "locutor " << get<0>(spk) << endl;
    for(int i=0;i<m.size();i++){
        cout << "distancia locutor " << i << " al locutor que dijo la frase " << get<0>(spk);
        cout << ": " << dst_spk[i] << endl;
    }
    EXPECT_EQ(1,get<0>(spk));
}