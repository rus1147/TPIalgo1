# TPIalgo1


## checklist

- [X] bool grabacionValida(audio s, int prof, int freq)
- [X] int elAcaparador(sala m, int freq, int prof)
- [X] sala ardillizar(sala m, int prof, int freq)
- [x] sala flashElPerezoso(sala m, int prof, int freq)
- [x] lista_intervalos silencios(audio s, int prof, int freq, int umbral)
- [x] bool hayQuilombo(sala m, int prof, int freq, int umbral)
- [X] audio sinSilencios(audio s, int freq, int prof, int umbral) (como los test los hice yo, habria que revisarlo)
- [x] encontrarAparicion(audio x, audio y)
- [x] medirLaDistancia(sala m, audio frase, int freq, int prof)


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
- bool hayUnicoAcapador(sala m, int prof, int freq);
- bool acapara(sala m, int prof, int freq, int p);
- int intesidadMedia(audio a);
- int indiceEnTiempo(tiempo t, audio a,int freq);
