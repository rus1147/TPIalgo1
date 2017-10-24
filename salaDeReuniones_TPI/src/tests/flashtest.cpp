#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(flastest, prueba) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,2,3,4,5,6},
            {5,7,8,9,2,1}
    };
    sala res = {
            {1,3,5},
            {5,8,2}
    };

    sala m_out = flashElPerezoso(m,prof,freq);

    for(int i=0;i<m.size();i++){
        for(int j=0;j<res[i].size();j++) {
            ASSERT_EQ(res[i][j],m_out[i][j]);
        }
    }
}


