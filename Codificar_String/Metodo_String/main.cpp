#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int n; //semilla
int metodo;
void first_params();
string c_bin(string cad, int tam_real,int nBloques);
void invertir(string*actual, int freq,int semilla,string *pegar,int *cont);
int contarbins(string anterior, int semilla);
string encripting(string binario,int nBloques,int *cont);
void lectura(string nf_ouput,string nf_input);
int main(){
    string nf_input, nf_output;//nombre archivos
    first_params(); //semilla, metodo, nombre archivos
    lectura(nf_output,nf_input);
    return 0;
}




int contarbins(string ant ,int semilla){
    string anterior = ant;
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
string c_bin(string cad, int tam_real,int nBloques){
    /*
      *cad: cadena original
      tam_real: tamaño real de la cadena
      *bin: cadena para guardar binario
    */
    string bin;
    for(int i = 0; i<nBloques*n;i++){
        bin+= '0';
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
    return bin;

}
void invertir(string* actual_, int freq,int semilla,string *pegar_,int *cont){
    string copia_actual = *actual_;
    string copia_pegar = *pegar_;
    string aux = "0";
    if(!(freq>semilla)){
        if(freq ==0){
            for(int i = 0;i<semilla;i++){
                if(copia_actual[i]=='1'){
                    copia_pegar[*cont] = '0';

                }else{
                    copia_pegar[*cont] = '1';
                }
                (*cont)++;

            }
        }else{
            int m = 1;
            for(int i = 0;i<semilla;i++){
                if(i == (freq*m)-1){
                    if(copia_actual[i]=='1'){
                        copia_pegar[*cont] = '0';

                    }else{
                        copia_pegar[*cont] = '1';
                    }
                    m++;
                }else{
                    aux = copia_actual[i];
                    copia_pegar = copia_pegar.replace(*cont,1,aux);

                }
                (*cont)++;


            }
        }

    }else{
        for(int i = 0;i<semilla;i++){
            aux = copia_actual[i];
            copia_pegar = copia_pegar.replace(*cont,1,aux);
            (*cont)++;
        }
    }
    *pegar_ = copia_pegar;

}
string encripting(string bin,int nBloques,int *cont){
    //char *anterior= new char [n];
    //char *actual = new char [n];
    string binario = bin;
    string pegar;
    string anterior;
    string actual;
    for(int i = 0; i<n;i++){
        pegar.append("0");
        anterior.append("0");
        actual.append("0");
    }

    int semilla = n;
    int c = 0;
    for(int z = 0; z<(nBloques-1)*semilla;z++)pegar.append("0"); //inicializa cadena en 0.
    //para el primer bloque
    for(int i = 0; i<semilla;i++){
        anterior[i]=binario[i];
        if(binario[i]=='0'){
            pegar[*cont] = '1';

        }else{

            pegar[*cont] = '0';
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
        invertir(&actual,contarbins(anterior,semilla),semilla,&pegar,cont);
        for(int j=0;j<semilla;j++){
            anterior[j]= actual[j];//actualiza anterior
        }
    }

    return pegar;
}

void lectura(string nf_ouput,string nf_input){
    string cad_linea;
    ifstream fin;               //stream de entrada, lectura
    ofstream fout;              //stream de salida, escritura
    int nBloques = 0;
    int tam_cad = 0;
    cout << "Ingrese nombre archivo de entrada: ";
    cin >> nf_input;
    cout << "Ingrese nombre archivo de salida: ";
    cin >> nf_ouput;
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
            getline(fin,cad_linea); //leer linea del archivo y guardar en variable.
            tam_cad = cad_linea.length();//longitud real de cada linea
            if(tam_cad>0){
                nBloques = tam_cad*8/n;
                if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
                int cont = 0;
                string pegar,bin;
                for(int i = 0; i<n*nBloques;i++)pegar.append("0");

                bin=c_bin(cad_linea,tam_cad,nBloques);
                string copybin = bin;//convierte cade a binario


                switch (metodo) {
                case 1:
                    pegar = encripting(copybin,nBloques,&cont);
                    break;
                case 2:

                    break;
                default:
                    cout << "Debes ingresar el método correcto. ";
                    break;
                }
                fout << pegar;

                //cout << pegar<<endl;
            }
        }else{
            for(int c = 0; c<=saltos;c++){
                // REVISAR CUANDO SEMILLA > TAM CAD*8

                    getline(fin,cad_linea); //leer linea del archivo y guardar en variable.
                    tam_cad = cad_linea.length();//longitud real de cada linea
                    if(tam_cad>0){
                        nBloques = tam_cad*8/n;
                        if(tam_cad*8%n != 0)nBloques++;//revisa division exacta
                        int cont = 0;
                        string pegar,bin;
                        for(int i = 0; i<n*nBloques;i++)pegar.append("0");

                        bin=c_bin(cad_linea,tam_cad,nBloques);
                        string copybin = bin;//convierte cade a binario


                        switch (metodo) {
                        case 1:
                            pegar = encripting(copybin,nBloques,&cont);
                            break;
                        case 2:

                            break;
                        default:
                            cout << "Debes ingresar el método correcto. ";
                            break;
                        }
                        fout << pegar;

                        cout << pegar;
                    }

                    fout << '\n';


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
void first_params(){
    /*Usuario ingresa semilla, metodo y nombres de archivos.
    n y metodo son variables globales, unicas.
    */


    cout << "Ingresa semilla: " << endl;
    cin >> n;
    cout << "Ingresa numero de metodo (1 o 2): " << endl;
    cin >> metodo;


}
