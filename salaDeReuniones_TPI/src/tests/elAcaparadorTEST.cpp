#include "../ejercicios.h"
#include "gtest/gtest.h"


TEST(elAcaparadorTEST, prueba){
    sala m = {
            {1,2,3,4,5,6},
            {0,0,8,6,7,8},
            {10,0,0,9,4,5},
            {5,7,8,9,2,1},
    };
    int freq = 4;
    int prof = 16;
    EXPECT_EQ(3, elAcaparador(m, freq, prof));
}

TEST(elAcaparadorTEST, prueba2){
    sala m = {
            {5,7,8,9,2,1},
            {10,0,0,9,4,5},
            {0,0,8,6,7,8},
            {1,2,3,4,5,6},
    };
    int freq = 4;
    int prof = 16;
    EXPECT_EQ(0, elAcaparador(m, freq, prof));
}

TEST(elAcaparadorTEST, prueba3){
    sala m = {
            {1,1,1,1,1,1},
            {-2,-1,-1,-1,-1,-1}
    };
    int freq = 4;
    int prof = 16;
    EXPECT_EQ(1, elAcaparador(m, freq, prof));
}

