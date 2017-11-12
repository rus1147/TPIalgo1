#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(grabacionValidaTEST, unaValida) {
    int freq = 4;
    int prof = 16;
    audio a = {1,2,3,4,5,6};

    EXPECT_EQ(true,grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, otraValida) {
    int freq = 12;
    int prof = 32;
    audio a = {1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6};
    EXPECT_EQ(true,grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, frecuenciaInvalida) {
    int freq = 1;
    int prof = 16;
    audio a = {1,2,3,4,5,6};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, fueraDeRangoInferiormente) {
    int freq = 4;
    int prof = 16;

    audio a = {1,-32769,3,4,5,6};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, fueraDeRangoSuperiormente) {
    int freq = 4;
    int prof = 16;

    audio a = {1,32768,3,4,5,6};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, profundidadInvalida) {
    int freq = 4;
    int prof = 33;

    audio a = {1,256,3,4,5,6};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, micNoFunciona1) {
    int freq = 4;
    int prof = 32;

    audio a = {0,0,0,0,0};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, micNoFunciona2) {
    int freq = 4;
    int prof = 32;

    audio a = {-1,0,0,0,0,0};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, micNoFunciona3) {
    int freq = 4;
    int prof = 32;

    audio a = {0,0,0,0,0,-1};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, micNoFunciona4) {
    int freq = 4;
    int prof = 32;

    audio a = {1,0,0,0,0,0,-1};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}


TEST(grabacionValidaTEST, duracionMenor1seg) {
    int freq = 4;
    int prof = 32;

    audio a = {1,1,1};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}

TEST(grabacionValidaTEST, duracion1seg) {
    int freq = 4;
    int prof = 32;

    audio a = {1,1,1,1};

    EXPECT_EQ(false, grabacionValida(a, prof, freq));
}
