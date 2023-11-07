#include <iostream>
#include <math.h>
using namespace std;

double determin(double **matp, int r){
	double dete = 0;
	if(r == 2){
		double pos = 1;
		double neg = -1;
		for(int i = 0; i < r; i++){
			for(int j = 0; j < r; j++){
				if(i == j){
					pos = pos * matp[i][j];
				}
				else{
					neg = neg * matp[i][j];
				}
			}
		}
		dete = pos + neg;
	}
	else{
		double **mataux = new double*[r-1];
		for(int i = 0; i < r-1; i++){
			mataux[i] = new double[r-1];
		}
		double mult = 0;
		double aux = 0;
		for(int i = 0; i < r; i++){
			mult = matp[0][i];
			for(int j = 1; j < r; j++){
				for(int k = 0; k < r; k++){
					if(k < i){
						mataux[j-1][k] = matp[j][k];
					}
					else if(k > i){
						mataux[j-1][k-1] = matp[j][k];
					}
				}
			}
			aux = mult * determin(mataux, r-1);
			dete += pow(-1, (i+2)) * aux;
		}
		delete []*mataux;
	}
	return dete;
}

void matadj(double **matinput, double **matoutput, int r){
	double **mataux = new double*[r-1];
	for(int i=0; i < r-1; i++){
		mataux[i] = new double[r-1];
	}
	for(int i = 0; i < r; i++){
		for(int j = 0; j < r; j++){
			for(int l = 0; l < r; l++){
				for(int k = 0; k < r; k++){
					if(l < i){
						if(k < j){
							mataux[l][k] = matinput[l][k];
							//cout<<l<<", "<<k<<": "<<matinput[l][k]<<" ";
						}
						else if(k > j){
							mataux[l][k-1] = matinput[l][k];
							//cout<<l<<", "<<k<<": "<<matinput[l][k]<<" ";
						}
					}
					else if(l > i){
						if(k < j){
							//cout<<"C3: ";
							mataux[l-1][k] = matinput[l][k];
							//cout<<l<<", "<<k<<": "<<matinput[l][k]<<" ";
							//cout<<l-1<<", "<<k<<": "<<mataux[l-1][k]<<"|";
						}
						else if(k > j){
							//cout<<"C4: ";
							mataux[l-1][k-1] = matinput[l][k];
							//cout<<l<<", "<<k<<": "<<matinput[l][k]<<" ";
							//cout<<l-1<<", "<<k-1<<": "<<mataux[l-1][k-1]<<"|";
						}
					}
				}
			}
			if(r > 2){
				matoutput[i][j] = pow(-1, (2 + (i + j))) * determin(mataux, (r - 1));
			}
			else{
				matoutput[i][j] = pow(-1, (2 + (i + j))) * mataux[0][0];
			}
		}
	}
	delete []*mataux;
}

void mattra(double **matp, double **mato, int r){
	for(int i = 0; i < r; i++){
		for(int j = 0; j < r; j++){
			mato[i][j] = matp[j][i];
		}
	}
}

void matinv(double **matp, double **mato, int n){
	double det = determin(matp, n);
	cout<<det<<endl;
	double **matc = new double*[n];
	for(int i=0; i<n; i++){
		matc[i] = new double[n];
	}
	matadj(matp, matc, n);
	double **matt = new double*[n];
	for(int i=0; i<n; i++){
		matt[i] = new double[n];
	}
	mattra(matc, matt, n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mato[i][j] = (matt[i][j] / det);
		}
	}
	delete []*matt;
	delete []*matc;
}
/*
int main(){
	const int n = 4;
	double **matp = new double*[n];
	for(int i=0; i<n; i++){
		matp[i] = new double[n];
	}
	matp[0][0] = 1;
	matp[0][1] = -2;
	matp[0][2] = 2;
	matp[0][3] = 2;
	matp[1][0] = 0;
	matp[1][1] = 4;
	matp[1][2] = -2;
	matp[1][3] = 1;
	matp[2][0] = 1;
	matp[2][1] = -2;
	matp[2][2] = 4;
	matp[2][3] = 0;
	matp[3][0] = 1;
	matp[3][1] = -1;
	matp[3][2] = 2;
	matp[3][3] = 2;
	double **mato = new double*[n];
	for(int i=0; i<n; i++){
		mato[i] = new double[n];
	}
	matinv(matp, mato, n);
	for(int i = 0; i < n; i++){
		cout<<"[";
		for(int j = 0; j < n; j++){
			cout<<mato[i][j]<<", ";
		}
		cout<<"]"<<endl;
	}
	delete []*matp;
	delete []*mato;
}
*/
