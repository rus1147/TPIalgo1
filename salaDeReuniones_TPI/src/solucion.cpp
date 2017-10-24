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
    sala res=m;
    int i=0;
    while(i<res.size()){
        ponerCerosEnPosPar(res[i]);
        audioSinCeros(res[i]);
        //revisar esta funcion
        // ardillizaraudio(res[i]);
        
        i++;
    }
    return res;
}

/************************** EJERCICIO flashElPerezoso **************************/
sala flashElPerezoso(sala m, int prof, int freq){
    sala res={};
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

/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result={};
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y){
    return -1;
}

/************************** EJERCICIO medirLaDistancia **************************/
/*locutor medirLaDistancia(sala m, audio frase, int freq, int prof){
    locutor out;
    return out;
}*/
