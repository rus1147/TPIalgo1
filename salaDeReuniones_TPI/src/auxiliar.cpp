#include "auxiliar.h"
#include "math.h"
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