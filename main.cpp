#include <iostream>
#include "gtest/gtest.h"
#include "ejercicios.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "Implementando TPI!!" << endl;
    resultadosEjercicio7(500);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}