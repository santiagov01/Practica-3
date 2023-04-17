#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int n = 4;
int metodo = 0;
void invertir(char[],int,int,char[],int*); //bloque y frecuencia/condicion para invertir
int contarbins(char[],int semilla);
void encripting(char[], int, char*, int *cont);
void encript2(char binario[],int nBloques, char*pegar);
int s_real(char*,int);
void c_bin(char*,int,char*,int);
void first_params(char[],char[]);




void lectura(char *nf_ouput, char *nf_input, char* c_original, int size_cad);


int main()
{
    char nf_input[64]=" ", nf_output[64]=" ";//nombre archivos
    first_params(nf_input,nf_output); //semilla, metodo, nombre archivos

    char c_original[256] =" "; //cadena original



    lectura(nf_output,nf_input,c_original,sizeof(c_original));

    return 0;
}
void invertir(char actual[], int freq,int semilla,char *pegar,int *cont){

    if(!(freq>semilla)){
        if(freq ==0){
            for(int i = 0;i<semilla;i++){
                if(actual[i]=='1'){
                    pegar[*cont]='0';

                }else{
                    pegar[*cont] = '1';

                }
                (*cont)++;

            }
        }else{
            int m = 1;
            for(int i = 0;i<semilla;i++){
                if(i == (freq*m)-1){
                    if(actual[i]=='1'){
                        pegar[*cont]='0';

                    }
                    else{
                        pegar[*cont]='1';

                    }
                    m++;
                }else{
                    pegar[*cont]= actual[i];

                }
                (*cont)++;


            }
        }

    }else{
        for(int i = 0;i<semilla;i++){
            pegar[*cont]=actual[i];
            (*cont)++;
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
void encripting(char binario[],int nBloques, char*pegar,int *cont){
    /*Hace reglas del primer metodo
    Se regresa cadena codificada "pegar" por referencia*/

    char *anterior= new char [n];
    char *actual = new char [n];

    int semilla = n;
    int c = 0;
    for(int z = 0; z<(nBloques*semilla);z++)pegar[z]='0'; //inicializa cadena en 0.
    //para el primer bloque
    for(int i = 0; i<semilla;i++){
        anterior[i]=binario[i];
        if(binario[i]=='0'){
            pegar[*cont] = '1';

        }else{

            pegar[*cont]='0';
        }
        (*cont)++;//me dice en que posición va.
    }
    //para el resto de bloques
    c = *cont; //variable auxiliar
    for(int i = 1; i<nBloques;i++){
        for(int j=0;j<semilla;j++){
            actual[j]= binario[c];//actualiza bloque actual
            c++;
        }
        //hacer operacion
        invertir(actual,contarbins(anterior,semilla),semilla,pegar,cont);
        for(int j=0;j<semilla;j++){
            anterior[j]= actual[j];//actualiza anterior
        }

    }

    delete[] actual;
    delete[] anterior;
}
void encript2(char binario[],int nBloques, char*pegar){
    char *temporal= new char [n]; //debe ser de la cadena a pegar
    char *actual = new char [n];

    int semilla = n;
    int c = 0;
    int c2 = 0;
    for(int z = 0; z<(nBloques*semilla);z++)pegar[z]='0'; //inicializa cadena en 0.
    //para el primer bloque
    for(int k = 0;k<nBloques;k++){
        for(int i = 0; i<semilla;i++){
            temporal[i]=binario[c2];
            c2++;
        }
        actual[0]=temporal[n-1];
        for(int j = 0;j<n-1;j++){
            actual[j+1] = temporal[j];
        }
        for(int i = 0; i<n;i++){
            pegar[c]=actual[i];

            c++;
        }

    }

    delete[] actual;
    delete[] temporal;
}
void lectura(char *nf_ouput,char *nf_input, char* cad_linea, int size_cad){
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    int nBloques = 0;
    int tam_cad = 0;
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

        fout.open(nf_ouput);
        if(!fout.is_open()){
            throw '1';
        }
        if(saltos == 0){
            fin.getline(cad_linea,256); //leer linea del archivo y guardar en variable.
            tam_cad = s_real(cad_linea,size_cad);//longitud real de cada linea
            if(tam_cad>0){

                nBloques = tam_cad*8/n;
                if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
                char pegar[nBloques*n];
                int cont = 0;
                char bin[nBloques*n];
                c_bin(cad_linea,tam_cad,bin,nBloques);//convierte cade a binario


                switch (metodo) {
                case 1:
                    encripting(bin,nBloques,pegar,&cont);
                    break;
                case 2:
                    encript2(bin,nBloques, pegar);
                    break;
                default:
                    cout << "Debes ingresar el método correcto. ";
                    break;
                }
                for(int z = 0; z<nBloques*n;z++){
                    fout << pegar[z];
                }
            }
        }else{
            for(int c = 0; c<=saltos;c++){
                // REVISAR CUANDO SEMILLA > TAM CAD*8

                fin.getline(cad_linea,256);//extrae linea a linea.
                tam_cad = s_real(cad_linea,size_cad);//longitud real de cada linea

                if(tam_cad>0){
                    int cont = 0;
                    nBloques = tam_cad*8/n;
                    if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
                    char bin[tam_cad*8];
                    char pegar[nBloques*n];
                    c_bin(cad_linea,tam_cad,bin,nBloques);
                    switch (metodo) {
                    case 1:
                        encripting(bin,nBloques,pegar,&cont);
                        break;
                    case 2:
                        encript2(bin,nBloques, pegar);
                        break;
                    default:
                        cout << "Debes ingresar el método correcto. ";
                        break;
                    }

                    for(int z = 0; z<nBloques*n;z++){
                        fout << pegar[z];
                    }

                    fout << '\n';
                }

            }

        }


        fout.close();
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

int s_real(char* cad, int s){
    /*Conoce tamaño real de la cadena*/
    int tam_real = 0;
    for(int i = 0; i< s;i++){
        if(cad[i] == '\0')break;
        tam_real++;
    }
    return tam_real;
}
void c_bin(char* cad,int tam_real,char* bin,int nBloques){
    /*
      *cad: cadena original
      tam_real: tamaño real de la cadena
      *bin: cadena para guardar binario
    */
    for(int i = 0; i<nBloques*n;i++){
        bin[i]= '0';
    }
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

