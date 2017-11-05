#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "../auxiliar.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(sinSilenciosTEST, audioSinSilencios1){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 1, 1, 1, 0, 0, 0, 0};
    audio a2 = {1, 1, 1};
    
    
    EXPECT_EQ(sinSilencios(a1, freq, prof, umbral), a2);
}
TEST(sinSilenciosTEST, audioSinSilencios2){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 1, 1, 1, 0, 0, 1, 1};
    audio a2 = {1, 1, 1,1,1};
    
    
    EXPECT_EQ(sinSilencios(a1, freq, prof, umbral), a2);
}
TEST(sinSilenciosTEST, audioSinSilencios3){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {1, 0, 0, 0, 0, 0,1};
    audio a2 = {1, 1};
    
    
    EXPECT_EQ(sinSilencios(a1, freq, prof, umbral), a2);
}
TEST(sinSilenciosTEST, audioSinSilencios4){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 0, 0, 0, 0, 0,0};
    audio a2 = {};
    
    
    EXPECT_EQ(sinSilencios(a1, freq, prof, umbral), a2);
}

TEST(sinSilenciosTEST, longitudcorrecta){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 1, 1, 1, 0, 0, 0, 0};
    audio a2 = {1, 1, 1};
    
    EXPECT_EQ(a2.size() != (a1.size()-cantSilencios(a1,freq,umbral,a1.size()-1)),true);
}
TEST(sinSilenciosTEST, esValidoAlSacarSilencios){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 1, 1, 1, 0, 0, 0, 0};
    audio a2 = {1, 1, 1};
    bool result= (enSegundos((a1.size()-cantSilencios(a1,freq,umbral,a1.size())),freq)>1.0);
    EXPECT_EQ( result,true);
}
TEST(sinSilenciosTEST, noHaySilencioQueLoContiene){
    int prof = 16;
    int freq = 1;
    int umbral=7500;
    audio a1 = {0, 1, 1, 1, 0, 0, 0, 0};
    audio a2 = {1, 1, 1};
    bool result= haySilencioQueLoContiene(a2,prof,freq,umbral);
    EXPECT_EQ( result, false);
}
