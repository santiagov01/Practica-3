#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int n; //semilla
int metodo;
void first_params();
string c_bin(string cad, int tam_real,int nBloques);
char bin_to_char(string binario);
void invertir(string*actual, int freq,int semilla,string *pegar,int *cont);
int contarbins(string anterior, int semilla);
//string encripting(string binario,int nBloques,int *cont);
void lectura(string nf_ouput,string nf_input);
string decode(string binario,int nBloques, string pegar,int *cont);
string decode2(string binario,int nBloques, string pegar);
int main()
{
    string nf_input, nf_output;//nombre archivos
    first_params(); //semilla, metodo, nombre archivos
    lectura(nf_output,nf_input);
    return 0;
}
string decode(string binario,int nBloques, string pegar,int *cont){
    string anterior;
    string actual;
    int semilla = n;
    int c = 0;
    for(int i = 0; i<n;i++){
        //pegar.append("0");
        anterior.append("0");
        actual.append("0");
    }
    //for(int z = 0; z<(nBloques*semilla);z++)pegar.append("0"); //inicializa cadena en 0.
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
        invertir(&actual,contarbins(anterior,semilla),semilla,&pegar,cont);
        for(int j=0;j<semilla;j++){
            anterior[j]= pegar[j-semilla+(*cont)];//actualiza anterior
        }

    }
    return pegar;

}
string decode2(string binario,int nBloques, string pegar){
    string temporal;
    string actual;
    int semilla = n;
    int c = 0;
    int c2 = 0;
    for(int i = 0; i<n;i++){
        //pegar.append("0");
        temporal.append("0");
        actual.append("0");
    }


    for(int k = 0;k<nBloques;k++){
        for(int i = 0; i<semilla;i++){
            temporal[i]=binario[c2];
            c2++;
        }
        actual[n-1]=temporal[0];
        for(int j = 0;j<n-1;j++){
            actual[j] = temporal[j+1];
        }
        for(int i = 0; i<n;i++){
            pegar[c]=actual[i];
            //cout << pegar[c];
            c++;
        }

    }
    return pegar;
}
void lectura(string nf_ouput,string nf_input){
    string bin_linea;
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
            getline(fin,bin_linea); //Lee linea y la guarda en string
            tam_cad = bin_linea.length();//longitud real de cada linea
            if(tam_cad>0){
                nBloques = tam_cad/n;
                int cont = 0;
                string pegar,temp= "00000000";
                string u = "11111111"; string cer = "00000000";
                int aux = 0;
                for(int i = 0; i<n*nBloques;i++)pegar.append("0");
                switch (metodo) {
                case 1:
                    pegar = decode(bin_linea,nBloques, pegar,&cont);
                    aux = 0;
                    for(int j = 0;j<tam_cad/8;j++){
                        for(int c = 0; c<8;c++){
                            temp[c]=pegar[aux];
                            aux++;
                        }
                        if(!(temp==u||temp==cer))//los ceros o unos de relleno
                            fout<< bin_to_char(temp);
                    }
                    break;
                case 2:
                    pegar = decode2(bin_linea,nBloques, pegar);
                    aux = 0;
                    for(int j = 0;j<tam_cad/8;j++){
                        for(int c = 0; c<8;c++){
                            temp[c]=pegar[aux];
                            aux++;
                        }
                        if(!(temp==u||temp==cer))//los ceros o unos de relleno
                            fout<< bin_to_char(temp);
                    }
                    break;
                default:
                    cout << "Debes ingresar el método correcto. ";
                    break;
                }

            }
        }else{
            for(int c = 0; c<=saltos;c++){
                // REVISAR CUANDO SEMILLA > TAM CAD*8
                getline(fin,bin_linea); //Lee linea y la guarda en string
                tam_cad = bin_linea.length();//longitud real de cada linea
                if(tam_cad>0){
                    nBloques = tam_cad/n;
                    int cont = 0;
                    string pegar,temp= "00000000";
                    string u = "11111111"; string cer = "00000000";
                    int aux = 0;
                    for(int i = 0; i<n*nBloques;i++)pegar.append("0");
                    switch (metodo) {
                    case 1:
                        pegar = decode(bin_linea,nBloques, pegar,&cont);
                        aux = 0;
                        for(int j = 0;j<tam_cad/8;j++){
                            for(int c = 0; c<8;c++){
                                temp[c]=pegar[aux];
                                aux++;
                            }
                            if(!(temp==u||temp==cer))//los ceros o unos de relleno
                                fout<< bin_to_char(temp);
                        }
                        break;
                    case 2:
                        pegar = decode2(bin_linea,nBloques, pegar);
                        aux = 0;
                        for(int j = 0;j<tam_cad/8;j++){
                            for(int c = 0; c<8;c++){
                                temp[c]=pegar[aux];
                                aux++;
                            }
                            if(!(temp==u||temp==cer))//los ceros o unos de relleno
                                fout<< bin_to_char(temp);
                        }
                        break;
                    default:
                        cout << "Debes ingresar el método correcto. ";
                        break;
                    }

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
char bin_to_char(string binario) {
    int decimal = 0, base = 1;
    for (int i = 7; i >= 0; i--) {
        if (binario[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return (char)decimal;
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

void first_params(){
    /*Usuario ingresa semilla, metodo y nombres de archivos.
    n y metodo son variables globales, unicas.
    */


    cout << "Ingresa semilla: " << endl;
    cin >> n;
    cout << "Ingresa numero de metodo (1 o 2): " << endl;
    cin >> metodo;


}
