#include <iostream>
#include <fstream>
#include "auxiliar.h"
#include <vector>
#include "math.h"
#include "Funciones_TPI.h"

bool freqValida(int freq){
    return freq >= 4;
}

bool enRango(audio a, int prof){
    int limiteInferior = -1*pow(2, (prof-1));

    int limiteSuperior = pow(2, (prof-1)) - 1;

    for (int k = 0; k < a.size(); k++) {
        if (a[k] < limiteInferior || a[k] > limiteSuperior) {
            return false;
        }
    }

    return true;
}

bool profValida(int prof) {
    return prof == 16 || prof == 32;
}

bool micFunciona(audio a, int freq){

    for (int i = 0; i + freq + 1 <= a.size(); i++) {
        if (sonTodosCeros(subSeq(a, i, i + freq + 1))) {
            return false;
        }
    }

    return true;
}

bool sonTodosCeros(vector<int> s){
    int i = 0;
    while (i < s.size()) {
        if (s[i] != 0) {
            return false;
        }
        i++;
    }
    return true;
}

bool duraMasDe(tiempo t, audio a, int freq){
    return duracion(a, freq) > t;
}

tiempo duracion(audio a, int freq){
    return enSegundos(a.size(), freq);
}

tiempo enSegundos(float n, float freq){
    return n / freq;
}

float intensidadMedia(audio s) {
    float sum = 0;

    for (int i = 0; i < s.size(); i++) {
        sum = sum + fabsf(s[i]);
    }

    return sum/s.size();
}

audio ardillizarAudio(audio& a){
    audio res = {};

    int limite = (a.size() + 1)/2;

    for (int i = 0; i < limite; i++) {
        res.push_back(a[2*i]);
    }

    return res;
}

audio interpolarAudio(audio a) {
    audio res(2*a.size() - 1);

    for (int i = 0; i < res.size(); i++) {
        if (i % 2 == 0) {
            res[i] = a[i/2];
        } else {
            int index = (i-1)/2;
            res[i] = (a[index] + a[index + 1])/2;
        }
    }

    return res;
}

bool isValidSilenceLength(int silenceBeginning, int silenceEnding, int freq) {
    return silenceEnding - silenceBeginning > 0.1*freq;
}

intervalo makeInterval(float intervalBeginning, float intervalEnding, int freq) {
    return make_tuple(intervalBeginning/freq, intervalEnding/freq);
}

lista_intervalos noSilencios(audio s, int prof, int freq, int umbral){

    lista_intervalos res = {};

    lista_intervalos silenceIntervals = silencios(s, prof, freq, umbral);

    if (silenceIntervals.size() < 1) {
        res.push_back(make_tuple(0, duracion(s, freq)));
        return res;
    }

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

bool ordenarUltimoElementoYCheckearColisiones(lista_intervalos& intervalos) {

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

bool mergearYCheckearIntervalos(lista_intervalos& intervalos1, lista_intervalos& intervalos2){

    for (int i = 0; i < intervalos2.size(); i++) {
        intervalos1.push_back(intervalos2[i]);

        if (!ordenarUltimoElementoYCheckearColisiones(intervalos1)){
            return false;
        }
    }

    return true;
}

lista_intervalos intervalosDeHablaDesdeArchivo(string nombreArchivo) {
    lista_intervalos intervalos = {};

    ifstream archivo;
    archivo.open(nombreArchivo.c_str(), ifstream::in);

    if (archivo.is_open()) {

        float intervaloInicio = -2;
        float intervaloFin = -2;

        while (!archivo.eof()) {

            archivo >> intervaloInicio;
            archivo >> intervaloFin;

            if (intervaloInicio >= 0 && intervaloFin >= 0) {
                intervalos.push_back(make_tuple(intervaloInicio, intervaloFin));
            }

            intervaloInicio = -1;
            intervaloFin = -1;
        }

        if (intervaloInicio == -2) {
            cout << "Archivo vacio: " << nombreArchivo << endl;
        }

    } else {
        cout << "Error leyendo el archivo: " << nombreArchivo << endl;
    }

    archivo.close();
    return intervalos;
}

vector<bool> enmascarar (tiempo duracion, lista_intervalos tiempos) {

    tiempo maskLength = 0.01;
    tiempo i = 0;

    int j = 0;

    vector<bool> mascara = {};

    while (i < duracion) {

        if (j >= tiempos.size() || i < get<0>(tiempos[j])) {

            mascara.push_back(false);
            i = i + maskLength;

        } else if (i < get<1>(tiempos[j])) {

            mascara.push_back(true);
            i = i + maskLength;

        } else {
            j++;
        }
    }

    return mascara;
}

void negacionLogica (vector<bool> &mascara){
    for (int i = 0; i < mascara.size(); i++) {
        mascara[i] = !mascara[i];
    }
}

int cantVerdaderosPositivos (vector<bool> esperado, vector<bool> generado) {
    int cant = 0;

    for (int i = 0; i < generado.size(); i++) {
        if (generado[i] == true && esperado[i] == true) {
            cant++;
        }
    }

    return cant;
}

int cantFalsosPositivos (vector<bool> esperado, vector<bool> generado) {
    int cant = 0;

    for (int i = 0; i < generado.size(); i++) {
        if (generado[i] == true && esperado[i] == false) {
            cant++;
        }
    }

    return cant;
}

int cantFalsosNegativos (vector<bool> esperado, vector<bool> generado) {
    int cant = 0;

    for (int i = 0; i < generado.size(); i++) {
        if (generado[i] == false && esperado[i] == true) {
            cant++;
        }
    }

    return cant;
}

float precision (vector<bool> esperado, vector<bool> generado) {
    float vp = cantVerdaderosPositivos(esperado, generado);
    float fp = cantFalsosPositivos(esperado, generado);
    return vp / (vp + fp);
}

float recall (vector<bool> esperado, vector<bool> generado) {
    float vp = cantVerdaderosPositivos(esperado, generado);
    float fn = cantFalsosNegativos(esperado, generado);
    return vp / (vp + fn);
}

float f1score (vector<bool> esperado, vector<bool> generado){
    float prec = precision(esperado, generado);
    float reca = recall(esperado, generado);

    return 2*(prec*reca)/(prec + reca);
}

int indiceEnTiempo(tiempo t,int freq){
    int k=floor((freq*t));
    return abs(k);
}

audio subSeq(audio s, int i, int j){
    audio sSubSeq = {};
    int k = i;

    while(k < j) {
        sSubSeq.push_back(s[k]);
        k++;
    }

    return sSubSeq;
}
