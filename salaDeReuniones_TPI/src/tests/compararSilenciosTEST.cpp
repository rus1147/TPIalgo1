#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"


using namespace std;

TEST(compararSilenciosTEST, speaker0) {
    int frecuencia, profundidad, duracion;
    audio orig = leerVectorAudio("datos/spkr0.dat", frecuencia, profundidad, duracion);

    float f1 = compararSilencios(orig, frecuencia, profundidad, 0, 10000);

    EXPECT_NEAR(f1, 0.90, 0.01);

}

TEST(resultadoFinalTEST, all_speakers) {
    int frecuencia, profundidad, duracion;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr3.dat",
                                     "datos/spkr4.dat",
                                     "datos/spkr5.dat"};

    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion);
    float f1 = resultadoFinal(m, frecuencia, profundidad, 15000);

    EXPECT_NEAR(f1, 0.80, 0.01);

}
