#ifndef SALADEREUNION_AUXILIAR_H
#define SALADEREUNION_AUXILIAR_H

#include <iostream>
#include <vector>
#include <fstream>
#include "definiciones.h"

using namespace std;

bool freqValida(int freq);
bool enRango(audio a, int prof);
bool profValida(int prof);
bool micFunciona(audio a,int freq);
bool sonTodosCeros(vector<int> s);
bool duraMasDe(tiempo t, audio a, int freq);
tiempo duracion(audio a,int freq);
tiempo enSegundos(float n, float freq);

float intensidadMedia(audio a);

audio ardillizarAudio(audio& a);

audio interpolarAudio(audio a);

bool isValidSilenceLength(int silenceBeginning, int silenceEnding, int freq);
intervalo makeInterval(float intervalBeginning, float intervalEnding, int freq);

lista_intervalos noSilencios(audio s, int prof, int freq, int umbral);
bool mergearYCheckearIntervalos(lista_intervalos& intervalos1, lista_intervalos& intervalos2);
bool ordenarUltimoElementoYCheckearColisiones(lista_intervalos& intervalos);

lista_intervalos intervalosDeHablaDesdeArchivo(string nombreArchivo);
vector<bool> enmascarar (tiempo duracion, lista_intervalos tiempos);
void negacionLogica (vector<bool> &mascara);
float f1score (vector<bool> m1, vector<bool> ms);
float precision (vector<bool> m1, vector<bool> ms);
float recall (vector<bool> m1, vector<bool> ms);
int cantVerdaderosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios);
int cantFalsosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios);
int cantFalsosNegativos (vector<bool> mascara1, vector<bool> mascaraSilencios);

int indiceEnTiempo(tiempo t,int freq);

vector<int> subSeq(vector<int> s,int i, int j);

#endif //SALADEREUNION_AUXILIAR_H
