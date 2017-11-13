#include "ejercicios.h"
#include "Funciones_TPI.h"

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
        while(j < s.size()){
            audio subsecuencia = subseq(s, i, j);
            float duracion = subsecuencia.size() / (float)freq;
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
    for(int i = 0; i < m.size(); i++)
        if(acapara(m, i, prof, freq))
            persona = i;
    return persona;
}

bool acapara(sala m, int posibleAcaparador, int prof, int freq){
    bool res = true;
    int persona = 0;
    while(persona < m.size()){
        if(persona != posibleAcaparador and intensidadMedia(m[persona]) >= intensidadMedia(m[posibleAcaparador]))
            res = false;
        persona++;
    }
    return res;

}

float intensidadMedia(audio a) {
    int i = 0;
    int sum = 0;
    while (i < a.size()) {
        sum += abs(a[i]);
        i++;
    }
    return sum/(float)a.size();
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

    int i = 0;
    while(i < length_m){
        int j = 0;
        int l = 0;
        while(j < m[i].size() or l < vecInterpolado(m[i]).size()){
            res[i][2*j] = m[i][j];
            res[i][2*j+1] = vecInterpolado(m[i])[l];
            j++;
            l++;
        }
        i++;
    }
    return res;
}

vector<int> vecInterpolado(vector<int> a){
    vector<int> interpolado;
    for(int i = 1; i < a.size(); i++){
        int promedioVecinos = floor((a[i-1] + a[i])/2);
        interpolado.push_back(promedioVecinos);
    }
    return interpolado;
}

/************************** EJERCICIO silencios **************************/
lista_intervalos silencios(audio &s, int prof, int freq, int umbral){
    lista_intervalos res;
    int i = 0;
    while(i < s.size()) {
        if (abs(s[i]) <= umbral) {
            //solo en este caso me interesaria armar una tupla
            int j = i + indiceEnTiempo(0.1, freq) + 1; //asi la duracion es mayor a 0.1 segundos
            bool candidatoASilencio = noSuperaUmbral(s, i, j, umbral);
            if(candidatoASilencio) {
                while (j < s.size() and abs(s[j]) <= umbral) {
                    if (noHaySilencioMayor(s, i, j, umbral)) {//armo la tupla
                        intervalo tupla;
                        float primerElemento = i / (float) freq; //tiempo hasta i exclusive
                        float segundoElemento = (j + 1) / (float) freq; //tiempo hasta j inclusive (por eso +1)
                        get<0>(tupla) = primerElemento;
                        get<1>(tupla) = segundoElemento;
                        res.push_back(tupla);
                    }
                    j++;
                }
                i = j;
            }
        }
        i++;
    }
    return res;
}

bool esSilencio (audio &s, intervalo inter, int umbral, int i, int j, int freq){
    bool res = false;
    float tf = get<1>(inter);
    float ti = get<0>(inter);
    bool duracionValida = indiceEnTiempo(tf, freq) - indiceEnTiempo(ti, freq) > indiceEnTiempo(0.1, freq);
    if(duracionValida and noSuperaUmbral(s, i, j, umbral) and noHaySilencioMayor(s, i, j, umbral))
        res = true;
    return res;
}

int indiceEnTiempo(float tiempo, int freq){
    int res = floor(freq * tiempo);
    return res;
}

bool noSuperaUmbral (audio &s, int i, int j,int umbral) {
    bool res = true;
    for (int k = i; k <= j; k++)
        if (abs(s[k]) > umbral)
            res = false;
    return res;
}

