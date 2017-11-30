#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(resultadoFinal, salaCompleta){
cout << "El F1-score promedio de la sala es: ";
int frecuencia, profundidad, duracion;
vector<string> archivos = {"datos/spkr0.dat",
                           "datos/spkr1.dat",
                           "datos/spkr2.dat",
                           "datos/spkr3.dat",
                           "datos/spkr4.dat",
                           "datos/spkr5.dat"};
sala reunion = cargarSalaAudio(archivos, frecuencia, profundidad, duracion);
int umbral = 7605;
cout << resultadoFinal(reunion, frecuencia, profundidad, umbral) << endl;
EXPECT_TRUE(true);
/* este test siempre va a ser pasado, pero lo que me interesa a mi es el valor del
 * estadistico que imprimo por pantalla */
}