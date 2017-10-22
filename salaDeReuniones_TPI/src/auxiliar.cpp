#include "auxiliar.h"
#include "math.h"
bool profValida(int prof){
    return (prof==16 || prof=32);
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
tiempo enSegundos(int n,int freq){
    return n/freq;
}
tiempo duracion(audio a,int freq){
    enSegundos(a.size(),freq);
}
bool duraMasDe(tiempo t, audio a, int freq){
    return duracion(a,freq)>t;
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
vector<int> subSeq(vector<int> s,int i, int j){
    vector<int> sSubSeq;
    int k=i;
    while(k<j){
        sSubSeq.push_back(s[k]);
        k++;
    }
    return sSubSeq;
}
bool audioValido(audio a,int prof, int freq){
    return freqValida(freq) && enRango(a,prof) && profValida(prof) && micFunciona(a,freq) && duraMasDe(1.0,a,freq);
}
bool intervaloEnRango(intervalo i){
    return 0 <= i.first() <= i.second() <= i.size();
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
        if(intervalos[i].second<intervalos[j].second){
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
        if(conPrecision(intervalos[i].first,precision) && conPrecision(intervalos[i].second,precision)){
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