bool noHaySilencioMayor(audio &s, int i, int j, int umbral) {
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
/* en los archivos spkrX.dat obtengo de las primeras 3 posiciones los valores
 * correspondientes a la frecuencia, profundidad y duracion de cada audio */


lista_intervalos cargarIntervaloDeHabla(string archivo){
    lista_intervalos res;
    ifstream entrada;
    entrada.open(archivo, ifstream::in);
    while(!entrada.eof()){
        tiempo tIni;
        tiempo tFin;
        intervalo tupla;
        entrada >> tIni >> tFin;
        get<0>(tupla) = tIni;
        get<1>(tupla) = tFin;
        res.push_back(tupla);
    }
    entrada.close();
    return res;
}

vector<bool> enmascarar(tiempo dur, lista_intervalos tiempos) {
    vector<bool> mascara(dur * 100, false);
    int i = 0;
    while (i < mascara.size()) {
        int j = 0;
        while (j < tiempos.size()) {
            float t0 = get<0>(tiempos[j]);
            float t1 = get<1>(tiempos[j]);
            if(t0 <= tiempoEnPosicion(i) and tiempoEnPosicion(i) < t1)
                mascara[i] = true;
            j++;
        }
        i++;
    }
    return mascara;
}

float tiempoEnPosicion(int i) {
    return i / (float) 100;
}

void negacionLogica(vector<bool> &mascara ) {
    for (int i = 0; i < mascara.size(); i++) {
        bool temp = mascara[i];
        mascara[i] = !temp;
    }
}

vector<bool> enmascararSilencios(audio &s, int umbral, int prof, int freq){
    lista_intervalos silenciosSinMascara = silencios(s, prof, freq, umbral);
    float duracion = s.size() / freq;
    vector<bool> silencioEnmascarado = enmascarar(duracion, silenciosSinMascara);
    return silencioEnmascarado;
}

unsigned int verdaderosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de T detectados que eran T realmente
    //se asume que las longitudes de ambos vectores es la misma
    unsigned int res = 0;
    for(int i = 0; i < mascaraDesdeIntervalos.size(); i++){
        if(mascaraDesdeIntervalos[i] == true)
            if(mascaraConAlgoritmo[i] == true)
                res++;
    }
    return res;
}
unsigned int verdaderosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de F detectados que eran F realmente
    //se asume que las longitudes de ambos vectores es la misma
    unsigned int res = 0;
    for(int i = 0; i < mascaraDesdeIntervalos.size(); i++){
        if(mascaraDesdeIntervalos[i] == false)
            if(mascaraConAlgoritmo[i] == false)
                res++;
    }
    return res;
}
unsigned int falsosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de T detectados que eran F realmente
    //se asume que las longitudes de ambos vectores es la misma
    unsigned int res = 0;
    for(int i = 0; i < mascaraDesdeIntervalos.size(); i++){
        if(mascaraDesdeIntervalos[i] == false)
            if(mascaraConAlgoritmo[i] == true)
                res++;
    }
    return res;
}
unsigned int falsosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de F detectados que eran T realmente
    //se asume que las longitudes de ambos vectores es la misma
    unsigned int res = 0;
    for(int i = 0; i < mascaraDesdeIntervalos.size(); i++){
        if(mascaraDesdeIntervalos[i] == true)
            if(mascaraConAlgoritmo[i] == false)
                res++;
    }
    return res;
}

float compararSilencios(audio &vec, int freq, int prof, int locutor, int umbralSilencio){
    //obtengo la mascara de silencios de vec
    vector<bool> mascaraDesdeArchivo = enmascararSilencios(vec, umbralSilencio, prof, freq);

    //obtengo la mascara de habla asociada al locutor. El locutor puede ser 0, 1, 2, 3, 4, 5, o 6
    //(este ultimo es el microfono del centro)
    string archivoDeHabla;
    if (locutor == 0){archivoDeHabla = "datos/habla_spkr0.txt";}
    if (locutor == 1){archivoDeHabla = "datos/habla_spkr1.txt";}
    if (locutor == 2){archivoDeHabla = "datos/habla_spkr2.txt";}
    if (locutor == 3){archivoDeHabla = "datos/habla_spkr3.txt";}
    if (locutor == 4){archivoDeHabla = "datos/habla_spkr4.txt";}
    if (locutor == 5){archivoDeHabla = "datos/habla_spkr5.txt";}
    if (locutor == 6){archivoDeHabla = "datos/habla_spkrdefault.txt";}
    lista_intervalos listaDeHabla = cargarIntervaloDeHabla(archivoDeHabla);
    int dur = vec.size()/freq;
    vector<bool> mascaraDesdeIntervalo = enmascarar(dur, listaDeHabla);
    //transformo la mascara de habla a mascara de silencios
    negacionLogica(mascaraDesdeIntervalo);

    //calculo los datos necesarios para el estadistico
    unsigned int vp = verdaderosPositivos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    unsigned int vn = verdaderosNegativos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    unsigned int fp = falsosPositivos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    unsigned int fn = falsosNegativos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    float precision = vp / (float) (vp + fp);
    float recall = vp / (float) (vp + fn);

    //calculo el estadistico
    float f1 = (2 * precision * recall) / (precision + recall);
    return f1;
}

