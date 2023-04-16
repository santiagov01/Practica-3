#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void menu_admin();
void menu_general();
void menu_user();
void menu_init();
void menu_registrar();
bool comparar_claves(string clave);// Tal vez

void decodificar();
void leer_usuarios(char cedula[]);
void escribir_usuarios();
string leer_sudo();
void saltos();
void lista_texto();
void split(char* cadena,char**subcadenas,char sep, int nf);
int len_char (char *p);

bool ingresar();
bool compare(char* a, char* b);
void concatenar();
void consultar_saldo();
void retirar_dinero();
int main()
{
    menu_general();
    return 0;
}
void menu_general(){
    int opc = 0;

    while(opc!= -1){
        cout << "Ingresa opción: (Pulse -1 para salir)" <<endl;
        cout << "1. Ingresar como admin \n2. Ingresar como usuario.";
        switch (opc) {
        case 1:
            menu_admin();
            break;
        case 2:
            menu_user();
            break;
        default:
            break;
        }
    }

}
void menu_admin(){
    //char clave[64]="0";
    string clave;
    cout << "Ingresa tu clave: ";
    getline(cin,clave);
    if(clave==leer_sudo()){
        menu_registrar();
    }else cout << "ACCESO DENEGADO!!!" << endl;


}

void menu_registrar(){
    char ced[10];
    char clave[32];
    char saldo[32];
    cout << "Ingresa cedula del usuario: " << endl;
    cin >> ced;


    leer_usuarios(ced);
    escribir_usuarios();
}
string leer_sudo(){
    string clave_decof;
    //Leer archivo y decodificar
    return clave_decof;
}


void menu_users(){
    if(ingresar()){
        cout << "Usuario correcto" << endl;
        int opc = 0;
        while(opc!=-1){
            cout << "Ingresa opcion:\n1.Consultar Saldo\n2.Retirar Dinero" <<endl;
            switch (opc) {
            case 1:
                consultar_saldo();
                break;
            case 2:
                retirar_dinero();
                break;
            default:
                break;
            }
        }

    }else cout << "No se pudo acceder";
}
int len_char (char *p){
    int longitud=0;
    while(p[longitud]!= '\0'){
        longitud++;
    }
    return longitud;
}
void split(char* cadena,char**subcadenas,char sep, int nf){
    //Cadena: Cadena char a "formatear"
    //Subcadenas: Matriz 2 dimensiones que contiene cada dato como arreglo char
    //sep: caracter que representa la separación ';' '-' etc
    //nf: Cantidad de filas que tendrá la matriz.
    //Por ejemplo, al guardar cedula, clave, saldo
    int l = len_char(cadena);
    int c = -1;
    for(int i = 0; i<nf;i++){
        int j = 0;
        c++;
        while(cadena[c]!=sep){
            if(c==l) break;//verifica si recorre toda la cadena
            subcadenas[i][j]=cadena[c];
            j++;
            c++;//copia caracter a caracter en la matriz
        }
        subcadenas[i][j]= '\0';
    }
}
void concatenar(char *a,char*b,char*c,char*unir){
    int sep = 2;
    int dim = len_char(a)+len_char(b)+len_char(c)+sep;
    char* concatenado = new char[dim];
    int cont = 0;
    for(int i = 0;i<len_char(a);i++){
        *(concatenado + cont) = *(a+i);
        cont++;
    }
    *(concatenado+cont)=';';
    cont++;
    for(int i = 0;i<len_char(b);i++){
        *(concatenado + cont) = *(b+i);
        cont++;
    }
    *(concatenado+cont)=';';
    cont++;
    for(int i = 0;i<len_char(c);i++){
        *(concatenado + cont) = *(c+i);
        cont++;
    }
    for(int i = 0; i<dim;i++){
        *(unir+i)= *(concatenado+i);
    }
    delete[] concatenado;

}
void leer_usuarios(char cedula[])
{
    /*Guardar en una matriz la infromación de cursos
    */

    char cadena[20];
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    char name_file[64] = "users.txt";//Solo será de lectura
    //Se supone que el archivo ya está creado (así sea vacio)

    try{

        fin.open(name_file);//abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }
        int saltos = 0;

        while(fin.good()){ //lee caracter a caracter hasta el fin del archivo
            char temp=fin.get();
            if(fin.good()){
                if(temp == '\n'){
                    saltos++;//contar saltos de linea (cantidad cursos)
                }
            }
        }
        fin.close();
        fin.open(name_file);
        if(!fin.is_open()){
            throw '2';
        }
        for(int i = 0; i<(saltos+1);i++){
            fin.getline(cadena,20);

            //convertir/formatear cadena a matriz(lista de arreglos char)

        }

    /*
        int i=0;
        while(fin.good()){              //lee caracter a caracter hasta el fin del archivo
            char temp=fin.get();
            if(fin.good()){
                cadena2[i]=temp;     //Asigna cada caracter leido a la cadena de caracteres
            }
            i++;
        }*/
        fin.close();                //Cierra el archivo de lectura.


    }
    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='2'){
            cout<<"Error al abrir el archivo para escritura.\n";
        }
    }
    catch (...){
        cout<<"Error no definido\n";
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
