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
lista_intervalos silencios(audio &s, int prof, int freq, int umbral) {
    lista_intervalos res;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            intervalo tupla;
            float primerElemento = i / (float) freq; //despues de este tiempo esta la muestra i, i+1, ...
            float segundoElemento = (j + 1) / (float) freq; //antes de este tiempo esta la muetra j, j-1, ... (por eso j+1 y no j)
            get<0>(tupla) = primerElemento;
            get<1>(tupla) = segundoElemento;
            if (esSilencio(s, tupla, umbral, i, j, freq))
                res.push_back(tupla);
        }
    }
    return res;
}

bool esSilencio (audio &s, intervalo inter, int umbral, int i, int j, int freq){
    bool res = false;
    float tf = get<1>(inter);
    float ti = get<0>(inter);
    bool duracionValida = indiceEnTiempo(tf, freq) - indiceEnTiempo(ti, freq) >= indiceEnTiempo(0.1, freq);
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
int freq = 16000;
int prof = 16;
int dur = 120;

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
        get<0>(tupla) = tFin;
        res.push_back(tupla);
    }
    return res;
}

vector<bool> enmascarar(lista_intervalos listaIntervalo, tiempo dur){
    vector <bool> mascara;
    for(int i = 0; i < dur*100; i++) {
        bool valor = false;
        for (int j = 0; j < listaIntervalo.size(); j++) {
            float t0 = get<0>(listaIntervalo[j]);
            float t1 = get<1>(listaIntervalo[j]);
            float tiempoEnPosicion_i = i /(float)100;
            if (t0 <= tiempoEnPosicion_i and tiempoEnPosicion_i < t1)
                valor = true;
        }
        mascara.push_back(valor);
    }
    return mascara;
}

void negacionLogica(vector<bool> &mascara ) {
    for (int i = 0; i < mascara.size(); i++) {
        bool temp = mascara[i];
        mascara[i] = !temp;
    }
}

vector<bool> enmascararSilencios(audio &s, int umbral){
    lista_intervalos silenciosSinMascara = silencios(s, prof, freq, umbral);
    float duracion = s.size() /(float) freq;
    vector<bool> silencioEnmascarado = enmascarar(silenciosSinMascara, duracion);
    return silencioEnmascarado;
}

audio deArchivoAVector (string archivo){
    int freq = 0;
    int prof = 0;
    int dur = 0;
    audio vector;
    ifstream entrada;
    entrada.open(archivo, ifstream::in);
    entrada >> freq;
    entrada >> prof;
    entrada >> dur;
    while(!entrada.eof()) {
        int amplitud = 0;
        entrada >> amplitud;
        vector.push_back(amplitud);
    }
    entrada.close();
   return vector;
}

/* //audios reales
audio centro = deArchivoAVector("datos/pzm.dat");
audio persona0 = deArchivoAVector("datos/spkr0.dat");
audio persona1 = deArchivoAVector("datos/spkr1.dat");
audio persona2 = deArchivoAVector("datos/spkr2.dat");
audio persona3 = deArchivoAVector("datos/spkr3.dat");
audio persona4 = deArchivoAVector("datos/spkr4.dat");
audio persona5 = deArchivoAVector("datos/spkr5.dat");
*/
int verdaderosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de T detectados que eran T realmente
    //se asume que las longitudes de ambos vectores es la misma
    int res = 0;
    negacionLogica(mascaraDesdeIntervalos);
    for(int i = 0; i < mascaraConAlgoritmo.size(); i++){
        if(mascaraDesdeIntervalos[i] == true)
            if(mascaraConAlgoritmo[i] == true)
                res++;
    }
    return res;
}
int verdaderosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de F detectados que eran F realmente
    //se asume que las longitudes de ambos vectores es la misma
    int res = 0;
    negacionLogica(mascaraDesdeIntervalos);
    for(int i = 0; i < mascaraConAlgoritmo.size(); i++){
        if(mascaraDesdeIntervalos[i] == false)
            if(mascaraConAlgoritmo[i] == false)
                res++;
    }
    return res;
}
int falsosPositivos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de T detectados que eran F realmente
    //se asume que las longitudes de ambos vectores es la misma
    int res = 0;
    negacionLogica(mascaraDesdeIntervalos);
    for(int i = 0; i < mascaraConAlgoritmo.size(); i++){
        if(mascaraDesdeIntervalos[i] == false)
            if(mascaraConAlgoritmo[i] == true)
                res++;
    }
    return res;
}
int falsosNegativos(vector<bool> &mascaraConAlgoritmo, vector<bool> &mascaraDesdeIntervalos){
    //cantidad de F detectados que eran T realmente
    //se asume que las longitudes de ambos vectores es la misma
    int res = 0;
    negacionLogica(mascaraDesdeIntervalos);
    for(int i = 0; i < mascaraConAlgoritmo.size(); i++){
        if(mascaraDesdeIntervalos[i] == true)
            if(mascaraConAlgoritmo[i] == false)
                res++;
    }
    return res;
}

