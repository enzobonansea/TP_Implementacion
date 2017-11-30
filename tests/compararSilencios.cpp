#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(compararSilencios, persona0){
    cout << "El F1-score para la persona 0 es: ";
    int frecuencia, profundidad, duracion = 0;
    audio persona0 = leerVectorAudio("datos/spkr0.dat", frecuencia, profundidad, duracion);
    int locutor = 0;
    int umbral = 7605;
    cout << compararSilencios(persona0, frecuencia, profundidad, locutor, umbral) << endl;
    EXPECT_TRUE(true);
    /* este test siempre va a ser pasado, pero lo que me interesa a mi es el valor del
     * estadistico que imprimo por pantalla */
}