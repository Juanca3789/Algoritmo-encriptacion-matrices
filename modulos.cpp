#include <iostream>
#include <math.h>
using namespace std;

double modulo(double a, double b){
	if(a >= 0){
		int entero;
		double mult;
		double res;
		double div = a/b;
		entero = int(a/b);
		mult = double(entero);
		res = div - mult;
		res = res * b;
		return res;
	}
	else{
		double res;
		double mult = 0;
		int cont = 0;
		while(a < mult){
			cont++;
			mult = -1.0 * b;
			mult = mult * cont;
		}
		res = mult - a;
		res = -1 * res;
		return res;
	}
}

double invmod(double a, double b){
	double mod = modulo(a, b);
	//cout<<mod<<endl;
	double cont = 0;
	double acc = mod * cont;
	for(cont = 0; cont < b; cont++){
		acc = mod * cont;
		double v = round(modulo(acc, b));
		if(v == 1){
			break;
		}
	}
	return double(cont);
}

/*
int main(){
	double r = invmod(-5004, 223);
	cout<<r;
}
*/