float compararSilencios(audio &vec, int freq, int prof, int locutor, int umbralSilencio){
    /* obtengo la mascara de silencios de vec y la mascara de habla asociada
     * al locutor. El locutor puede ser 0, 1, 2, 3, 4, 5 o 6 (este ultimo es el
     * microfono del centro */
    vector<bool> mascaraDesdeArchivo = enmascararSilencios(vec, umbralSilencio);
    string archivoDeHabla;
    if (locutor == 0){archivoDeHabla = "datos/habla_spkr0.txt";}
    if (locutor == 1){archivoDeHabla = "datos/habla_spkr1.txt";}
    if (locutor == 2){archivoDeHabla = "datos/habla_spkr2.txt";}
    if (locutor == 3){archivoDeHabla = "datos/habla_spkr3.txt";}
    if (locutor == 4){archivoDeHabla = "datos/habla_spkr4.txt";}
    if (locutor == 5){archivoDeHabla = "datos/habla_spkr5.txt";}
    if (locutor == 6){archivoDeHabla = "datos/habla_spkrdefault.txt";}
    lista_intervalos listaDeHabla = cargarIntervaloDeHabla(archivoDeHabla);
    vector<bool> mascaraDesdeIntervalo = enmascarar(listaDeHabla, dur);
    int vp = verdaderosPositivos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    int vn = verdaderosNegativos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    int fp = falsosPositivos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    int fn = falsosNegativos(mascaraDesdeArchivo, mascaraDesdeIntervalo);
    //guarda con las disiones por cero
    float precision = vp / (vp + fp);
    float recall = vp / (vp + fn);
    float f1 = (2 * precision * recall) / (precision + recall);
    return f1;
}

float resultadoFinal(sala &m, int freq, int prof, int umbralSilencio){
    float cantidadDeLocutores = m.size();
    float sumaScores = 0;
    for (int i = 0; i < cantidadDeLocutores; i++){
        sumaScores += compararSilencios(m[i], freq, prof, i, umbralSilencio);
    }
    return sumaScores / cantidadDeLocutores;
}

void resultadosEjercicio7(int umbralSilencio){
    int decision = 0;
    cout << "Ingrese el numero de la persona a la que le quiere comparar" << endl;
    cout << "los momentos de silencio: " << endl;
    cout << "* Persona 0" << endl;
    cout << "* Persona 1" << endl;
    cout << "* Persona 2" << endl;
    cout << "* Persona 3" << endl;
    cout << "* Persona 4" << endl;
    cout << "* Persona 5" << endl;
    cout << "* Microfono central (6)" << endl;
    cout << endl;
    cin >> decision;
    if (decision == 0){
        cout << "Copiando vector ..." << endl;
        audio persona0 = deArchivoAVector("datos/spkr0.dat");
        cout << "Vector copiado. El F1 score es: " << endl;
        int locutor = 0;
        cout << compararSilencios(persona0, freq, prof, 0, umbralSilencio) << endl;
    }
    /*  sala m = {centro,
                persona0,
                persona1,
                persona2,
                persona3,
                persona4,
                persona5 };
      cout << "Los F1 score son:" << endl;
      cout << "* Microfono central: " << compararSilencios(centro, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 0: " << compararSilencios(persona0, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 1: " << compararSilencios(persona1, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 2: " << compararSilencios(persona2, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 3: " << compararSilencios(persona3, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 4: " << compararSilencios(persona4, freq, prof, 6, umbralSilencio) << endl;
      cout << "* Persona 5: " << compararSilencios(persona5, freq, prof, 6, umbralSilencio) << endl;
      cout << endl;
      cout << "Y el promedio es: " << resultadoFinal(m, freq, prof, umbralSilencio); */
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

                if(esSilencio(s,inter,umbral,i,j, freq)){
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

//LISTO  (verificar si faltan casos de test)

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
        }
        j++;
    }

    return out;
}


float intensidadCorrelacion(audio a, audio frase){
    int l_a= a.size();
    int l_f= frase.size();
    int sum = 0;
    int acum = 0;
    for (int i = 0; i < l_a - l_f; i++) {
        if (correlacion(subseq(a, acum, acum + l_f), frase) < correlacion(subseq(a, i, i + l_f), frase)) {
            acum = i;
        }
    }
    sum = sum + intensidadMedia(subseq(a, acum, acum + l_f));

    return sum;
}


float distanciaAP(sala m, int p1,int p2,int freq, audio frase) {
    float vel_sonido_freq = 343.2 / freq;
    float dist = abs(comienzoCorrelacion(m[p1], frase) - comienzoCorrelacion(m[p2], frase)) * vel_sonido_freq;

    return dist;
}

//trate de seguir la especificacion pero el programa me cuelga... verificar los auxiliares