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
