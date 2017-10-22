# TPIalgo1


## checklist

- [X] bool grabacionValida(audio s, int prof, int freq)
- [] int elAcaparador(sala m, int freq, int prof)
- [] sala ardillizar(sala m, int prof, int freq)
- [] sala flashElPerezoso(sala m, int prof, int freq)
- [] lista_intervalos silencios(audio s, int prof, int freq, int umbral)
- [] bool hayQuilombo(sala m, int prof, int freq, int umbral)
- [] audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral)
- [] encontrarAparicion(audio x, audio y)
- [] medirLaDistancia(sala m, audio frase, int freq, int prof)


## Auxiliares hechos

- bool profValida(int prof)
- bool freqValida(int freq)
- bool conPrecision(tiempo t,int p)
- bool enRango(audio a, int prof)
- bool sonTodosCeros(vector<int> s)
- tiempo enSegundos(int n,int freq)
- tiempo duracion(audio a,int freq)
- bool duraMasDe(tiempo t, audio a, int freq);
- vector<int> subSeq(vector<int> s,int i, int j);
- bool micFunciona(audio a,int freq);
- bool audioValido(audio a,int prof, int freq);
- bool intervaloEnRango(intervalo i);
- bool intervalosEnRango(lista_intervalos intervalos,tiempo durTotal);
- bool enOrden(lista_intervalos intervalos);
- bool todosConPrecision(lista_intervalos intervalos,int precision);
- bool intervalosValidos(lista_intervalos intervalos,tiempo durTotal);
- bool salaValida(sala m, int prof, int freq);
- bool esMatriz(sala m);