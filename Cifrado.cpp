#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <windows.h>
#include "inversa.cpp"
#include "modulos.cpp"
#include "pruebaColad.cpp"
#define ascii 437 //Tabla ascii de encriptacion
using namespace std;

//Funciones Principales
Cola* correrc(Cola* palabra, int clave); //Desplaza n caracteres de la tabla ascii a cada letra de la plabra
Cola* encriptP(Cola* palabra, Cola* clave); //Encripta la palabra con una string clave utilizando el metodo de Hill
Cola* desencriptP(Cola* palabra, Cola* clave);
string encriptar(string palabra, int clave1, string clave2); //Junta los dos metodos de encriptación y retorna el string cifrado
string desencriptar(string encriptado, int clave1, string clave2); //Retorna el string descifrado
void crearArchivos(); //Crea los archivos de exportación si aún no existen

//Funciones de Interfaz
void encriptCons();
void desencriptCons();
void encriptArchpr();
void desencriptArchpr();
void encriptArchpe();
void desenciptArchpe();
void leerArchpe();

int main(){
	SetConsoleCP(ascii);
	SetConsoleOutputCP(ascii);
	crearArchivos();
	int opc;
	menu:
		system("Title Sistema de encriptacion de texto");
		system("color f0");
		system("cls");
		cout<<"Menú principal: "<<endl;
		cout<<"Seleccione una opcion: "<<endl;
		cout<<"\t1. Encriptar texto desde la consola"<<endl;
		cout<<"\t2. Desencriptar texto desde la consola"<<endl;
		cout<<"\t3. Encriptar texto desde archivo predeterminado"<<endl;
		cout<<"\t4. Desencriptar texto desde archivo predeterminado"<<endl;
		cout<<"\t5. Encriptar texto desde archivo personalizado"<<endl;
		cout<<"\t6. Desencriptar texto desde archivo personalizado"<<endl;
		cout<<"\t7. Consultar texto almacenado en archivos"<<endl;
		cout<<"\t0. Cerrar programa"<<endl;
		cout<<"\t   Digite una opcion: "; cin>>opc;
		cin.ignore();
		switch (opc){
			case 0:{
				goto end;
				break;
			}
			case 1:{
				system("Title Encriptacion Consola");
				system("cls");
				encriptCons();
				system("PAUSE");
				goto menu;
				break;
			}
			case 2:{
				system("Title Desencriptacion Consola");
				system("cls");
				desencriptCons();
				system("PAUSE");
				goto menu;
				break;
			}
			case 3:{
				system("Title Encriptacion Archivo Predeterminado");
				system("cls");
				encriptArchpr();
				system("PAUSE");
				goto menu;
				break;
			}
			case 4:{
				system("Title Desencriptacion Archivo Predeterminado");
				system("cls");
				desencriptArchpr();
				system("PAUSE");
				goto menu;
				break;
			}
			case 5:{
				system("Title Encriptacion Archivo Personalizado");
				system("cls");
				encriptArchpe();
				system("PAUSE");
				goto menu;
				break;
			}
			case 6:{
				system("Title Desencriptacion Archivo Personalizado");
				system("cls");
				desenciptArchpe();
				system("PAUSE");
				goto menu;
				break;
			}
			case 7:{
				system("Lectura de archivos predeterminados");
				system("cls");
				leerArchpe();
				system("PAUSE");
				goto menu;
				break;
			}
			default:{
				cout<<"Ingrese una opción valida"<<endl;
				goto menu;
				break;
			}
		}
	end:
		return 0;
}

//Funciones
Cola* correrc(Cola* palabra, int clave){
	Cola* Res = new Cola;
	while(!palabra->vacia()){
		int letra = palabra->extraer(); //Obtiene cada letra de la palabra ingresada
			if(letra + clave < 256 && letra + clave >= 32){
				letra = letra + clave; //Desplaza las letra dentro de la tabla ascii
			}
			Res->insertar(letra);
	}
	return Res;//Retorna la cadena en forma de cola
}

