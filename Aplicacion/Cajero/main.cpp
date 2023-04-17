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
void escribir_usuarios(char*);
string leer_sudo();
void saltos();
void lista_texto();
void split(char* cadena,char**subcadenas,char sep, int nf);
int len_char (char *p);

bool validar_user();
bool compare(char* a, char* b);
void concatenar(char*,char*,char*,char*);
void consultar_saldo(char **data, char ced[], int saltos);
void retirar_dinero();
bool verificar_cedula(char[]);
void intostr(int num, char *punter);
int matoi(char array[], int s);
int saltoschar();
void actualizar_usuarios(char** pegar,int saltos);
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
        cin >> opc;
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
    char pegar[74];
    cout << "Ingresa cedula del usuario: " << endl;
    cin >> ced;
    if(!verificar_cedula(ced)){
        //leer_usuarios(ced);
        cout << "Ingresa clave del usuario: " << endl;
        cin >> clave;
        cout << "Ingresa saldo del usuario: " << endl;
        cin >> saldo;
        concatenar(ced,clave,saldo,pegar);
        escribir_usuarios(pegar);
    }
}
bool verificar_cedula(char cedula[]){
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
        char **lista_individual = new char* [3];

        for(int i = 0; i<3; i++){
            lista_individual[i] = new char[32];
        }

        for(int i = 0; i<(saltos+1);i++){
            fin.getline(cadena,32);
            split(cadena,lista_individual,';',3);
            if(compare(cedula,lista_individual[0]))return true;//la cedula es la misma(ya existe)
        }
        for(int i = 0; i<3;i++)delete[] lista_individual[i];
        delete[] lista_individual;
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
    return false;
}
void escribir_usuarios(char* pegar){
    /*Guardar en una matriz la infromación de cursos
    */
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    char name_file[10] = "users.txt";//Solo será de lectura
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
        char **lista_usuarios = new char* [saltos+1];
        for(int i = 0; i<saltos+1; i++){
            lista_usuarios[i] = new char[32];
        }

        fin.open(name_file);
        if(!fin.is_open()){
            throw '2';
        }
        for(int i = 0; i<(saltos+1);i++){
            fin.getline(lista_usuarios[i],20);//guardar en una lista
        }
        fin.close();
        //ahora lo abre como escritura
        fout.open(name_file);
        if(!fout.is_open()){
            throw '1';
        }
        for(int i = 0; i<(saltos+1);i++){
            fout << lista_usuarios[i] <<endl;//pega cada linea
        }
        fout << pegar;//añade la nueva

        for(int i = 0; i<saltos+1;i++)delete[] lista_usuarios[i];
        delete[] lista_usuarios;

    }
    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='1'){
            cout<<"Error al abrir el archivo para escritura.\n";
        }
        cout<<"Error # "<<c<<": ";
        if(c=='2'){
            cout<<"Error al abrir el archivo para lectura.\n";
        }
    }
    catch (...){
        cout<<"Error no definido\n";
    }
}
string leer_sudo(){
    string clave_decof;
    //Leer archivo y decodificar
    return clave_decof;
}
bool validar_user(char *cedula,char *clave, char**data){
    //VALIDA CEDULA Y CLAVE
    //Ademas guarda los datos en una matriz para poder actualizarlos luego

    char cadena[64];
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;
    bool state = false;//stream de salida, escritura
    char name_file[32] = "users.txt";//Solo será de lectura
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
        for(int i = 0; i<saltos+1;i++){
            data[i]= new char[64];
        }
        fin.open(name_file);
        if(!fin.is_open()){
            throw '2';
        }


        for(int i = 0; i<(saltos+1);i++){
            fin.getline(cadena,64);
            char **lista_individual = new char* [3];
            for(int i = 0; i<3; i++){
                lista_individual[i] = new char[64];
            }

            int cont = 0;
            for (int j = 0; j < len_char(cadena); j++) {
                *(*(data+i)+cont)= *(cadena+j);
                cont++;
            }

            *(*(data+i)+cont) = '\0';

            split(cadena,lista_individual,';',3);
            //comparar cedula
            if(compare(cedula,lista_individual[0])&&compare(clave,lista_individual[1])){
                state = true;
            }
            for(int i = 0; i<3;i++)delete[] lista_individual[i];
            delete[] lista_individual;
        }

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
    return state;
}
void consultar_saldo(char **data, char ced[], int saltos){

    for(int i = 0; i<saltos+1;i++){
        char clave[32] =" ";
        char saldo[32] = " ";
        char pegar[74] = " ";
        char **lista_individual = new char* [3];
        for(int j = 0; j<3; j++){
            lista_individual[j] = new char[32];
        }
        split(data[i],lista_individual,';',3);
        if(compare(ced,lista_individual[0])){
            for(int c = 0; c< len_char(lista_individual[1]);c++){
                clave[c] = lista_individual[1][c];
            }
            for(int c = 0; c< len_char(lista_individual[2]);c++){
                saldo[c] = lista_individual[2][c];
            }
            int saldo_copy = matoi(saldo,len_char(saldo));
            saldo_copy =saldo_copy-1000;
            char aux_saldo[32]="";

            intostr(saldo_copy,aux_saldo);


            concatenar(ced,clave,aux_saldo,pegar);
            //Actualizar lista
            for(int m = 0; m<len_char(pegar);m++){
                data[i][m] = pegar[m];
            }
            cout << "Su saldo es: $";
            cout << saldo_copy;
            break;
        }
        for(int i = 0; i<3;i++){
            delete[] lista_individual[i];
            }
        delete[] lista_individual;

    }
}

