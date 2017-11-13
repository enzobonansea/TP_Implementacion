#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(compararSilencios, persona0){
    cout << "El F1-score para la persona 0 es: ";
    int frecuencia, profundidad, duracion = 0;
    audio persona0 = leerVectorAudio("datos/spkr0.dat", frecuencia, profundidad, duracion);
    int locutor = 0;
    int umbral = 3500;
    cout << compararSilencios(persona0, frecuencia, profundidad, locutor, umbral);
    EXPECT_TRUE(true);
    /* este test siempre va a ser pasado, pero lo que me interesa a mi es el valor del
     * estadistico que imprimo por pantalla */
}

TEST(compararSilencios, salaCompleta){
    cout << "El F1-score promedio de la sala es: ";
    int frecuencia, profundidad, duracion = 0;
    vector<string> archivos = {"datos/pzm.dat",
                               "datos/spkr0.dat",
                               "datos/spkr1.dat",
                               "datos/spkr2.dat",
                               "datos/spkr3.dat",
                               "datos/spkr4.dat",
                               "datos/spkr5.dat"};
    sala reunion = cargarSalaAudio(archivos, frecuencia, profundidad, duracion);
    int umbral = 4000;
    cout << resultadoFinal(reunion, frecuencia, profundidad, umbral);
    EXPECT_TRUE(true);
    /* este test siempre va a ser pasado, pero lo que me interesa a mi es el valor del
     * estadistico que imprimo por pantalla */
}