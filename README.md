# TPIalgo1


## checklist

- [X] bool grabacionValida(audio s, int prof, int freq) #1
- [X] int elAcaparador(sala m, int freq, int prof) #2
- [X] sala ardillizar(sala m, int prof, int freq) #3
- [x] sala flashElPerezoso(sala m, int prof, int freq) #4
- [x] lista_intervalos silencios(audio s, int prof, int freq, int umbral) #5
- [x] bool hayQuilombo(sala m, int prof, int freq, int umbral)  #6
- [x] float compararSilencios(audio vec, int freq, int prof, int locutor, int umbralSilencio) #7
- [x] float resultadoFinal(sala m, int freq, int prof, int umbralSilencio)#8
- [X] audio sinSilencios(audio s, int freq, int prof, int umbral) #9
- [x] encontrarAparicion(audio x, audio y) #10
- [x] medirLaDistancia(sala m, audio frase, int freq, int prof) #11

# Como correr cobertura:
- (1) Correr proyecto.
- (2)Desde la carpeta *salaDeReuniones_TPI/src/cmake-build-debug/CMakeFiles/salaDeReunion.dir*, copiar archivos generados a la carpeta *salaDeReuniones_TPI/src/pdir*.
### es posible que algunos archivos no los pueda leer, por eso los puse en *salaDeReuniones_TPI/src/pdirquenolee*
- (3) Abrir terminal desde *salaDeReuniones_TPI/src/* y ejecutar `lcov --capture --directory pdir --output-file odir/coverage.info`
- (4) Luego correr `genhtml odir/coverage.info --output-directory odir/cobertura`
- (5) Abrir archivo `index.html` localizado en *salaDeReuniones_TPI/src/odir/cobertura*. Aqui pueden ver la cobertura