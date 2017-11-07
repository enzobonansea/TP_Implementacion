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
int elAcaparador(sala m, int freq, int prof){
    int persona = 0;
    for(int i =0; i<m.size();i++){
        if(acapara(m,i,prof,freq)){
            persona = i;

        }

    }

    return persona;
}

bool acapara(sala m, int p, int prof, int freq){
    int x =0;
    bool res = false;
    while(x<m.size()){
        if(x!=p && intensidadMedia(m[x]) < intensidadMedia(m[p])){
            res = true;


        }


        x=x+1;

    }
    return res;

}
float intensidadMedia(audio a){
    int i=0;
    int sum = 0;
    while(i<a.size()){
        sum += abs(a[i])/a.size();
        i = i+1;
    }
    return sum;
int elAcaparador(sala m, int freq, int prof){
    int persona = 0;
    for(int i =0; i<m.size();i++){
        if(acapara(m,i,prof,freq)){
            persona = i;

        }

    }

    return persona;
}

bool acapara(sala m, int p, int prof, int freq){
    int x =0;
    bool res = false;
    while(x<m.size()){
        if(x!=p && intensidadMedia(m[x]) < intensidadMedia(m[p])){
            res = true;

        }
        x=x+1;
    }
    return res;

}
float intensidadMedia(audio a){
    int i=0;
    int sum = 0;
    while(i<a.size()){
        sum += abs(a[i])/a.size();
        i = i+1;
    }
    return sum;
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
sala flashElPerezoso(sala m, int prof, int freq){
    int length_m = m.size();
    int length_mi = 2 * m[0].size() - 1;
    sala res(length_m, vector<int> (length_mi));

    int i= 0;
    while(i<length_m){
        int j = 0;
        int l = 0;
        while(j<m[i].size() || l<vecInterpolado(m[i]).size()){
            res[i][2*j] = m[i][j];
            res[i][2*j+1] = vecInterpolado(m[i])[l];
            j++;
            l++;
        }
        i++;
    }
    return res;
}
//fun para inteppolar vector
vector<int> vecInterpolado(vector<int> a){
    vector<int> aux;
    for( int i=1; i<a.size(); i++){
        aux.push_back(floor(((a[i-1] + a[i])/2)));
    }
    return aux;
}

/************************** EJERCICIO silencios **************************/
lista_intervalos silencios(audio s, int prof, int freq, int umbral) {
    lista_intervalos res;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            intervalo tupla;
            float primerElemento = i / (float) freq; //despues de este tiempo esta la muestra i, i+1, ...
            float segundoElemento = (j + 1) / (float) freq; //antes de este tiempo esta la muetra j, j-1, ... (por eso j+1 y no j)
            get<0>(tupla) = primerElemento;
            get<1>(tupla) = segundoElemento;
            if (esSilencio(s, tupla, umbral, i, j))
                res.push_back(tupla);
        }
    }
    return res;
}

bool esSilencio (audio s, intervalo inter, int umbral, int i, int j){
    bool res = false;
    float duracion = get<1>(inter) - get<0>(inter);
    float epsilon = 0.00001;
    bool duracionValida = (duracion >= 0.1 - epsilon) or (duracion >= 0.1 + epsilon);
    if(duracionValida and noSuperaUmbral(s, i, j, umbral) and noHaySilencioMayor(s, i, j, umbral))
        res = true;
    return res;
}

bool noSuperaUmbral (audio s, int i, int j,int umbral) {
    bool res = true;
    for (int k = i; k <= j; k++)
        if (abs(s[k]) > umbral)
            res = false;
    return res;
}

bool noHaySilencioMayor(audio s, int i, int j, int umbral) {
    bool res = true;
    if(i > 0){
        if (j < s.size() - 1){
            res = abs(s[i-1]) > umbral and abs(s[j+1] > umbral);
        }else{
            res = abs(s[i-1]) > umbral;
        }
    }else{
        if(j < s.size() - 1){
            res = abs(s[j+1]) > umbral;
        }
    }
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
            if(p1 != p2 and !seRespetan(m, p1, p2, freq, umbral, prof))
                res = true;
            p2++;
        }
        p1++;
    }
    return res;
}

