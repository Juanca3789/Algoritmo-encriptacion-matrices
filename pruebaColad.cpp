#include <iostream>
#include <string>
using namespace std;

class Cola{
	private:
		class Nodo{
			public:
				int info;
				Nodo* sig;
		};
	Nodo* inicio;
	Nodo* fin;
	public:
		Cola();
		~Cola();
		int length();
		bool vacia();
		void insertar(int elemento);
		int extraer();
		void imprimir();
		void strTocola(string pal);
		string colaTostr();
};

Cola::Cola(){
	inicio = NULL;
	fin = NULL;
}

Cola::~Cola(){
	Nodo* recorrido = inicio;
	Nodo* eliminar;
	while (recorrido != NULL){
		eliminar = recorrido;
		recorrido = recorrido->sig;
		delete eliminar;
	}
}

int Cola::length(){
	int num = 0;
	Nodo* recorrido = inicio;
	while (recorrido != NULL){
		num++;
		recorrido = recorrido->sig;
	}
	return num;
}

bool Cola::vacia(){
	if(inicio == NULL){
		return true;
	}
	else{
		return false;
	}
}

void Cola::insertar(int elemento){
	Nodo* nuevo;
	nuevo = new Nodo;
	if(elemento < 0){
		elemento = elemento + 256;
	}
	nuevo->info = elemento;
	if(vacia()){
		inicio = nuevo;
	}
	else{
		fin->sig = nuevo;
	}
	nuevo->sig = NULL;
	fin = nuevo;
}

int Cola::extraer(){
	if(!vacia()){
		int elemento;
		Nodo* extraido;
		extraido = inicio;
		inicio = inicio->sig;
		elemento = extraido->info;
		delete extraido;
		return elemento;
	}
}

void Cola::imprimir(){
	if(!vacia()){
		cout<<"[ ";
		Nodo* recorrido;
		recorrido = inicio;
		while(recorrido != NULL){
			cout<<recorrido->info<<" ";
			recorrido = recorrido->sig;
		}
		cout<<"] ";
	}
	else{
		cout<<"Vacia"<<endl;
	}
}

void Cola::strTocola(string pal){
	for(int i = 0; i < int(pal.length()); i++){
		char letra = pal[i];
		int num = int(letra);
		insertar(num);
	}
}

string Cola::colaTostr(){
	if(!vacia()){
		Nodo* recorrido;
		recorrido = inicio;
		string resultado = "";
		while(recorrido != NULL){
			recorrido = recorrido->sig;
			resultado += extraer();
		}
		return resultado;
	}
}