Cola* encriptP(Cola* palabra, Cola* clave){
	double raiz = sqrt(clave->length()); //obtiene la raiz de la longitud de la clave para crear una matriz cuadrada
	double dec = (raiz - (int)raiz);
	double red = (1 - dec);
	int cuadrado = 0;
	if(dec > 0){
		cuadrado = raiz + red; //redondea la raiz hacia el numero mayor
	}
	else{
		cuadrado = raiz;
	}
	int **matrizClave = new int*[cuadrado]; //crea un arreglo de punteros con dimension de la matriz cuadrada
	for(int i = 0; i < cuadrado; i++){
		matrizClave[i] = new int[cuadrado]; //crea un arreglo de numeros de la misma dimensión dentro de cada puntero
	}
	
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < cuadrado; j++){
			if(!clave->vacia()){
				int letra = clave->extraer(); //obtiene cada letra de la clave
				matrizClave[j][i] = letra; //almacena cada letra en forma vertical
			}
			else{
				matrizClave[j][i] = 32; //llena los espacios sobrantes con espacios (ASCII : 32)
			}
		}
	}
	/*
	for(int i = 0; i < cuadrado; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizClave[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
	*/
	double div = (double(palabra->length())/double(cuadrado)); //Divide la longitud de la palabra a encriptar entre el tamaño de la matriz clave para que se permita la multiplicacion
	dec = div - int(div);
	red = (1 - dec);
	int col = 0;
	if(dec > 0){
		col = div + red; //redondea al numero mayor
	}
	else{
		col = div;
	}
	int **matrizPal = new int*[col]; //crea un arreglo de punteros con el tamaño de filas obtenidos
	for(int i = 0; i < col; i++){
		matrizPal[i] = new int[cuadrado]; //crea un arreglo de enteros con la misma cantidad de columnas que la matriz clave contiene de filas
	}
	
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < col; j++){
			if(!palabra->vacia()){
				int letra = palabra->extraer(); //obtiene cada letra de la palabra a encriptar
				matrizPal[j][i] = letra; //almacena cada letra en forma de columnas con su equivalente ascii
			}
			else{
				matrizPal[j][i] = 32; //ocupa los espacios restantes con espacios (ASCII : 32)
			}
		}
	}
	/*
	for(int i = 0; i < col; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizPal[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
	*/
	int **matrizRes = new int*[col]; //Crea una nueva matriz resultado del mismo tamaño de la matriz que contiene la palabra
	for(int i = 0; i < col; i++){
		matrizRes[i] = new int[cuadrado];
	}
	for(int k = 0; k < col; k++){
		for(int l = 0; l < cuadrado; l++){
			int cont = 0;
			for(int i = 0; i < cuadrado; i++){
				cont += (matrizPal[k][i] * matrizClave[i][l]); //Realiza la multiplicacion entre las dos matrices
			}
			matrizRes[k][l] = cont;
		}
	}
	
	Cola* res = new Cola;
	for(int i = 0; i < col; i++){
		for(int j = 0; j < cuadrado; j++){
			matrizRes[i][j] = (matrizRes[i][j]%223) + 32; //Halla el modulo del resultado entre los 223 caracteres comprendidos entre 32 y 255, luego suma 32 para evitar los caracteres no imprimibles
			res->insertar(matrizRes[i][j]); //Guarda en la nueva cola cada elemento de la matriz encriptada
		}
	}
	/*
	for(int i = 0; i < col; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizRes[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	*/
	delete []*matrizPal;
	delete []*matrizRes;
	delete []*matrizClave; //Libera la mamoria de las matrices utlizadas
	return res; //Retorna la cola de la cadena encriptada
}

