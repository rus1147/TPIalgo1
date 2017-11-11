// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include "math.h"
#include "auxiliar.h"
#include "auxiliar.cpp"

/************************** EJERCICIO grabacionValida #1 **************************/
bool grabacionValida(audio s, int prof, int freq){
    return audioValido(s,prof,freq);
}
/************************** EJERCICIO elAcaparador #2**************************/
int elAcaparador(sala m, int freq, int prof) {
    int p = 0;
    int personaRes;
    while (p < m.size()) {
        if (acapara(m, p, prof, freq)) {
            personaRes = p;
            return personaRes;
        } else {
            p++;
        }
    }
}
/************************** EJERCICIO ardillizar #3**************************/
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
/************************** EJERCICIO flashElPerezoso #4**************************/
sala flashElPerezoso(sala m, int prof, int freq){
    sala res(m.size());

    for (int i = 0; i < m.size(); i++) {
        res[i] = interpolarAudio(m[i]);
    }

    return res;
}
/************************** EJERCICIO silencios #5**************************/
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
/************************** EJERCICIO hayQuilombo #6**************************/
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
/************************** EJERCICIO compararSilencios #7**************************/
float compararSilencios(audio a, int freq, int prof, int locutor, int umbralSilencio) {

    string nombreArchivo = "datos/habla_spkr" + to_string(locutor) + ".txt";

    lista_intervalos tiempos = intervalosDeHablaDesdeArchivo(nombreArchivo);

    tiempo dur = duracion(a, freq);

    vector<bool> mascaraDeArchivo = enmascarar(dur, tiempos);

    //quiero que la máscara devuelva true si hay silencio así que uso la negación lógica
    negacionLogica(mascaraDeArchivo);

    lista_intervalos silenciosMedianteAlgoritmo = silencios(a, prof, freq, umbralSilencio);

    vector<bool> mascaraDeAlgoritmo = enmascarar(dur, silenciosMedianteAlgoritmo);

    return f1score(mascaraDeArchivo, mascaraDeAlgoritmo);
}

/************************** EJERCICIO resultadoFinal #8**************************/
float resultadoFinal(sala m, int freq, int prof, int umbralSilencio){
    float sumaf1 = 0;

    for (int i = 0; i < m.size(); i++){
        sumaf1 += compararSilencios(m[i], freq, prof, i, umbralSilencio);
    }

    float cantPersonas = m.size();

    return sumaf1 / cantPersonas;
}

/************************** EJERCICIO sacarPausas #9**************************/
audio sinSilencios(audio a, int freq, int prof, int umbral) {
    audio res{};
    lista_intervalos s = silencios(a, prof, freq, umbral);
    int i = 0;
    int j = 0;
    while (j < s.size()) {
        if (i < indiceEnTiempo(get<0>(s[j]), freq)) {
            res.push_back(a[i]);
            i++;
        } else {
            if ((i >= indiceEnTiempo(get<0>(s[j]), freq)) && (i < indiceEnTiempo(get<1>(s[j]), freq))) {
                i++;
            } else {
                j++;
            }
        }
    }
    while (i < a.size()) {
        res.push_back(a[i]);
        i++;
    }
    return res;
}

/************************** EJERCICIO encontrarAparicion #10**************************/
int encontrarAparicion(audio s,audio target, int freq, int prof){
    int index = -1;
    float maximaCorrelacion = 0;
    int longitudTarget=target.size();
    int longitudAudio=s.size();
    for (int i = 0; i <= s.size() - target.size(); i++) {

        float aux = correlacion(subSeq(s, i, (int) (i + target.size())), target);

        if (fabsf(aux) > fabsf(maximaCorrelacion)) {
            maximaCorrelacion = aux;
            index = i;
        }
    }

    return index;
}
/************************** EJERCICIO medirLaDistancia #11**************************/
tuple<int,lista_distancias> medirLaDistancia(sala m, audio frase, int freq, int prof){

    vector<int> apariciones = {};

    for (int i = 0; i < m.size(); i++) {
        apariciones.push_back(encontrarAparicion( m[i],frase, freq, prof));
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
