/****************************************
	Proyecto encriptación con matrices
	Juan Carlos Clavijo Triviño
	Juan Sebastían Carvajal Cardenas
	2023 - Estructuras de datos
****************************************/

#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include "inversa.cpp"
#include "modulos.cpp"
using namespace std;

string correrc(string palabra, int clave); //Desplaza n caracteres de la tabla ascii a cada letra de la plabra
string encriptP(string palabra, string clave); //Encripta la palabra con una string clave utilizando el metodo de Hill
string desencriptP(string palabra, string clave);
string encriptar(string palabra, int clave1, string clave2); //Junta los dos metodos de encriptación y retorna el string cifrado
string desencriptar(string encriptado, int clave1, string clave2); //Retorna el string descifrado

int main(){
	string palabra;
	cout<<"Ingrese la palabra a encriptar: ";
	getline(cin, palabra, '\n');
	string clavepal;
	cout<<"Ingrese la palabra clave: ";
	getline(cin, clavepal, '\n');
	int clavenum;
	cout<<"Ingrese la clave numerica: ";
	cin>>clavenum;
	string enc = encriptar(palabra, clavenum, clavepal);
	cout<<endl<<enc<<endl;
	string des = desencriptar(enc, clavenum, clavepal);
	cout<<endl<<"Palabra desencriptada: "<<des<<endl;
}

//Funciones

string correrc(string palabra, int clave){
	string resultado = "";
	for(int i=0; i <= palabra.length(); i++){
		char letra = palabra[i]; //Obtiene cada letra de la palabra ingresada
		if(letra >= 'a' && letra <= 'z'){ 
			if(letra + clave < 256 && letra + clave > 0){
				letra = letra + clave; //Desplaza las letra dentro de la tabla ascii (Mantiene los simbolos)
			}
		}
		else if (letra >= 'A' && letra <= 'Z'){
			if(letra + clave < 256 && letra + clave > 0){
				letra = letra + clave;
			}
		}
		resultado += letra; //Almacena cada letra en una nueva cadena
	}
	return resultado; //Retorna la cadena
}

string encriptP(string palabra, string clave){
	double raiz = sqrt(clave.length()); //obtiene la raiz de la longitud de la clave para crear una matriz cuadrada
	double dec = (raiz - (int)raiz);
	double red = (1 - dec);
	int cuadrado = 0;
	if(dec > 0){
		cuadrado = raiz + red; //redondea la raiz hacia el numero mayor
	}
	else{
		cuadrado = raiz;
	}
	double **matrizClave = new double*[cuadrado]; //crea un arreglo de punteros con dimension de la matriz cuadrada
	for(int i = 0; i < cuadrado; i++){
		matrizClave[i] = new double[cuadrado]; //crea un arreglo de numeros de la misma dimensión dentro de cada puntero
	}
	int cont = 0;
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < cuadrado; j++){
			if(cont < clave.length()){
				char letra = clave[cont]; //obtiene cada letra de la clave
				matrizClave[j][i] = letra; //almacena cada letra en forma vertical
			}
			else{
				matrizClave[j][i] = ' '; //llena los espacios sobrantes con espacios (ASCII : 32)
			}
			cont++;
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
	double div = (double(palabra.length())/double(cuadrado)); //Divide la longitud de la palabra a encriptar entre el tamaño de la matriz clave para que se permita la multiplicacion
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
	cont = 0;
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < col; j++){
			if(cont < palabra.length()){
				char letra = palabra[cont]; //obtiene cada letra de la palabra a encriptar
				matrizPal[j][i] = letra; //almacena cada letra en forma de columnas con su equivalente ascii
			}
			else{
				matrizPal[j][i] = ' '; //ocupa los espacios restantes con espacios (ASCII : 32)
			}
			cont++;
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
			cont = 0;
			for(int i = 0; i < cuadrado; i++){
				cont += (matrizPal[k][i] * matrizClave[i][l]); //Realiza la multiplicacion entre las dos matrices
			}
			matrizRes[k][l] = cont;
		}
	}
	string res = "";
	for(int i = 0; i < col; i++){
		for(int j = 0; j < cuadrado; j++){
			matrizRes[i][j] = (matrizRes[i][j]%223) + 32; //Halla el modulo del resultado entre los 223 caracteres comprendidos entre 32 y 255, luego suma 32 para evitar los caracteres no imprimibles
			res += matrizRes[i][j]; //Guarda en la nueva cadena cada elemento de la matriz encriptada
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
	return res; //Retorna la cadena encriptada
}

string desencriptP(string palabra, string clave){
	double raiz = sqrt(clave.length()); //obtiene la raiz de la longitud de la clave para crear una matriz cuadrada
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
	int cont = 0;
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < cuadrado; j++){
			if(cont < clave.length()){
				char letra = clave[cont]; //obtiene cada caracter de la palabra clave
				matrizClave[j][i] = letra; //Almacena cada caracter de manera vertical en su forma equivalente ascii
			}
			else{
				matrizClave[j][i] = ' '; //Llena el restante de la matriz con espacios (ASCII : 32)
			}
			cont++;
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
	double div = (double(palabra.length())/double(cuadrado)); //Calcula la cantidad de filas necesarias para que la matriz palabra sea multplicable
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
	cont = 0;
	/*
	for(int i = 0; i < cuadrado; i++){
		for(int j = 0; j < col; j++){
			if(cont < palabra.length()){
				char letra = palabra[cont];
				matrizPal[j][i] = letra;
				if(matrizPal[j][i] < 0){
					matrizPal[j][i] = matrizPal[j][i] + 256;
				}
			}
			else{
				matrizPal[j][i] = ' ';
			}
			cont++;
		}
	}*/
	for(int i = 0; i < col; i++){
		for(int j = 0; j < cuadrado; j++){
			if(cont < palabra.length()){
				char letra = palabra[cont]; //obtiene cada caracter de la palabra encriptada
				matrizPal[i][j] = letra; //almacena su equivalente ascii 
				if(matrizPal[i][j] < 0){
					matrizPal[i][j] = matrizPal[i][j] + 256; //convierte los caracteres negativos propios de c++ en su equivalente ascii 
				}
				matrizPal[i][j] = matrizPal[i][j] - 32; 
			}
			else{
				matrizPal[i][j] = ' '; //rellena el resto de la matriz con espacios (ASCII : 32)
			}
			cont++;
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
	string res = "";
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
			char letra = char(round(matrizRes[j][i])); //obtiene cada letra de la matriz resultado
			res += letra; //Almacena en el string resultado cada caracter
		}
	}
	delete []*matrizinv;
	delete []*matrizPal;
	delete []*matrizRes;
	delete []*matrizClave;
	return res; //Retorna la cadena desencriptada
}

string encriptar(string palabra, int clave1, string clave2){
	string resultado = ""; //Crea una nueva cadena para retornar la cadena encriptada
	resultado = correrc(palabra, clave1); //Realiza la encriptación corriendo caracteres
	resultado = encriptP(resultado, clave2); //Encripta la palabra con el corrimiento de caracteres usando la clave
	return resultado; //Retorna la palabra encriptada
}

string desencriptar(string encriptado, int clave1, string clave2){
	string resultado = ""; //Crea una nueva cadena para retornar la cadena desencriptada
	resultado = desencriptP(encriptado, clave2); //Desencripta la palabra usando la misma clave que se usó para encriptar
	resultado = correrc(resultado, -1 * clave1); //Realiza la desencriptación retrocediendo la misma cantidad de caracteres que al inicio
	return resultado; //Retorna la cadena desencriptada
}