Cola* desencriptP(Cola* palabra, Cola* clave){
	double raiz = sqrt(clave->length()); //obtiene la raiz de la longitud de la clave para crear una matriz cuadrada
	double dec = (raiz - (int)raiz);
	double red = (1 - dec);
	int cuadrado = 0;
	if(dec > 0){
		cuadrado = raiz + red; //redondea el valor de la raiz hacia el numero mayor
	}
	else{
		cuadrado = raiz;
	}
	double **matrizClave = new double*[cuadrado]; //Crea dos matrices cuadradas para almacenar la matriz clave y su inversa
	double **matrizinv = new double*[cuadrado];
	for(int i = 0; i < cuadrado; i++){
		matrizClave[i] = new double[cuadrado];
		matrizinv[i] = new double[cuadrado];
	}
	
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < cuadrado; j++){
			if(!clave->vacia()){
				int letra = clave->extraer(); //obtiene cada caracter de la palabra clave
				matrizClave[j][i] = letra; //Almacena cada caracter de manera vertical en su forma equivalente ascii
			}
			else{
				matrizClave[j][i] = 32; //Llena el restante de la matriz con espacios (ASCII : 32)
			}
		}
	}
	/*
	for(int i = 0; i < cuadrado; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizClave[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
	*/
	double det = determin(matrizClave, cuadrado); //Halla el determinante de la matriz clave
	//cout<<invmod(det, 223)<<endl;
	matadj(matrizClave, matrizinv, cuadrado); //Halla la matriz adjunta de la matriz clave
	mattra(matrizinv, matrizClave, cuadrado); //Transpone la matriz adjunta
	for(int i = 0; i < cuadrado; i++){
		//cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			matrizClave[i][j] = matrizClave[i][j] * invmod(det,223); //Calcula el inverso modular de la matriz clave, luego lo multiplica por cada elemento de la matriz adjunta transpuesta
			//cout<<matrizClave[i][j]<<" ";
		}
		//cout<<" ]"<<endl;
	}
	//cout<<endl;
	/*
	for(int i = 0; i < cuadrado; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			matrizClave[i][j] = modulo(matrizClave[i][j], 223);
			cout<<matrizClave[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
	*/
	double div = (double(palabra->length())/double(cuadrado)); //Calcula la cantidad de filas necesarias para que la matriz palabra sea multplicable
	dec = div - int(div);
	red = (1 - dec);
	int col = 0;
	if(dec > 0){
		col = div + red;//Redondea hacia el numero mayor
	}
	else{
		col = div;
	}
	double **matrizPal = new double*[col]; //Crea la matriz para almacenar la palabra encriptada
	for(int i = 0; i < col; i++){
		matrizPal[i] = new double[cuadrado];
	}
	
	for(int i = 0; i < col; i++){
		for(int j = 0; j < cuadrado; j++){
			if(!palabra->vacia()){
				int letra = palabra->extraer(); //obtiene cada caracter de la palabra encriptada
				matrizPal[i][j] = letra; //almacena su equivalente ascii 
				if(matrizPal[i][j] < 0){
					matrizPal[i][j] = matrizPal[i][j] + 256; //convierte los caracteres negativos propios de c++ en su equivalente ascii 
				}
				matrizPal[i][j] = matrizPal[i][j] - 32; 
			}
			else{
				matrizPal[i][j] = 32; //rellena el resto de la matriz con espacios (ASCII : 32)
			}
		}
	}
	/*
	for(int i = 0; i < col; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizPal[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	cout<<endl;
	*/
	double **matrizRes = new double*[col]; //Crea una matriz resultado de igual dimension que la matriz que almacena la palabra encriptada
	for(int i = 0; i < col; i++){
		matrizRes[i] = new double[cuadrado];
	}
	for(int k = 0; k < col; k++){
		for(int l = 0; l < cuadrado; l++){
			double contd = 0;
			for(int i = 0; i < cuadrado; i++){
				contd += (matrizPal[k][i] * matrizClave[i][l]); //Multiplica la matriz encriptada por la matriz modular inversa clave
			}
			matrizRes[k][l] = contd;
			matrizRes[k][l] = modulo(matrizRes[k][l], 223); //Halla el modulo de la matriz resultado, obteniendo la matriz de la palabra desencriptda
		}
	}
	Cola* res = new Cola;
	/*
	for(int i = 0; i < col; i++){
		cout<<"[ ";
		for(int j = 0; j < cuadrado; j++){
			cout<<matrizRes[i][j]<<" ";
		}
		cout<<" ]"<<endl;
	}
	*/
	for(int i=0; i < cuadrado; i++){
		for(int j = 0; j < col; j++){
			int letra = int(round(matrizRes[j][i])); //obtiene cada letra de la matriz resultado
			res->insertar(letra); //Almacena en la cola resultado cada caracter
		}
	}
	delete []*matrizinv;
	delete []*matrizPal;
	delete []*matrizRes;
	delete []*matrizClave;
	return res; //Retorna la cola desencriptada
}

string encriptar(string palabra, int clave1, string clave2){
	Cola* pal = new Cola;
	Cola* cla = new Cola; 
	Cola* aux = new Cola;
	pal->strTocola(palabra);
	cla->strTocola(clave2);
	string resultado; //Crea una nueva cadena para retornar la cadena encriptada
	aux = correrc(pal, clave1); //Realiza la encriptación corriendo caracteres
	if(cla->length() > 1){
		aux = encriptP(aux, cla); //Encripta la palabra con el corrimiento de caracteres usando la clave
	}
	else{
		cout<<"La clave debe contener mas de un caracter"<<endl;
		delete pal;
		delete cla;
		delete aux;
		return "";
	}
	resultado = aux->colaTostr();
	delete pal;
	delete cla;
	delete aux;
	return resultado; //Retorna la palabra encriptada
}

