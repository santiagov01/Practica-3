#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
int n = 0;
int metodo = 0;
void c_bin(char*);
void first_params(char[],char[]);
bool compare(char* a, char* b); //Función para comparar si las cadenas de caracteres son iguales.
int main()
{
    char nf_input[32]=" ", nf_output[32]=" ";
    char c_original[64] =" "; //cadena original
    char *c_encript = NULL;
    c_encript = new char[256]; //apuntador a cadena encriptada.
    //Tamaño dinamico

    first_params(nf_input,nf_output); //semilla, metodo, nombre archivos


    /**/
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    try{
        fout.open(nf_output);       //abre el archivo para escritura
        if(!fout.is_open()){
            throw '1';
        }

        fin.open(nf_input);        //abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }


        fin.getline(c_original,64); //leer linea del archivo y guardar en variable.
        fin.seekg(0);
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



    //cin.getline(cadena1, sizeof(cadena1));      //lee una cadena con espacios



    /**/
    /*
    char cadena1[15], cadena2[15], cadena3[15];
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura

    cout<<"Ingrese una palabra: ";
    cin>>cadena1;                          //lee una cadena sin espacios

    //cin.getline(cadena1, sizeof(cadena1));      //lee una cadena con espacios

    try{
        fout.open("archivo2.txt");       //abre el archivo para escritura
        if(!fout.is_open()){
            throw '1';
        }
        fout<<cadena1;                     //escribe la palabra
        fout.close();                   //cierra el archivo

        fin.open("archivo2.txt");        //abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }



        fin.getline(cadena3,15);           //lee una linea y la almacena en cadena3

        fin.seekg(0);                   //vuelve al principio del archivo

        int i=0;
        while(fin.good()){              //lee caracter a caracter hasta el fin del archivo
            char temp=fin.get();
            if(fin.good()){
                cadena2[i]=temp;     //Asigna cada caracter leido a la cadena de caracteres
            }
            i++;
        }
        fin.close();                //Cierra el archivo de lectura.


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

    if(compare(cadena1, cadena2) && compare(cadena1, cadena3))
        cout<<"Funciona!!!!\n";
    else
        cout<<"Error en la lectura de los datos!!!!\n";

    */
    delete[] c_encript;
    return 0;
}
void first_params(char in[], char ou[]){
    //Usuario ingresa semilla, metodo y nombres de archivos.


    cout << "Ingresa semilla: " << endl;
    cin >> n;
    cout << "Ingresa numero de metodo (1 o 2): " << endl;
    cin >> metodo;

    cout << "Ingrese nombre archivo de entrada: ";
    cin >> in;
    cout << "Ingrese nombre archivo de salida: ";
    cin >> ou;

}
void c_bin(char *msg){
    int ltr =0;
    char bin;
    for(int i = 0; i<26;i++){
        ltr = msg[i];
        for(int j = 0; j<8;j++){

        }
    }
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
