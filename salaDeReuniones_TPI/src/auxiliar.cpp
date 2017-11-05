#include "auxiliar.h"
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
            break;
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
tiempo duracion(audio a,int freq){
    int j=a.size();
    return enSegundos(a.size(),freq);
}
tiempo enSegundos(int n,int freq){
    return 1.0f*n/freq;
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
/*bool esSilencio(audio a,intervalo inter, int freq, amplitud umbral){

}*/
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
bool acapara(sala m, int prof, int freq, int p){
    int x=0;
    bool acapar=false;
    if(x!=p){
        while(x<m.size()){
            if(intesidadMedia(m[x])<intesidadMedia(m[p])){
                acapar= true;
            }
            x++;
        }
    }
    return acapar;
}
int intesidadMedia(audio a){
    int i=0;
    int sum=0;
    while(i<a.size()){
        sum=sum+(abs(a[i])/a.size());
        i++;
    }
    return sum;
}
int indiceEnTiempo(tiempo t, audio a,int freq){
    int k=freq*t;
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

void negacionLogica (vector<bool> &mascara){
    int i = 0;
    while (i<mascara.size()){
        if (mascara[i]==true){
            mascara[i]=false;
        } else {
            mascara[i]=true;
        }
        i++;
    }
}

lista_intervalos crearTuplas (string nombreArchivo, int& frecuencia, int& profundidad, int& duracion){
    lista_intervalos v;
    int i = 0;
    vector<int> m = leerVectorAudio(nombreArchivo, frecuencia, profundidad, duracion);
    while(i<m.size()){
        tuple<int, int> tuple1 = make_tuple(m[i],m[i+1]);
        v.push_back(tuple1);
        i+2;
    }
}

vector<bool> enmascarar (float dur, lista_intervalos tiempos) {
    float i = 0;
    int j = 0;
    vector<bool> mascara = {};

    while (i < dur) {

        while (j < tiempos.size()) {

            if (i < get<0>(tiempos[j])) {

                mascara.push_back(false);
                i = i + 0, 01;

            } else {

                if (i >= get<0>(tiempos[j]) && i < get<1>(tiempos[j])) {

                    mascara.push_back(true);
                    i = i + 0, 01;

                } else {

                    j++;
                }
            }
        }

        mascara.push_back(false);
        i = i + 0,01;
    }
}


int cantVerdaderosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios){
    int i = 0;
    int cant = 0;
    while(i<mascara1.size()){
        if(mascara1[i]== true && mascaraSilencios[i]== true){
            cant++;
        }
        i++;
    }
    return cant;
}

int cantVerdaderosNegativos (vector<bool> mascara1, vector<bool> mascaraSilencios){
    int i = 0;
    int cant = 0;
    while(i<mascara1.size()){
        if(mascara1[i]== false && mascaraSilencios[i]== false){
            cant++;
        }
        i++;
    }
    return cant;
}

int cantFalsosPositivos (vector<bool> mascara1, vector<bool> mascaraSilencios){
    int i = 0;
    int cant = 0;
    while(i<mascara1.size()){
        if(mascara1[i]== false && mascaraSilencios[i]== true){
            cant++;
        }
        i++;
    }
    return cant;
}

int cantFalsosNegativos (vector<bool> mascara1, vector<bool> mascaraSilencios){
    int i = 0;
    int cant = 0;
    while(i<mascara1.size()){
        if(mascara1[i]== true && mascaraSilencios[i]== false){
            cant++;
        }
        i++;
    }
    return cant;
}

float precision (vector<bool> m1, vector<bool> ms){
    float p = cantVerdaderosPositivos(m1,ms) / (cantVerdaderosPositivos(m1,ms) + cantFalsosPositivos(m1,ms));
    return p;
}

float recall (vector<bool> m1, vector<bool> ms){
    float p = cantVerdaderosPositivos(m1,ms) / (cantVerdaderosPositivos(m1,ms) + cantFalsosNegativos(m1,ms));
    return p;
}

float f1score (vector<bool> m1, vector<bool> ms){
    float f1 = 2 * ((precision(m1,ms) * recall(m1,ms)) / (precision(m1,ms) + recall(m1,ms)));
    return f1;
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