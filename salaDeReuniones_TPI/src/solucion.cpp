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
    lista_intervalos res={};
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
