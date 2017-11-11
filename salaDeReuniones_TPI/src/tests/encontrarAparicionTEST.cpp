#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"


using namespace std;

TEST(encontrarAparicionTEST, smallEncontrarAparicion) {
    audio s = {0, 0, 0, -3, -3, -3, -3, 3, 0, 0};
    audio target = {-1, -1, -1, -1, 1};
    int freq = 4;
    int prof = 16;
    EXPECT_EQ(3,encontrarAparicion( s,target, freq, prof));
}

TEST(encontrarAparicionTEST, smallEncontrarAparicion2) {
    audio s = {0, 0, 0, -3, -3, -3, -3, 3, 0, 0};
    audio target = {1, 1 , 1 , 1 , -1};
    int freq = 4;
    int prof = 16;
    EXPECT_EQ(3,encontrarAparicion( s,target, freq, prof));
}

TEST(encontrarAparicionTEST, encontrarAparicion) {
    int frecuencia, profundidad,duracion;
    int startPOINT, endPOINT;
    audio pzm = leerVectorAudio("datos/pzm.dat",frecuencia,profundidad,duracion);
    audio frase = subAudio(pzm,POS_SMP_TEST_DISTANCIA,QUANT_SMP_TEST_DISTNACIA);
    startPOINT = POS_SMP_TEST_DISTANCIA - 3000;
    endPOINT = QUANT_SMP_TEST_DISTNACIA + 2 * 3000;
    audio speaker = leerVectorAudio("datos/spkr1.dat",frecuencia,profundidad,duracion);
    int posMxCrr = encontrarAparicion(subAudio(speaker,startPOINT,endPOINT),frase, frecuencia, profundidad);
    EXPECT_EQ(3854,posMxCrr);
}