string desencriptar(string encriptado, int clave1, string clave2){
	Cola* enc = new Cola;
	Cola* cla = new Cola;
	Cola* aux = new Cola;
	enc->strTocola(encriptado);
	cla->strTocola(clave2);
	string resultado; //Crea una nueva cadena para retornar la cadena desencriptada
	if(cla->length() > 1){
		aux = desencriptP(enc, cla); //Desencripta la palabra usando la misma clave que se usó para encriptar
	}
	else{
		cout<<"La clave debe contener mas de un caracter"<<endl;
		delete enc;
		delete cla;
		delete aux;
		return "";
	}
	aux = correrc(aux, -1 * clave1); //Realiza la desencriptación retrocediendo la misma cantidad de caracteres que al inicio
	resultado = aux->colaTostr();
	delete enc;
	delete cla;
	delete aux;
	return resultado; //Retorna la cadena desencriptada
}

void crearArchivos(){ //Crea los archivos necesarios si aun no existen
	ifstream entrada;
	ofstream salida;
	entrada.open("encriptacion.txt", ios::in);
	if(entrada.fail()){
		entrada.close();
		salida.open("encriptacion.txt", ios::out);
		salida.close();
	}
	entrada.open("desencriptacion.txt", ios::in);
	if(entrada.fail()){
		entrada.close();
		salida.open("desencriptacion.txt", ios::out);
		salida.close();
	}
}

//Funciones interfaz

void encriptCons(){
	string palabra, clave, encriptado;
	int num, opc;
	cout<<"Ingrese la palabra a encriptar: "; getline(cin, palabra, '\n');
	cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
	cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
	encriptado = encriptar(palabra, num, clave);
	archivo:	
		if(encriptado != ""){
			cout<<"Palabra encriptada: "<<encriptado<<endl;
			cout<<"Desea almacenar el resultado en el archivo? (0: No, 1: Si): "; cin>>opc;
			if(opc == 0){
				cout<<"Volviendo a pagina principal"<<endl;
			}
			else if(opc == 1){
				ofstream salida;
				salida.open("encriptacion.txt", ios::out);
				salida<<encriptado<<endl;
				cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
				salida.close();
			}
			else{
				cout<<"Ingrese una opcion valida"<<endl;
				goto archivo;	
			}
		}
}

void desencriptCons(){
	string palabra, clave, encriptado;
	int num, opc;
	cout<<"Ingrese la palabra a desencriptar: "; getline(cin, encriptado, '\n');
	cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
	cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
	palabra = desencriptar(encriptado, num, clave);
	archivo:
		if(palabra != ""){
			cout<<"Palabra desencriptada: "<<palabra<<endl;
			cout<<"Desea almacenar el resultado en el archivo? (0: No, 1: Si): "; cin>>opc;
			if(opc == 0){
				cout<<"Volviendo a pagina principal"<<endl;
			}
			else if(opc == 1){
				ofstream salida;
				salida.open("desencriptacion.txt", ios::out);
				salida<<palabra<<endl;
				cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
				salida.close();
			}
			else{
				cout<<"Ingrese una opcion valida"<<endl;
				goto archivo;	
			}
		}
}

void encriptArchpr(){
	string palabra, clave, encriptado;
	int num, opc;
	ifstream entrada;
	entrada.open("desencriptacion.txt", ios::in);
	getline(entrada, palabra, '\n');
	cout<<"Se encriptará la palabra almacenada en 'desencriptacion.txt': "<<palabra<<endl;
	cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
	cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
	encriptado = encriptar(palabra, num, clave);
	archivo:	
		if(encriptado != ""){
			cout<<"Palabra encriptada: "<<encriptado<<endl;
			cout<<"Desea almacenar el resultado en el archivo? (0: No, 1: Si): "; cin>>opc;
			if(opc == 0){
				cout<<"Volviendo a pagina principal"<<endl;
			}
			else if(opc == 1){
				ofstream salida;
				salida.open("encriptacion.txt", ios::out);
				salida<<encriptado<<endl;
				cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
				salida.close();
			}
			else{
				cout<<"Ingrese una opcion valida"<<endl;
				goto archivo;	
			}
		}
	entrada.close();
}