float resultadoFinal(sala &m, int freq, int prof, int umbralSilencio){
    int cantidadDeLocutores = m.size();
    float sumaScores = 0;
    for (int i = 0; i < cantidadDeLocutores; i++){
        sumaScores += compararSilencios(m[i], freq, prof, i, umbralSilencio);
    }
    return sumaScores / (float) cantidadDeLocutores;
}

/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, int freq, int prof, int umbral) {
    audio result;
    int i =0;
    vector < tuple<int,int> > aux;
    /*bool esSilencio (audio s,intervalo inter,int umbral,int i,int j)*/
    while(i<s.size()) {
        if (s[i] <= umbral) {
            for (int j = i; j < s.size(); j++) {
                tuple<float,float> inter;
                get<0>(inter) = i/(float)freq;
                get<1>(inter) = j/(float)freq;
                if (esSilencio(s,inter,umbral,i,j-1, freq)) {
                    result.push_back(s[j]);
                    i = j;
                }
            }
        } else {
            result.push_back(s[i]);
        }
        i++;
    }
    /*si el intervalo es un silencio y no esta contenido en otro silencio(esSilencio)
    salto la posicion inicial a j sino pusheo tod o el intervalo al vector audio   */


    return result;
}
/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y){
    int res = comienzoCorrelacion(x,y);
    return res;
}

int comienzoCorrelacion(audio a, audio frase) {
    int l_a = a.size();
    int l_f = frase.size();
    int acum = 0;
    for (int i = 0; i < l_a - l_f; i++) {
        if (correlacion(subseq(a, acum, acum + l_f), frase) < correlacion(subseq(a, i, i + l_f), frase)) {
            acum = i;

        }
    }
    return acum;
}

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof){
    locutor out;
    int elLoDijo = 0;
    for(int p = 0; p < m.size(); p++){
        if (intensidadCorrelacion(m[elLoDijo],frase) < intensidadCorrelacion(m[p],frase)){ // aca estoy busacando quien lo dijo
            elLoDijo = p;
        }
    }
    get<0>(out) = elLoDijo;

    int j=0;
    while(j < m.size()) {
        if(j!= get<0>(out)) {
            get<1>(out).push_back(distanciaAP(m, get<0>(out), j, freq, frase)); // busco las distancias de cada microfono
        }else{
            get<1>(out).push_back(0); // la distancia entre la persona que dijo la frase y si misma es cero
        }
        j++;
    }

    return out;
}

float intensidadCorrelacion(audio a, audio frase){
    int l_a= a.size();
    int l_f= frase.size();
    float sum = 0;
    int acum = 0;
    for (int i = 0; i < l_a - l_f; i++) {
        if (correlacion(subseq(a, acum, acum + l_f), frase) < correlacion(subseq(a, i, i + l_f), frase)) {
            acum = i;
        }
    }
    sum =  intensidadMedia(subseq(a, acum, acum + l_f));

    return sum;
}


float distanciaAP(sala m, int p1,int p2,int freq, audio frase) {
    float vel_sonido_freq = (float)343.2 / (float)freq;
    float dist = abs(comienzoCorrelacion(m[p1], frase) - comienzoCorrelacion(m[p2], frase)) * vel_sonido_freq;

    return dist;
}