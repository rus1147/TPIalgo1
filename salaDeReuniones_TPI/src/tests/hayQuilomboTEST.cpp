#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(hayQuilomboTest, unAudio){
    int prof = 16;
    int freq = 4;

    audio a1 = {1, 6, 6, 6, 1, 1, 1, 1};
    audio a2 = {1, 1, 1, 6, 1, 1, 1, 1};
    audio a3 = {1, 1, 1, 1, 6, 6, 1, 1};
    audio a4 = {1, 1, 1, 1, 1, 6, 1, 1};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 2), true);

    sala s2 = {};
    s2.push_back(a2);
    s2.push_back(a1);

    EXPECT_EQ(hayQuilombo(s2, prof, freq, 2), true);

    sala s3 = {};
    s3.push_back(a1);
    s3.push_back(a3);
    s3.push_back(a4);

    EXPECT_EQ(hayQuilombo(s3, prof, freq, 2), true);
}

TEST(hayQuilomboTest, hayQuilombo){
    int prof = 16;
    int freq = 4;

    audio a1 = {5, 5, 5, 5, 1, 1, 1, 1};
    audio a2 = {1, 1, 1, 1, 5, 1, 1, 1};
    audio a3 = {1, 1, 1, 1, 1, 5, 5, 1};
    audio a4 = {1, 1, 1, 1, 1, 5, 5, 5};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);
    s1.push_back(a3);
    s1.push_back(a4);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 4), true);
}

TEST(hayQuilomboTest, unSoloLocutor){
    int prof = 16;
    int freq = 4;

    audio a1 = {5, 5, 5, 5, 1, 1, 1, 1};

    sala s1 = {};
    s1.push_back(a1);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 2), false);
}

TEST(hayQuilomboTest, noHayQuilombo){
    int prof = 16;
    int freq = 4;

    audio a1 = {2, 2, 2, 2, 1, 1, 1, 1};
    audio a2 = {1, 1, 1, 1, 3, 1, 1, 1};
    audio a3 = {1, 1, 1, 1, 1, 4, 1, 1};
    audio a4 = {1, 1, 1, 1, 1, 1, 5, 5};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);
    s1.push_back(a3);
    s1.push_back(a4);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 2), false);
}

TEST(hayQuilomboTest, noHayQuilombo2){
    int prof = 16;
    int freq = 4;

    audio a1 = {1, 1, 1, 1, 1, 1, 1, 1};
    audio a2 = {2, 2, 2, 2, 2, 2, 2, 2};

    sala s1 = {};
    s1.push_back(a1);
    s1.push_back(a2);

    EXPECT_EQ(hayQuilombo(s1, prof, freq, 2), false);
}