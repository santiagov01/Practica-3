#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int n = 0;
int metodo = 0;
void invertir(char[],int,int); //bloque y frecuencia/condicion para invertir
int contarbins(char[],int semilla);
void encripting(char[],int);
int s_real(char*,int);
void c_bin(char*,int,char*);
void first_params(char[],char[]);


void separar(char **, char*, int);

void lectura(char *nf_input, char* c_original, int size_cad, char *bin, int tam_cad);
void escritura();

void regla();
bool compare(char* a, char* b); //Función para comparar si las cadenas de caracteres son iguales.
int main()
{
    char nf_input[64]=" ", nf_output[64]=" ";//nombre archivos
    first_params(nf_input,nf_output); //semilla, metodo, nombre archivos


    char c_original[256] =" "; //cadena original
    char bin[256*8]="0"; // ?
    int tam_cad = 0;

    lectura(nf_input,c_original,sizeof(c_original),bin,tam_cad);



    return 0;
}
void invertir(char actual[], int freq,int semilla){
    if(!(freq>semilla)){
        if(freq ==0){
            for(int i = 0;i<semilla;i++){
                if(actual[i]=='1')cout << '0';
                else cout << '1';
            }
        }else{
            int n = 1;
            for(int i = 0;i<semilla;i++){
                if(i == (freq*n)-1){
                    if(actual[i]=='1')cout << '0';
                    else{
                        cout << '1';
                    }
                    n++;
                }else{
                    cout << actual[i];
                }

            }
        }

    }else{
        for(int i = 0;i<semilla;i++){
            cout << actual[i];
        }
    }
}
int contarbins(char anterior[], int semilla){
    int unos = 0;
    int ceros = 0;
    for(int i = 0; i<semilla;i++){
        if(anterior[i]=='1')unos++;
        else ceros++;
    }
    //cout << endl << "cantidad 0s " << ceros << endl;
    if(unos==ceros)return 0;
    if(ceros > unos)return 2;
    else return 3;
}
void encripting(char binario[],int nBloques){
    char *anterior= new char [n];
    char *actual = new char [n];

    int semilla = 4;

    int cont =0;
    //para el primer bloque
    for(int i = 0; i<semilla;i++){
        anterior[i]=binario[i];
        if(binario[i]=='0'){
            cout << 1;
        }else{
            cout << 0;
        }
        cont++;//me dice en que posición va.
    }
    //para el resto de bloques

    for(int i = 1; i<nBloques;i++){
        for(int j=0;j<semilla;j++){
            actual[j]= binario[cont];//actualiza bloque actual
            cont++;
        }
        //hacer operacion
        invertir(actual,contarbins(anterior,semilla),semilla);
        for(int j=0;j<semilla;j++){
            anterior[j]= actual[j];//actualiza anterior
        }

    }

    delete[] actual;
    delete[] anterior;
}
void lectura(char *nf_input, char* cad_linea, int size_cad, char *bin, int tam_cad){
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    int nBloques = 0;
    try{
    //Lectura
        fin.open(nf_input);        //abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }
        int saltos = 0;

        while(fin.good()){ //lee caracter a caracter hasta el fin del archivo
            char temp=fin.get();
            if(fin.good()){
                if(temp == '\n'){
                    saltos++;
                }
            }

        }
        fin.close();

        //volver a abrir para evitar problemas.
        fin.open(nf_input);
        if(!fin.is_open()){
            throw '2';
        }
        //leer linea del archivo y guardar en variable.
        if(saltos == 0){
            fin.getline(cad_linea,256);//((((revisar que es necesario cambiar))))***
            tam_cad = s_real(cad_linea,size_cad);//longitud real de cada linea
            c_bin(cad_linea,tam_cad,bin);
            nBloques = tam_cad*8/n;
            if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
            encripting(bin,nBloques);
        }else{
            for(int c = 0; c<=saltos;c++){
                fin.getline(cad_linea,256);//extrae linea a linea.
                tam_cad = s_real(cad_linea,size_cad);//longitud real de cada linea
                c_bin(cad_linea,tam_cad,bin);
                nBloques = tam_cad*8/n;
                if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
                encripting(bin,nBloques);
                cout << endl;

                //[HACE FALTA REVISAR COMO ESCRIBIRLO CORRECTAMENTE
                // EN EL ARCHIVO]
            }
        }
        fin.close();

    }

    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='1'){
            cout<<"Error al abrir el archivo para escritura.\n";
        }
        else if(c=='2'){
            cout<<"Error al abrir el archivo para lectura.\n";
        }
    }
    catch (...){
        cout<<"Error no definido\n";
    }

}


void regla(){
    /*
    semilla n; //será el tamaño del bloque
    cadena encriptada[mismo tamaño de bin];

    cadena bloque[n]; (?) usar mejor apuntadores??
    bloque = matriz[i];
    para primer bloque:
    invertir(bloque,1)
    funcion invertir(bloque, frecuencia de intercambio)
        for(int i = 0; i<n; i+=frecuencia)
            if( bloque[i] == '1')bloque[i] = '0'
            else bloque[i]=='1'
    condicion:
    funcion contar 1s y 0s
        ingresa bloque
        verifica cada elemento del bloque
        contar 1s y 0s
      comparar y retornar segun sea el caso.
      retornará frecuencia

    invocar invertir()

    */
}

void separar(char ** array2d,char* cad, int nBloques){
    int cont = 0;

    /*int nBloques = size/n; //revisar para par impar
    if(size%n != 0)nBloques++;*/

    //Inicializar la Matriz en 0.
    for(int i = 0; i<nBloques;i++){
        for(int j = 0; j<n;j++ ){
            *(*(array2d+i)+j)='0';
            cont++;
        }
    }
    cont = 0;

    for(int i = 0; i<nBloques;i++){
        for(int j = 0; j<n;j++ ){
            if(*(cad+cont)=='\0')break;
            *(*(array2d+i)+j)=*(cad+cont);
            cont++;
        }

    }
}
int s_real(char* cad, int s){
    /*Conoce tamaño real de la cadena*/
    int tam_real = 0;
    for(int i = 0; i< s;i++){
        if(cad[i] == '\0')break;
        tam_real++;
    }
    return tam_real;
}
void c_bin(char* cad,int tam_real,char* bin){
    /*
      *cad: cadena original
      tam_real: tamaño real de la cadena
      *bin: cadena para guardar binario
    */

    int ltr =0;
    int cont = 7; //contar en que letra voy
    //[...,...,...]
    for(int i = 0; i<tam_real;i++){
        ltr = cad[i];
        int res = 0;
        for(int j = 0; j<8;j++){
            res = ltr%2;
            ltr = ltr/2;

            bin[cont-j] = char(res+48);
        }
        cont+=8;
    }


}
void first_params(char in[], char ou[]){
    /*Usuario ingresa semilla, metodo y nombres de archivos.
    in[]: nombre achivo lectura
    ou[]: nombre archivo escritura
    n y metodo son variables globales, unicas.
    */


    cout << "Ingresa semilla: " << endl;
    cin >> n;
    cout << "Ingresa numero de metodo (1 o 2): " << endl;
    cin >> metodo;

    cout << "Ingrese nombre archivo de entrada: ";
    cin >> in;
    cout << "Ingrese nombre archivo de salida: ";
    cin >> ou;

}