void menu_user(){
    char ced[20]=" ";
    char  clave[32]= " ";
    int saltos = saltoschar();
    char **data= new char*[saltos+1];
    cout << "Ingresa cedula: " << endl;
    cin >> ced;
    cout << "Ingresa clave: " << endl;
    cin >> clave;
    if(validar_user(ced,clave,data)){
        cout << "Usuario correcto" << endl;
        int opc = 0;
        while(opc!=-1){
            cout << "Ingresa opcion(-1 para salir):\n1.Consultar Saldo\n2.Retirar Dinero" <<endl;
            switch (opc) {
            case 1:
                consultar_saldo(data, ced,saltos);
                break;
            case 2:
                retirar_dinero();
                break;
            default:
                break;
            }
        }

    }else cout << "No se pudo acceder";

    for(int i = 0; i<saltos+1;i++)delete[] data[i];
    delete[] data;
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


    char cadena[20];
    ifstream fin;
    ofstream fout;
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
bool compare(char a[], char b[]){
    int t1 = len_char(a);
    int t2 = len_char(b);
    if(t1 == t2){ //Hace falta verificar tamaño
        for(int i =0; i<t1; i++){
            if((a[i]) != (b[i])){ //Si el caracter correspondiente es
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}
int saltoschar(){
    ifstream fin;
    //Pedir nombre del archivo o abrir con nombre existente
    char name_file[32] = "users.txt";
    int saltos = 0;
    try{

        fin.open(name_file);        //abre el archivo para lectura
        if(!fin.is_open()){
            throw '2';
        }

        while(fin.good()){ //lee caracter a caracter hasta el fin del archivo
            char temp=fin.get();
            if(fin.good()){
                if(temp == '\n'){
                    saltos++;//contar saltos de linea (cantidad cursos)
                }
            }
        }
        fin.close();
        return saltos;
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
    return 1;
}
int matoi(char array[], int s){
    int signo = 1;
    int num = 0;

    int iterar = 0;

    if(array[iterar]=='-'){
        iterar++;
        signo = -1;
    }//

    for(; iterar < s; iterar++){
        // e.g => 430 + 2
        num = num*10 + int(array[iterar]- '0');
    }

    return signo*num;

}
void intostr(int num, char *punter){
    int dig = 0;
    int N;
    int aux =0;
    int lim = 0;

    if(num < 0 ){
        *(punter) = '-';
        num = -num;
        lim = 1;
        dig++;

    }
    N=num;
    while(N!=0){
        N/=10;
        dig++;
    }
    for(int i = dig-1; i>=lim;i--){
       aux = num%10;
       *(punter + i) = char(aux + 48);
       num/=10;
    }
    cout << "aux: " << aux<<endl;
    if(aux==0){
        *(punter) = '0';
        *(punter+1) = '\0';
    }
}
void actualizar_usuarios(char** pegar, int saltos){

    ofstream fout;              //stream de salida, escritura
    char name_file[10] = "users.txt";//Solo será de lectura
    //Se supone que el archivo ya está creado (así sea vacio)

    try{
        //ahora lo abre como escritura
        fout.open(name_file);
        if(!fout.is_open()){
            throw '1';
        }
        for(int i = 0; i<(saltos+1);i++){
            fout << pegar[i] <<endl;//pega cada linea
        }


    }
    catch (char c){
        cout<<"Error # "<<c<<": ";
        if(c=='1'){
            cout<<"Error al abrir el archivo para escritura.\n";
        }
    }
    catch (...){
        cout<<"Error no definido\n";
    }
}
