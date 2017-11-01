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

//auxiliares
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
    for(int i=0;i<s.size();i++){
        for(int j=i; j<s.size();j++){
            intervalo tupla;
            get<0>(tupla) =(float)i/(float)freq;
            get<1>(tupla) =(float)j/(float)freq;
            if(esSilencio(s,tupla,umbral,i,j)) {
                res.push_back(tupla);

            }

        }

    }


    return res;
}



bool noSuperaUmbral (audio s, int i, int j,int umbral){
    bool res = true;
    for(auto k= i; k <= j; k++) {
        if (s[k] > umbral) {
            res = false;

        }
    }
    return res;
}


bool noHaySilencioMayor(audio s, int i, int j, int umbral) {
    bool res = true;
    if(i>0 && j<s.size()){
        if (abs(s[i - 1]) < umbral || abs(s[j+1])<umbral) {
            res = false;
        }
    }
    else if ( i > 0 ) {
        if (abs(s[i - 1]) < umbral) {
            res = false;
        }
    }else if(j < s.size()){
        if(abs(s[j+1])<umbral) {
            res = false;
        }
    }

    return res;
}



bool esSilencio (audio s,intervalo inter,int umbral,int i,int j){
    bool res = false;
    if((get<1>(inter) - get<0>(inter) > 0.1)  && noSuperaUmbral(s, i,j, umbral) && noHaySilencioMayor(s, i,j, umbral)){
        res = true;

    }
    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool hayQuilombo(sala m, int prof, int freq, int umbral) {
    return false;
}

/************************** EJERCICIO compararSilencios **************************/
/*float compararSilencios(audio vec, int freq, int prof,int locutor, int umbralSilencio){

    que carajos me esta pidiendo?


}*/


// tomo un archivo y lo convierto en una lista de tuplas(float,float)
lista_intervalos convertirALista(string archivo){

    lista_intervalos res;
// abro y leo el archivo
    ifstream fin;
    fin.open(archivo, ios::in);
//itero cada linea y guardo el tiempo inicial y final
    while(!fin.eof()){
        tiempo tInit;
        tiempo tFin;
        intervalo tupla;
        fin >> tInit >> tFin;
        get<0>(tupla)=tInit;
        get<0>(tupla)=tFin;
        res.push_back(tupla);
    }


    return res;
}

//de la lista de intervalos formo un vector de booleanos, cada posicion represente el tiempo i/100 ( intervalos de 10 milesimos) si el tiempo en la posicion se encuentre entre un intervalo de la lista de intervalos devuelvo true sino false
vector<bool> enmascarar(lista_intervalos listaIntervalo, tiempo dur){
    vector <bool> res;

    for(int j=0; j < dur*100; j++) {
        bool valor = false;
        for (int i = 0; i < listaIntervalo.size(); i++) {
            if (get<0>(listaIntervalo[i]) <= j / 100 && j / 100 < get<1>(listaIntervalo[i])) {
                valor = true;
            }

        }
        res.push_back(valor);

    }
    return res;
}

// invierto mascara
void negacionLogica(vector<bool> &mascara ){
    for(int i=0; i<mascara.size();i++){
        if(mascara[i]== false){
            mascara[i] = true;

        }else{
            mascara[i] = true;
        }

    }
    return;
}

//convierto a lista de intervalos los silencios de un audio con la funcion silencios
vector<bool> enmascararSilencios(audio s, int prof, int freq, int umbral){

    lista_intervalos mascaraSilencio = silencios(s,prof,freq,umbral);
    vector<bool> res = enmascarar(mascaraSilencio, s.size()/freq);

    return res;
}

int cantidadVerdaderos(vector<bool> mascara){
    int res = 0;
    for(int i=0; i<mascara.size(); i++){
        if(mascara[i]==true){
            res+=1;

        }

    }
    return res;
}

int cantidadFalsos(vector<bool> mascara){
    int res = 0;
    for(int i=0; i<mascara.size(); i++){
        if(mascara[i]== false){
            res+=1;

        }

    }
    return res;

}

float precision(lista_intervalos listaIntervalos, tiempo dur){
    vector <bool> mascara = enmascarar(listaIntervalos, dur);
    float  res = cantidadVerdaderos(mascara)/(cantidadVerdaderos(mascara)+cantidadFalsos(mascara));

    return res;
}

float recall(lista_intervalos listaIntervalos, audio s, int prof, int freq, int umbral, tiempo dur){
    vector <bool> mascara = enmascarar(listaIntervalos, dur);
    vector <bool> mascaranegativa = enmascararSilencios(s,prof,freq,umbral);
    float  res = cantidadVerdaderos(mascara)/(cantidadVerdaderos(mascara)+cantidadFalsos(mascaranegativa));

    return res;


}

float Funo(lista_intervalos listaIntervalos, audio s, int prof, int freq, int umbral, tiempo dur){
    float res = 2* (precision(listaIntervalos, dur)*recall(listaIntervalos,s,prof,freq,umbral,dur)/(precision(listaIntervalos, dur)+recall(listaIntervalos,s,prof,freq,umbral,dur)));
    return res;

}
//promedio de Funo entre todos los locutores
float resultadoFinal(sala m, int freq, int prof, int umbralSilencio ){
    float res;
    float sum = 0;

    for(int i =0; i<m.size();i++){
        vector <bool> mascaraDeSilencios = enmascararSilencios(m[i],prof,freq,umbralSilencio);
        lista_intervalos mascara = convertirALista(string("habla_spkr")+to_string(i)+".txt");
        sum += Funo(mascara,m[i],prof,freq,umbralSilencio,m[i].size()/freq);
    }


    res = sum/m.size();
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
