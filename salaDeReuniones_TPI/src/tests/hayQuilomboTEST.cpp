#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(hayQuilomboTest, unAudio){
    int prof = 16;
    int freq = 4;

    audio a1 = {0, 2, 2, 2, 0, 0, 0, 0};
    audio a2 = {0, 0, 0, 1, 0, 0, 0, 0};
    audio a3 = {0, 0, 0, 0, 2, 2, 0, 0};
    audio a4 = {0, 0, 0, 1, 0, 2, 0, 0};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 1), true);

    sala s2 = {};
    s2.push_back(a2);
    s2.push_back(a1);

    EXPECT_EQ(hayQuilombo(s2, prof, freq, 1), true);

    sala s3 = {};
    s3.push_back(a1);
    s3.push_back(a3);
    s3.push_back(a4);

    EXPECT_EQ(hayQuilombo(s3, prof, freq, 2), true);

    sala s4 = {};
    s3.push_back(a1);
    s3.push_back(a3);

    EXPECT_EQ(hayQuilombo(s4, prof, freq, 1), false);
}
