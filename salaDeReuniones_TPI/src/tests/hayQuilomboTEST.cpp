#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(hayQuilomboTest, unAudio){
    int prof = 16;
    int freq = 1;

    audio a1 = {0, 1, 1, 1, 0, 0, 0, 0};
    audio a2 = {0, 0, 0, 1, 0, 0, 0, 0};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 1), true);

    sala s2 = {};
    s2.push_back(a2);
    s2.push_back(a1);

    EXPECT_EQ(hayQuilombo(s2, prof, freq, 1), true);
}