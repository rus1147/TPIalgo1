#include <iostream>
#include <fstream>
#include "auxiliar.h"
#include <vector>
#include "math.h"
#include "Funciones_TPI.h"

bool audioValido(audio a,int prof, int freq){
        return duraMasDe(1.0, a, freq) && freqValida(freq) && enRango(a, prof) && profValida(prof) && micFunciona(a, freq);
}

bool micFunciona(audio a,int freq){
    int i=0;
    while(i<a.size()){
        int j=i;
        while(j<a.size()){
            if(duraMasDe(1,subSeq(a,i,j),freq) && sonTodosCeros(subSeq(a,i,j))){
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}
bool profValida(int prof){
    return (prof==16 || prof==32);
}
bool freqValida(int freq){
    return freq>=4;
}
bool enRango(audio a, int prof){
    int i=-(pow(2,(prof-1)));
    int j=(pow(2,(prof-1)))-1;
    int k=0;
    while(k<a.size()){
        if(i<=a[k] && a[k]<=j){
            k++;
        }
        else{
            return false;
        }
    }
    return true;
}
bool conPrecision(tiempo t,int p){
    return ( (t*pow(10,p)) /pow(10,p) ==t);
}
bool sonTodosCeros(vector<int> s){
    int i=0;
    while(i<s.size()){
        if(s[i]!=0){
            return false;
        }
        i++;
    }
    return true;
}

bool duraMasDe(tiempo t, audio a, int freq){
    return duracion(a,freq)>t;
}

tiempo duracion(audio a, int freq){
    return enSegundos(a.size(), freq);
}
tiempo enSegundos(float n, float freq){
    return n/freq;
}

vector<int> subSeq(vector<int> s,int i, int j){
    vector<int> sSubSeq;
    int k=i;
    while(k<j){
        sSubSeq.push_back(s[k]);
        k++;
    }
    return sSubSeq;
}

bool intervaloEnRango(intervalo i, tiempo durTotal){
    return (0 <= get<0>(i) && get<0>(i)<= get<1>(i) && get<1>(i)<= durTotal);
}

bool intervalosEnRango(lista_intervalos intervalos,tiempo durTotal){
    int i=0;
    while(i<intervalos.size()){
        if(intervaloEnRango(intervalos[i],durTotal)){
            i++;
        }
        else{
            return false;
        }
    }
    return true;
}

bool enOrden(lista_intervalos intervalos){
    int i=0;
    while(i<intervalos.size()){
        int j=i+1;
        if(get<1>(intervalos[i])<get<0>(intervalos[j])){
            i++;
        }else{
            return false;
        }
    }
    return true;
}

bool todosConPrecision(lista_intervalos intervalos,int precision){
    int i=0;
    while(i<intervalos.size()){
        if(conPrecision(get<0>(intervalos[i]),precision) && conPrecision(get<1>(intervalos[i]),precision)){
            i++;
        }
        else{
            return false;
        }
    }
    return true;
}
bool intervalosValidos(lista_intervalos intervalos,tiempo durTotal){
    return intervalosEnRango(intervalos,durTotal) && enOrden(intervalos) && todosConPrecision(intervalos,2);
}

bool salaValida(sala m, int prof, int freq){
    if(esMatriz(m)){
        int a=0;
        while(a<m.size()){
            if(audioValido(m[a],prof,freq)){
                a++;
            }else{
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

bool esMatriz(sala m){
    int a=0;
    while(a<m.size()){
        if(m[a].size()==m[0].size()){
            a++;
        }else{
            return false;
        }
    }
    return true;
}

bool hayUnicoAcapador(sala m, int prof, int freq){
    if(m.size()>0){
        int p=0;
        while(p<m.size()){
            if(acapara(m,prof,freq,p)){
                p++;
            }else{
                return false;
            }
            return true;
        }
    }
    else{
        return false;
        }
    }


float intensidadMedia(audio s) {
    float sum = 0;

    for (int i = 0; i < s.size(); i++) {
        sum = sum + fabsf(s[i]);
    }

    return sum/s.size();
}

 bool acapara(sala m, int p, int prof, int freq) {
    int j = 0;
    while (j < m.size()) {
        if (intensidadMedia(m[p]) > intensidadMedia(m[j]) || (j == p)){
            j++;
        } else {
            return false;
        }
    }
     return true;
}

int indiceEnTiempo(tiempo t,int freq){
    int k=floor((freq*t));
    return abs(k);
}

bool audioArdillizado(audio a, audio a0){
    if(a.size()==a0.size()/2){
        int i=0;
        while(i<a.size()){
            if(a[i]==a0[2*i]){
                i++;
            }
            else{
                return false;
            }
        }
        return true;
    }
    return false;
}

bool salaArdillizada(sala m, sala m0){
    int a=0;
    while(a<m.size()){
        if(audioArdillizado(m[a],m0[a])){
            a++;
        }else{
            return false;
        }
    }
    return true;
}

bool todosCerosEnPosPares(audio a){
    int i=0;
    bool esCerospar=false;
    while(i<a.size()){
        if(i%2==0){
            esCerospar=a[i]==0;
        }else{
            return false;
        }
        i=i+2;
    }
    return esCerospar;
}

bool hayCerosEnPosPares(audio a,int freq){
    int i=0;
    bool hayceropospar=false;
    while(i<a.size()){
        int j=0;
        while(j<a.size()){
            if(duraMasDe(2,subSeq(a,i,j),freq) && todosCerosEnPosPares(subSeq(a,i,j))){
                hayceropospar=true;
            }
            j++;
        }
        i++;
    }
    return hayceropospar;
}

void ardillizaraudio(audio& a){
    int i=0;
    audio res{};
    while(i<(a.size()/2)){
        res.push_back(a[2*i]);
        i++;
    }
    a=res;
}

void ponerCerosEnPosPar(audio& a){
    int i=0;
    while(i<a.size()){
        if(i%2==0){
            a[i]=0;
        }
        i=i+2;
    }
}

audio audioSinCeros(audio a){
    int i=0;
    vector<int> res{};
    while(i<a.size()){
        if(a[i]!=0){
            res.push_back(a[i]);
        }
        i++;
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

bool esMaximaCorrelacion(audio a, int startPoint, audio frase){
    int i=0;
    bool esCorrelacion=false;
    while(i<(a.size()-frase.size()) && i!=startPoint){
            if( correlacion(subSeq(a,i,i+frase.size()),frase) < correlacion(subSeq(a,startPoint,startPoint+frase.size()),frase)){
                esCorrelacion=true;
            } else{
                return false;
            }
        i++;
    }
    return esCorrelacion;
    
}
int comienzoCorrelacion(audio a, audio frase){
    int i=0;
    int suma=0;
    while(i<(a.size()-frase.size())){
        if(esMaximaCorrelacion(a,i,frase)){
            suma=suma+i;
        }
        i++;
    }
    return suma;
}

vector<float> leerVectorAudio2(string nombreArchivo) {
    ifstream miArchivo;
    float val = 0;
    vector<float> vec{};
    int contador = 0;

    miArchivo.open(nombreArchivo.c_str(), ifstream::in);
    if (miArchivo.is_open()) {
        while (!miArchivo.eof()) {
            miArchivo >> val;
            vec.push_back(val);
            contador++;
        }
    } else {

        if (contador == 0) {
            cout << "Archivo vacio." << endl;
        } else {
            cout << "Error leyendo el archivo." << endl;
        }
    }

    miArchivo.close();
    return vec;
}

void negacionLogica (vector<bool> &mascara){
    for (int i = 0; i < mascara.size(); i++) {
        mascara[i] = !mascara[i];
    }
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

intervalo makeInterval(float intervalBeginning, float intervalEnding, int freq) {
    return make_tuple(intervalBeginning/freq, intervalEnding/freq);
}

bool isValidSilenceLength(int silenceBeginning, int silenceEnding, int freq) {
    return silenceEnding - silenceBeginning > 0.1*freq;
}

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

bool esSilencio(audio a,intervalo inter, int freq, int umbral){
    if(intervaloEnRango(inter,duracion(a,freq))){
        if((get<1>(inter)-get<0>(inter))>0.1 && conPrecisionEnMuestra(get<0>(inter),freq) &&
                conPrecisionEnMuestra(get<1>(inter),freq)){
            int k=indiceEnTiempo(get<0>(inter),freq);
            while(k<indiceEnTiempo(get<1>(inter),freq)){
                if(abs(a[k])<umbral){
                    if(indiceEnTiempo(get<0>(inter),freq)!=0){
                        if(a[indiceEnTiempo(get<0>(inter),freq)-1]<umbral){
                            return false;
                        }
                    } else{
                        return false;
                    }
                    if(indiceEnTiempo(get<1>(inter),freq)!=a.size()){
                        if(a[indiceEnTiempo(get<1>(inter),freq)-1]<umbral){
                            return false;
                        }
                    } else{
                        return false;
                    }
                } else{
                    return false;
                }
                k++;
            }
        } else{
            return false;
        }
        return true;
    } else{
        return false;
    }
}

bool conPrecisionEnMuestra(tiempo t, int freq){
    int k=freq*t;
    return t=(abs(k))/freq;
}

int cantSilencios(audio a, int freq,int umbral, int hasta){
    int i=0;
    int sum=0;
    while(i<=hasta){
        if(haySilencioQueLoContiene(a,i,freq,umbral)){
            sum=sum+1;
        }
        i++;
    }
    return sum;
}

bool haySilencioQueLoContiene(audio a,int i,int freq,int umbral){
    float in=0.0;
    float fn=0.0;
    bool haySilence= false;
    while(in<a.size()){
        fn=in;
        while(fn<a.size()){
            tuple<float,float> inter(in,fn);
            if(intervaloEnRango(inter,duracion(a,freq))){
                if(get<0>(inter)<=enSegundos(i,freq) && enSegundos(i,freq)<get<1>(inter) && esSilencio(a,inter,freq,umbral)){
                    return true;
                }
            }
            fn++;
        }
        in++;
    }
    return haySilence;
    
}

audio sacarSilencios(audio a, int freq, int prof, int umbral){
    audio res{};
    int i=0;
    while(i<a.size()){
        if(a[i]!=0){
            res.push_back(a[i]);
        }
        i++;
    }
    return res;
    
    
    /*float in=0.0;
    float fn=0.0;
    bool haySilence= false;
    while(in<a.size()){
            fn=in;
            while(fn<a.size() && in!=0){
                tuple<float,float> inter(in,fn);
                if(!esSilencio(a,inter,freq,umbral) && fn!=0){
                   int k=fn;
                    //estoy seguro que esto tiene repetidos, pero se tiene que corregir
                    
                        res.push_back(a[k]);
                        
                    }
                fn++;
            }
        in++;
    }*/
    
}
    
