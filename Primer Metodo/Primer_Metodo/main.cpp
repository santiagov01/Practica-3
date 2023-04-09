#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int n = 0;
int metodo = 0;

int s_real(char*,int);
void c_bin(char*,int,char*);
void first_params(char[],char[]);
void archivo_r_w(char[], char[], char[], int, char*, int *tam_cad);

void separar(char **, char*, int);

bool compare(char* a, char* b); //Función para comparar si las cadenas de caracteres son iguales.
int main()
{
    char nf_input[32]=" ", nf_output[32]=" ";//nombre archivos
    char c_original[64] =" "; //cadena original
    char bin[64*8]="0";
    int nBloques = 0;
    int tam_cad = 0;
    char **matrix;



    first_params(nf_input,nf_output); //semilla, metodo, nombre archivos
    archivo_r_w(nf_output,nf_input,c_original,sizeof(c_original),bin,&tam_cad);
    nBloques = tam_cad*8/n; //revisar para par impar

    if(tam_cad%n != 0)nBloques++;
    cout << "tamanio bloques: " << nBloques;
    matrix = new char* [nBloques];
    for(int i = 0; i<nBloques; i++){
        matrix[i] = new char[n];
    }
    separar(matrix,bin,nBloques);


    /*
    cout << "Visualizacion matriz: \n";
    for(int i = 0; i < nBloques; i++){
        for(int j = 0; j< n; j++){
            cout << *(*(matrix+i)+j) << " ";
        }
        cout << endl;
    }*/

    for(int i = 0; i<nBloques;i++)delete[] matrix[i];
    delete[] matrix;
    return 0;
}
void archivo_r_w(char nf_output[],char nf_input[],char c_original[],int s,char*bin, int *tam_cad){
    /*Manipulacion archivo*/
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    try{
    //Lectura
        fin.open(nf_input);        //abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }

        //leer linea del archivo y guardar en variable.
        fin.getline(c_original,64);
        fin.seekg(0);

        //tamaño real cadena original

        *tam_cad = s_real(c_original,s);



        /*char* bin;
        bin = new char[64*8];*/
        //*(bin+(64*8)-1)='\0';

        //convertir a texto binario
        c_bin(c_original,*tam_cad,bin);
        fin.close();
    //Escritura
        fout.open(nf_output);       //abre el archivo para escritura
        if(!fout.is_open()){
            throw '1';
        }
        fout<<bin;                     //escribe la palabra
        fout.close();
        //delete [] bin;
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

bool compare(char* a, char* b){
    unsigned int i;
    bool out = true;
    for(i=0;a[i]!=0 && b[i]!=0;i++){
        if(a[i]!=b[i]){
            out =  false;
        }
    }
    return out;
}
