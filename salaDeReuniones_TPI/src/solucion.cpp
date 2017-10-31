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

bool isValidSilenceLength(int silenceBeginning, int silenceEnding, int freq) {
    return silenceEnding - silenceBeginning > 0.1*freq;
}

lista_intervalos silencios(audio s, int prof, int freq, int umbral){
    lista_intervalos res = {};

    bool silenceBeginningFoundFlag = false;
    int silenceBeginning = 0;

    for (int i = 0; i < s.size(); i++) {

        if (abs(s[i]) < umbral) {

            if (!silenceBeginningFoundFlag) {
                silenceBeginningFoundFlag = true;
                silenceBeginning = i;
            } else if (i == s.size() - 1 && isValidSilenceLength(silenceBeginning, i + 1, freq)) {
                res.push_back(makeInterval(silenceBeginning, i + 1, freq));
            }

        } else if (silenceBeginningFoundFlag) {
            silenceBeginningFoundFlag = false;

            if (isValidSilenceLength(silenceBeginning, i, freq)) {
                res.push_back(makeInterval(silenceBeginning, i, freq));
            }
        }
    }

    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool sortLastElement(lista_intervalos& intervalos) {

    if (intervalos.size() < 2) {
        return true;
    }

    int elementPosition = 0;

    for (int i = intervalos.size() - 1; i > 0; i--) {

        intervalo intervalo1 = intervalos[i-1];
        intervalo intervalo2 = intervalos[i];

        if (get<0>(intervalo1) < get<0>(intervalo2) ) {
            elementPosition = i;
            break;
        } else if (get<0>(intervalo1) == get<0>(intervalo2) ) {
            return false;
        } else {
            intervalos[i-1] = intervalo2;
            intervalos[i] = intervalo1;
        }
    }

    if (elementPosition + 1 < intervalos.size()) {
        return get<1>(intervalos[elementPosition]) <= get<0>(intervalos[elementPosition+1]);
    } else {
        return get<0>(intervalos[elementPosition]) >= get<1>(intervalos[elementPosition-1]);
    }
}

bool mergeAndValidate(lista_intervalos& intervalos1, lista_intervalos& intervalos2){

    for (int i = 0; i < intervalos2.size(); i++) {
        intervalos1.push_back(intervalos2[i]);

        if (!sortLastElement(intervalos1)){
            return false;
        }
    }

    return true;
}

lista_intervalos noSilencios(audio s, int prof, int freq, int umbral){
    lista_intervalos silenceIntervals = silencios(s, prof, freq, umbral);

    if (silenceIntervals.size() < 1) {
        return {};
    }

    lista_intervalos res = {};

    tiempo beginningTime = get<0>(silenceIntervals[0]);
    if (beginningTime > 0) {
        res.push_back(make_tuple(0, beginningTime));
    }

    for (int i = 0; i + 1 < silenceIntervals.size(); i++) {
        tiempo beginningTime = get<1>(silenceIntervals[i]);
        tiempo endingTime = get<0>(silenceIntervals[i+1]);

        res.push_back(make_tuple(beginningTime, endingTime));
    }

    tiempo endingTime = get<1>(silenceIntervals[silenceIntervals.size()-1]);
    if (endingTime < s.size() / freq) {
        res.push_back(make_tuple(endingTime, s.size() / freq));
    }

    return res;
}

bool hayQuilombo(sala m, int prof, int freq, int umbral){

    if (m.size() < 2) {
        return false;
    }

    lista_intervalos itervalosAcum = noSilencios(m[0], prof, freq, umbral);

    for (int i = 1; i < m.size(); i++) {
        lista_intervalos intervalos = noSilencios(m[i], prof, freq, umbral);

        if (!mergeAndValidate(itervalosAcum, intervalos)) {
            return true;
        }
    }

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
