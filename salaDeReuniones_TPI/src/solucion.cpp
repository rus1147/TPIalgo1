// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include "math.h"
#include "auxiliar.h"
#include "auxiliar.cpp"

/************************** EJERCICIO grabacionValida **************************/
bool grabacionValida(audio s, int prof, int freq){
    return audioValido(s,prof,freq);
}


/************************** EJERCICIO elAcaparador **************************/
int elAcaparador(sala m, int freq, int prof){
    int p=0;
    int personaRes=-1;
    while(p<m.size()){
        if(acapara(m,prof,freq,p)){
           personaRes=p;
        }
        p++;
        }
    return personaRes;
}

/************************** EJERCICIO ardillizar **************************/
sala ardillizar(sala m, int prof, int freq){
    int i=0;
    sala resultado{};
    while(i<m.size()){
        ardillizaraudio(m[i]);
        resultado.push_back(m[i]);
        i++;
    }
    return resultado;
}

/************************** EJERCICIO flashElPerezoso **************************/
sala flashElPerezoso(sala m, int prof, int freq){
    sala res(m.size());

    for (int i = 0; i < m.size(); i++) {
        res[i] = interpolarAudio(m[i]);
    }

    return res;
}

/************************** EJERCICIO silencios **************************/

intervalo makeInterval(float intervalBeginning, float intervalEnding, int freq) {
    return make_tuple(intervalBeginning/freq, intervalEnding/freq);
}

bool isValidSilenceEnding(int silenceBeginning, int silenceEnding, int freq) {
    return silenceEnding + 1 - silenceBeginning > 0.1*freq;
}

lista_intervalos silencios(audio s, int prof, int freq, int umbral){
    lista_intervalos res = {};

    bool silenceBeginningFoundFlag = false;
    int silenceBeginning = 0;

    for (int i = 0; i < s.size(); i++) {

        if (s[i] < umbral) {

            if (!silenceBeginningFoundFlag) {
                silenceBeginningFoundFlag = true;
                silenceBeginning = i;
            } else if (i == s.size() - 1 && isValidSilenceEnding(silenceBeginning, i + 1, freq)) {
                res.push_back(makeInterval(silenceBeginning, i, freq));
            }

        } else if (silenceBeginningFoundFlag) {
            silenceBeginningFoundFlag = false;

            if (isValidSilenceEnding(silenceBeginning, i, freq)) {
                res.push_back(makeInterval(silenceBeginning, i, freq));
            }
        }
    }

    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool hayQuilombo(sala m, int prof, int freq, int umbral){
    return false;
}

/************************** EJERCICIO negacionLogica **************************/

vector<bool> negacionLogica(vector<bool> mascara){
    negacionLogicaAux(mascara);
    return mascara;
}

/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result={};
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y){

    return comienzoCorrelacion(x,y);
}

/************************** EJERCICIO medirLaDistancia **************************/
/*locutor medirLaDistancia(sala m, audio frase, int freq, int prof){
    locutor out;
    return out;
}*/
