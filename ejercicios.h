#ifndef SALADEREUNION_EJERCICIOS_H
#define SALADEREUNION_EJERCICIOS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include "definiciones.h"

using namespace std;

bool grabacionValida(audio s, int prof, int freq);
bool enRango(audio s, int prof);
bool micFunciona(audio s, int freq);
audio subseq(audio s, int i, int j);
bool sonTodosCeros(audio a);

int elAcaparador(sala m, int freq, int prof);
bool acapara(sala m, int p, int prof, int freq);
float intensidadMedia(audio a);

sala ardillizar(sala m, int prof, int freq);
audio ardillizarAudio(audio a);

sala flashElPerezoso(sala m, int prof, int freq);
vector<int> vecInterpolado(vector<int> a);

lista_intervalos silencios(audio &s, int prof, int freq, int umbral);
bool esSilencio (audio &s,intervalo inter,int umbral,int i,int j, int freq);
int indiceEnTiempo(float tiempo, int freq);
bool noSuperaUmbral (audio &s, int i, int j,int umbral);
bool noHaySilencioMayor(audio &s, int i, int j, int umbral);

bool hayQuilombo(sala m, int prof, int freq, int umbral);
bool seRespetan(sala m, int p1, int p2, int freq, int umbral, int prof);
bool haySilencioQueLoContiene(audio a, int i, int freq, int umbral, int prof);

lista_intervalos cargarIntervaloDeHabla(string archivo);
vector<bool> enmascarar(lista_intervalos listaIntervalo, tiempo dur);
void negacionLogica(vector<bool> &mascara );
vector<bool> enmascararSilencios(audio &s, int umbral);
audio deArchivoAVector (string archivo);
int verdaderosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos);
int verdaderosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos);
int falsosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos);
int falsosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos);
float compararSilencios(audio &vec, int freq, int prof, int locutor, int umbralSilencio);
float resultadoFinal(sala &m, int freq, int prof, int umbralSilencio);
void resultadosEjercicio7(int umbralSilencio);

audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral);

int encontrarAparicion(audio x, audio y);
int comienzoCorrelacion(audio a,audio frase);
bool esMaximaCorrelacion(audio a, int starPoint, audio frase);

locutor medirLaDistancia(sala m, audio frase, int freq, int prof);

#endif //SALADEREUNION_EJERCICIOS_H
