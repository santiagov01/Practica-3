#include <iostream>
#include <fstream>
using namespace std;

int n;
int metodo;
void lectura(char *nf_ouput, char *nf_input, char* bin_linea, int size_cad);
void bin_to_char(char* cadena);
void decode(char binario[],int nBloques, char*pegar,int *cont);
void invertir(char actual[], int freq,int semilla,char *pegar,int *cont);
int contarbins(char anterior[], int semilla);
void first_params(char[],char[]);
int s_real(char* cad, int s);
int main()
{
    char nf_input[64]=" ", nf_output[64]=" ";//nombre archivos
    first_params(nf_input,nf_output); //semilla, metodo, nombre archivos
    char bin_linea[256*8] =" "; //cadena original


    lectura(nf_output,nf_input,bin_linea,sizeof(bin_linea));

    return 0;
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
        for(int i = 0;i<semilla;i++){//cuando semilla = 2, freq =3
            //Queda igual
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
void decode(char binario[],int nBloques, char*pegar,int *cont){
    char *anterior= new char [n]; //debe ser de la cadena a pegar
    char *actual = new char [n];

    int semilla = n;
    int c = 0;
    for(int z = 0; z<(nBloques*semilla);z++)pegar[z]='0'; //inicializa cadena en 0.
    //para el primer bloque
    for(int i = 0; i<semilla;i++){
        //anterior[i]=binario[i];
        if(binario[i]=='0'){
            pegar[*cont] = '1';
        }else{
            pegar[*cont]='0';
        }
        (*cont)++;//me dice en que posición va.
        anterior[i]=pegar[i];
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
            anterior[j]= pegar[j-semilla+(*cont)];//actualiza anterior
        }

    }

    delete[] actual;
    delete[] anterior;
}
void lectura(char *nf_ouput,char *nf_input, char* bin_linea, int size_cad){
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
            fin.getline(bin_linea,256);//extrae linea a linea.
            tam_cad = s_real(bin_linea,size_cad);//longitud real de cada linea

            if(tam_cad>0){
                int cont = 0;
                nBloques = tam_cad/n;
                char pegar[nBloques*n];
                //c_bin(cad_linea,tam_cad,bin,nBloques);
                switch (metodo) {
                case 1:
                    decode(bin_linea,nBloques,pegar,&cont);
                    break;
                case 2:

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

                fin.getline(bin_linea,256);//extrae linea a linea.
                tam_cad = s_real(bin_linea,size_cad);//longitud real de cada linea

                if(tam_cad>0){
                    int cont = 0;
                    nBloques = tam_cad/n;
                    char pegar[nBloques*n];
                    //c_bin(cad_linea,tam_cad,bin,nBloques);
                    switch (metodo) {
                    case 1:
                        decode(bin_linea,nBloques,pegar,&cont);
                        break;
                    case 2:

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
