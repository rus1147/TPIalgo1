#ifndef SALADEREUNION_AUXILIAR_H
#define SALADEREUNION_AUXILIAR_H

#include <iostream>
#include <vector>
#include <fstream>
#include "definiciones.h"

using namespace std;
bool profValida(int prof);
bool freqValida(int freq);
bool conPrecision(tiempo t,int p);
bool enRango(audio a, int prof);
bool sonTodosCeros(vector<int> s);
tiempo enSegundos(int n,int freq);
tiempo duracion(audio a,int freq);
bool duraMasDe(tiempo t, audio a, int freq);
vector<int> subSeq(vector<int> s,int i, int j);
bool micFunciona(audio a,int freq);
bool audioValido(audio a,int prof, int freq);
bool intervaloEnRango(intervalo i);
bool intervalosEnRango(lista_intervalos intervalos,tiempo durTotal);
bool enOrden(lista_intervalos intervalos);
bool todosConPrecision(lista_intervalos intervalos,int precision);
bool intervalosValidos(lista_intervalos intervalos,tiempo durTotal);
bool salaValida(sala m, int prof, int freq);
bool esMatriz(sala m);
bool hayUnicoAcapador(sala m, int prof, int freq);
bool acapara(sala m, int prof, int freq, int p);
int intesidadMedia(audio a);
int indiceEnTiempo(tiempo t, audio a,int freq);//
bool audioArdillizado(audio a, audio a0);
bool salaArdillizada(sala m, sala m0);
bool todosCerosEnPosPares(audio a);
bool hayCerosEnPosPares(audio a,int freq);
void ardillizaraudio(audio& a);
void ponerCerosEnPosPar(audio& a);
audio audioSinCeros(audio a);
void audioInterpolado(audio a);
bool esMaximaCorrelacion(audio a, int startPoint, audio frase);
int comienzoCorrelacion(audio a, audio frase);
void negacionLogica (vector<bool> &mascara);
lista_intervalos crearTuplas (string nombreArchivo, int& frecuencia, int& profundidad, int& duracion);
int cantVerdaderosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios);
int cantVerdaderosNegativos (vector<bool> mascara1, vector<bool> mascaraSilencios);
int cantFalsosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios);
int cantFalsosNegativos (vector<bool> mascara1, vector<bool> mascaraSilencios);
float precision (vector<bool> m1, vector<bool> ms);
float recall (vector<bool> m1, vector<bool> ms);
float f1score (vector<bool> m1, vector<bool> ms);

#endif //SALADEREUNION_AUXILIAR_H
