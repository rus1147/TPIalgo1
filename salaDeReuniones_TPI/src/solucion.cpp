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

/************************** EJERCICIO compararSilencios **************************/

/*float compararSilencios(audio vec, int freq, int prof, int locutor, int umbralSilencio){

}*/

/************************** EJERCICIO sacarPausas **************************/
audio sinSilencios(audio s, int freq, int prof, int umbral) {
    audio res = {};

    for (int i = 0; i < s.size(); i++) {
        if (abs(s[i]) >= umbral) {
            res.push_back(s[i]);
        }
    }

    return res;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio target, audio s, int freq, int prof){

    int index = -1;
    float maximaCorrelacion = 0;

    for (int i = 0; i <= s.size() - target.size(); i++) {

        float aux = correlacion(subSeq(s, i, i + target.size()), target);

        if (fabsf(aux) > fabsf(maximaCorrelacion)) {
            maximaCorrelacion = aux;
            index = i;
        }
    }

    return index;
}

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia (sala m, audio frase, int freq, int prof) {

    vector<int> apariciones = {};

    for (int i = 0; i < m.size(); i++) {
        apariciones.push_back(encontrarAparicion(frase, m[i], freq, prof));
    }

    int firstTime = m[0].size();

    for (int i = 0; i < m.size(); i++) {
        if (apariciones[i] < firstTime) {
            firstTime = apariciones[i];
        }
    }

    int locutor;
    float maximaIntensidadMedia = 0;

    for (int i = 0; i < m.size(); i++) {
        if (apariciones[i] == firstTime) {
            float im = intensidadMedia(subSeq(m[i], firstTime, firstTime + frase.size()));

            if (im > maximaIntensidadMedia) {
                maximaIntensidadMedia = im;
                locutor = i;
            }
        }
    }

    vector<float> distancias = {};

    for (int i = 0; i < m.size(); i++) {
        if (i != locutor) {
            distancias.push_back((apariciones[i] - firstTime)*VELOCIDAD_SONIDO/freq);
        }
    }

    return make_tuple(locutor, distancias);
}
