#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(sinSilenciosTEST, audio1){
    int prof = 16;
    int freq = 20;
    int umbral = 2;
    audio a = {5,15,0,3,2,10,25,1,0,1,0,4,0,16,17,20,0,0,1,0};
    audio res = {5,15,0,3,2,10,25,4,0,16,17,20};
    EXPECT_EQ(res,sinSilencios(a,freq,prof,umbral));
}

TEST(sinSilenciosTEST, audio2){
    int prof = 16;
    int freq = 5;
    int umbral = 1000;
    audio a = {1500,1505,32,2598,5415,1085,2556,1009,3000,1059,1087};
    audio res = {1500,1505,2598,5415,1085,2556,1009,3000,1059,1087};
    EXPECT_EQ(res,sinSilencios(a,freq,prof,umbral));
}

TEST(sinSilenciosTEST, audioSinSilencios){
    int prof = 32;
    int freq = 15;
    int umbral = 20;
    audio a = {30,35,39,40,58,19};
    audio res = a;
    EXPECT_EQ(res, sinSilencios(a,freq,prof,umbral));
}