void desencriptArchpr(){
	string palabra, clave, encriptado;
	int num, opc;
	ifstream entrada;
	entrada.open("encriptacion.txt", ios::in);
	getline(entrada, encriptado, '\n');
	cout<<"Se encriptará la palabra almacenada en 'encriptacion.txt': "<<encriptado<<endl;
	cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
	cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
	palabra = desencriptar(encriptado, num, clave);
	archivo:
		if(palabra != ""){
			cout<<"Palabra desencriptada: "<<palabra<<endl;
			cout<<"Desea almacenar el resultado en el archivo? (0: No, 1: Si): "; cin>>opc;
			if(opc == 0){
				cout<<"Volviendo a pagina principal"<<endl;
			}
			else if(opc == 1){
				ofstream salida;
				salida.open("desencriptacion.txt", ios::out);
				salida<<palabra<<endl;
				cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
				salida.close();
			}
			else{
				cout<<"Ingrese una opcion valida"<<endl;
				goto archivo;	
			}
		}
	entrada.close();
}

void encriptArchpe(){
	string texto = "", clave, encriptado, extension = ".txt", narchivo, linea;
	int num, opc;
	cout<<"Ingrese el nombre del archivo txt a encriptar: ";
	getline(cin, narchivo, '\n');
	narchivo = narchivo + extension;
	cout<<"Archivo: "<<narchivo<<endl;
	ifstream entrada(narchivo.c_str());
	if(entrada.fail()){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		cout<<"Leyendo contenido del archivo "<<narchivo;
		while(!entrada.eof()){
			cout<<".";
			getline(entrada, linea, '\n');
			texto += linea;
			texto += " ";
		}
		texto.erase(texto.end() - 1);
		cout<<endl<<"Contenido leido: "<<texto<<endl;
		cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
		cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
		encriptado = encriptar(texto, num, clave);
		archivo:	
			if(encriptado != ""){
				cout<<"Palabra encriptada: "<<encriptado<<endl;
				cout<<"Desea almacenar el resultado en el archivo predeterminado? (0: No, 1: Si): "; cin>>opc;
				if(opc == 0){
					cout<<"Volviendo a pagina principal"<<endl;
				}
				else if(opc == 1){
					ofstream salida;
					salida.open("encriptacion.txt", ios::out);
					salida<<encriptado<<endl;
					cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
					salida.close();
				}
				else{
					cout<<"Ingrese una opcion valida"<<endl;
					goto archivo;	
				}
			}
		entrada.close();
	}
}

void desenciptArchpe(){
	string texto, clave, encriptado = "", extension = ".txt", narchivo, linea;
	int num, opc;
	cout<<"Ingrese el nombre del archivo txt a desencriptar: ";
	getline(cin, narchivo, '\n');
	narchivo = narchivo + extension;
	cout<<"Archivo: "<<narchivo<<endl;
	ifstream entrada(narchivo.c_str());
	if(entrada.fail()){
		cout<<"El archivo no existe"<<endl;
	}
	else{
		cout<<"Leyendo contenido del archivo "<<narchivo;
		while(!entrada.eof()){
			cout<<".";
			getline(entrada, linea, '\n');
			encriptado += linea;
			encriptado += " ";
		}
		encriptado.erase(encriptado.end() - 1);
		cout<<endl<<"Contenido leido: "<<encriptado<<endl;
		cout<<"Ingrese la clave de encriptacion: "; getline(cin, clave, '\n');
		cout<<"Ingrese la clave numerica de encriptacion: "; cin>>num;
		texto = desencriptar(encriptado, num, clave);
		archivo:	
			if(texto != ""){
				cout<<"Palabra desencriptada: "<<texto<<endl;
				cout<<"Desea almacenar el resultado en el archivo predeterminado? (0: No, 1: Si): "; cin>>opc;
				if(opc == 0){
					cout<<"Volviendo a pagina principal"<<endl;
				}
				else if(opc == 1){
					ofstream salida;
					salida.open("desencriptacion.txt", ios::out);
					salida<<encriptado<<endl;
					cout<<"Guardado correctamente, volviendo al menu principal"<<endl;
					salida.close();
				}
				else{
					cout<<"Ingrese una opcion valida"<<endl;
					goto archivo;	
				}
			}
	}
	entrada.close();
}

void leerArchpe(){
	ifstream entradaE;
	ifstream entradaD;
	string E, D;
	entradaE.open("encriptacion.txt", ios::in);
	entradaD.open("desencriptacion.txt", ios::in);
	getline(entradaE, E, '\n');
	getline(entradaD, D, '\n');
	cout<<"Texto de archivo de encriptacion: "<<E<<endl<<endl;
	cout<<"Texto de archivo de desencriptacion: "<<D<<endl;
}