bool seRespetan(sala m, int p1, int p2, int freq, int umbral, int prof){
    bool res = true;
    audio persona1 = m[p1];
    audio persona2 = m[p2];
    int i = 0;
    while(i < persona1.size()){
        bool algunSilencioContieneLaMuestra = haySilencioQueLoContiene(persona1, i, freq, umbral, prof) or haySilencioQueLoContiene(persona2, i, freq, umbral, prof);
        res &= algunSilencioContieneLaMuestra;
        i++;
    }
    return res;
}

bool haySilencioQueLoContiene(audio a, int i, int freq, int umbral, int prof){
    bool res = false;
    float tiempoAntesDeLaMuestra = i/(float)freq;
    float tiempoDespuesDeLaMuestra = (i+1)/(float)freq;
    lista_intervalos intervalosDeSilencio = silencios(a, prof, freq, umbral);
    int j = 0;
    while(j < intervalosDeSilencio.size()){
        float inicio = get<0>(intervalosDeSilencio[j]);
        float fin = get<1>(intervalosDeSilencio[j]);
        bool enElIntervalo = tiempoAntesDeLaMuestra >= inicio and tiempoDespuesDeLaMuestra <= fin;
        if(enElIntervalo)
            res = true;
        j++;
    }
    return res;
}
/************************** EJERCICIO compararSilencios **************************/
/*float compararSilencios(audio vec, int freq, int prof,int locutor, int umbralSilencio){

    // todo que carajos me esta pidiendo?


}*/


// tomo un archivo y lo convierto en una lista de tuplas(float,float)
lista_intervalos convertirALista(string archivo){

    lista_intervalos res;
// abro y leo el archivo
    ifstream fin;
    fin.open(archivo, ios::in);
//itero cada linea y guardo el tiempo inicial y final en una lista de tuplas
    while(!fin.eof()){
        tiempo tInit;//tiempo inicial
        tiempo tFin;//tiempo final
        intervalo tupla;//tupla del tiempo inicial y final
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
                //me fijo los intervalos de 10 milesimos si existen dentro de algun intervalo de habla devuelvo true (mirar especificacion de TiempoEnPosicionI
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
    //creo una lista de intervalos de silencios del audio s
    lista_intervalos mascaraSilencio = silencios(s,prof,freq,umbral);
    //enmascaro los silencios TRUE si es Silencio FALSE si no es silencio
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
//estoy hay que implementar en compararSilencios
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
        //convierto a lista de intervalos al archivo del locutor
        lista_intervalos mascara = convertirALista(string("habla_spkr")+to_string(i)+".txt");
        sum += Funo(mascara,m[i],prof,freq,umbralSilencio,m[i].size()/freq);
    }


    res = sum/m.size();
    return res;
}

/************************** EJERCICIO sacarPausas **************************/
//usar esSilencio del punto 7
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result;
    int i =0;
    /*bool esSilencio (audio s,intervalo inter,int umbral,int i,int j)*/
    while(i<s.size()){
        for(int j=i; j<s.size();j++){
            tuple<float,float> inter;//chequeo por intervalos
            get<0>(inter)=float(i/freq);//tiempo inicial
            get<1>(inter)=float(j/freq);//tiempo final
            /*si el intervalo es un silencio y no esta contenido en otro silencio(esSilencio)
              salto la posicion inicial a j sino pusheo tod o el intervalo al vector audio   */

                if(esSilencio(s,inter,umbral,i,j)){
                    i = j;
                }else{
                    for(int k=i;k<=j;k++) {
                        result.push_back(s[k]);
                    }
                }

        }
        //aca si i= j termina j+1 sino se incrementa en 1 el i original
        i++;
    }
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y) {   //x = target  y=audio
    int res = comienzoCorrelacion(x,y);
    return res;
}

int comienzoCorrelacion(audio a,audio frase){
    int l_a= a.size();
    int l_f= frase.size();
    int acum = 0;
        for(int i = 0; i<l_a - l_f; i++){
            if (esMaximaCorrelacion(a,i,frase)){
                acum = acum +i;
            }
        }

    return acum;
}


bool esMaximaCorrelacion(audio a, int starPoint, audio frase){
    int l_a= a.size();
    int l_f= frase.size();
    bool res = false;
        for(int i = 0; i < l_a - l_f; i++){
            if(i!=starPoint){
                if (correlacion(subseq(a,i,i+l_f),frase) < correlacion(subseq(a, starPoint, starPoint+l_f),frase)){
                    res= true;
                } else {
                    res = false;
                }
            }
        }
    return res;
}



//LISTO  (verificar si faltan casos de test)

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof) {
    locutor out;



    return out;
}