#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"

using namespace std;

TEST(flashElPerezosoTEST, sample01) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,2,3,4,5,6},
            {5,7,8,9,2,1}
    };

    sala res = {
            {1,1,2,2,3,3,4,4,5,5,6},
            {5,6,7,7,8,8,9,5,2,1,1}
    };

    sala m_out = flashElPerezoso(m, prof, freq);

    ASSERT_EQ(m_out.size(), res.size());

    for (int i = 0; i < m_out.size(); i++) {

        ASSERT_EQ(m_out[i].size(), res[i].size());

        for(int j = 0; j < m_out[i].size(); j++) {
            EXPECT_EQ(m_out[i][j], res[i][j]);
        }
    }
}

TEST(flashElPerezosoTEST, sample02) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,1,2,2,3,3},
            {10,0,5,0,10,0},
            {1,3,5,7,9,11}
    };

    sala res = {
            {1,1,1,1,2,2,2,2,3,3,3},
            {10,5,0,2,5,2,0,5,10,5,0},
            {1,2,3,4,5,6,7,8,9,10,11}
    };

    sala m_out = flashElPerezoso(m, prof, freq);

    ASSERT_EQ(m_out.size(), res.size());

    for (int i = 0; i < m_out.size(); i++) {

        ASSERT_EQ(m_out[i].size(), res[i].size());

        for(int j = 0; j < m_out[i].size(); j++) {
            EXPECT_EQ(m_out[i][j], res[i][j]);
        }
    }
}