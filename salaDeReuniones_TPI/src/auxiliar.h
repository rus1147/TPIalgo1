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
bool esMatriz(sala m);//
bool hayUnicoAcapador(sala m, int prof, int freq);
bool acapara(sala m, int prof, int freq, int p);
int intesidadMedia(audio a);
int indiceEnTiempo(tiempo t, audio a,int freq);


#endif //SALADEREUNION_AUXILIAR_H
