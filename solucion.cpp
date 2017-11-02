// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include "math.h"

/************************** EJERCICIO grabacionValida **************************/
bool grabacionValida(audio s, int prof, int freq) {
    bool res = false;
    bool freqValida = freq >= 4;
    bool profValida = prof == 16 or prof == 32;
    int longitud = s.size();
    bool duracionValida = longitud/(float)freq > 1;
    if(freqValida and profValida and duracionValida and enRango(s, prof) and micFunciona(s, freq))
        res = true;
    return res;
}

bool enRango(audio s, int prof){
    bool res = true;
    double limiteInferior = pow(-2, prof - 1);
    double limiteSuperior = pow(2, prof - 1) -1;
    int i = 0;
    while(i < s.size()){
        if(!(limiteInferior <= s[i] and s[i] <= limiteSuperior))
            res = false;
        i++;
    }
    return res;
}

bool micFunciona(audio s, int freq){
    bool res = true;
    int i = 0;
    while (i < s.size()){
        int j = 0;
        while(j < i){
            audio subsecuencia = subseq(s, i, j);
            int duracion = subsecuencia.size() / freq;
            if (duracion > 1 and sonTodosCeros(subsecuencia))
                res = false;
            j++;
        }
        i++;
    }
    return res;
}

audio subseq(audio s, int i, int j){
    audio res;
    for (int k = i; k < j; k++)
        res.push_back(s[k]);
    return res;
}

bool sonTodosCeros(audio a){
    bool res = true;
    for(int i = 0; i < a.size(); i++)
        if (a[i] != 0)
            res = false;
    return res;
}


/************************** EJERCICIO elAcaparador **************************/
int elAcaparador(sala m, int freq, int prof) {
    return -1;
}

/************************** EJERCICIO ardillizar **************************/
sala ardillizar(sala m, int prof, int freq) {
    sala res;
    int i = 0;
    while(i < m.size()){
        audio ardillizado = ardillizarAudio(m[i]);
        res.push_back(ardillizado);
        i++;
    }
    return res;
}

/*¿Para que entran por parametro prof y freq si no debo garantizar nada sobre ellos en
 * la postcondicion?*/

audio ardillizarAudio(audio a){
    audio res;
    int i = 0;
    while (i < a.size()){
        if(i % 2 == 0)
            res.push_back(a[i]);
        i++;
    }
    return res;
}

/************************** EJERCICIO flashElPerezoso **************************/
sala flashElPerezoso(sala m, int prof, int freq) {
    sala res;
    return res;
}

/************************** EJERCICIO silencios **************************/
lista_intervalos silencios(audio s, int prof, int freq, int umbral) {
    lista_intervalos res;
    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool hayQuilombo(sala m, int prof, int freq, int umbral) {
    bool res = false;
    int p1 = 0;
    int cantPersonas = m.size();
    while(p1 < cantPersonas){
        int p2 = 0;
        while(p2 < cantPersonas){
            if(!seRespetan(m, p1, p2, freq, umbral, prof))
                res = true;
            p2++;
        }
        p1++;
    }
    /* el codigo precedente compara todos los posibles pares de personas y deja en res un valor
     * de verdad que depende de si 'hay respeto' o no entre todos estos pares. Si hay respeto,
     * no hay quilombo, entonces res = false */
    return res;
}

bool seRespetan(sala m, int p1, int p2, int freq, int umbral, int prof){
    bool res = true;
    audio persona1 = m[p1];
    audio persona2 = m[p2];
    int i = 0;
    while(i < persona1.size()){
        if( !haySilencioQueLoContiene(persona1, i, freq, umbral, prof) and
            !haySilencioQueLoContiene(persona2, i, freq, umbral, prof)    )
            /* si vale la guarda anterior, persona1[i] y persona2[i] estan en dos no-silencios
             * simultaneamente, es decir hay superposicion de habla entre persona1 y persona2
             * por ende no hay respeto, luego seRespetan devuelve false */
            res = false;
        i++;
    }
    return res;
}

bool haySilencioQueLoContiene(audio a, int i, int freq, int umbral, int prof){
    bool res = false;
    float tiempoEnCuestion = i * freq; //asocio a la muestra a[i] un tiempo
    lista_intervalos momentosDeSilencio = silencios(a, freq, umbral, prof);
    int j = 0;
    while(j < momentosDeSilencio.size()){
        int inicio = get<0>(momentosDeSilencio[j]);
        int fin = get<1>(momentosDeSilencio[j]);
        if(inicio <= tiempoEnCuestion and tiempoEnCuestion <= fin)
            res = true;
        j++;
    }
    /* en el ciclo me fijo si el tiempo asociado a a[i] se encuentra dentro de un intervalo de silencio o no.
     * Por ende devuelvo true si y solo si al menos un silencio contiene a a[i] */
    return res;
}

/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result;
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y) {
    return -1;
}

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof) {
    locutor out;
    return out;
}
