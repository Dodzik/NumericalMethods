#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "gaussj.c"

#define PI 3.14159

#define x_min  -5.f
#define x_max  5.f
#define alpha 0.f
#define betha 0.f

void printf_matrix(float** dummy, int x, int y){
	printf("\n");
	for (int i = 1; i<= x ; i++){
		for (int j = 1; j <= y; j++){
			printf("%.3f ",dummy[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void printf_vector(float* dummy, int n){
	printf("\n");
	for (int i = 1; i<= n ; i++){
		printf("%.3f ",dummy[i]);
		
	}
	printf("\n");
}

void fillZerosVector(float* v, int n) {
  for (int i = 1; i <= n; ++i)
    v[i] = 0.f;
}

void fillZerosMatrix(float** M, int n, int m) {
  for (int i = 1; i <= n; ++i)
    fillZerosVector(M[i], m);
}

void wyzM(float *xw,float *yw, float *w, int n, float alfa, float beta){
	float **A = matrix(1,n,1,n);
	float **d = matrix(1,n,1,1);
	fillZerosMatrix(A,n,n);
	fillZerosMatrix(d,n,1);

	A[1][1] = 1.f;
	A[n][n] = 1.f;
  	A[1][2] = 0.f;
  	A[n][n-1] = 0.f;
	float lambda, my, di;
	float h = (x_max - x_min) / (n - 1);

	for (int i = 2; i < n; ++i) {
   		lambda = h / (h + h);
   		my = 1 - lambda;
   		di = 6/(h + h) * ((yw[i+1] - yw[i])/h - (yw[i] - yw[i-1])/h);
   		A[i][i] = 2;
   		A[i][i-1] = my;
   		A[i][i+1] = lambda;
   		d[i][1] = di;
  	}

	gaussj(A,n,d,1);

	for (int i=2;i<n;i++){
		w[i] = d[i][2];
	}
	free_matrix(A, 1, n, 1, n);
  	free_matrix(d, 1, n, 1, 1);
}



float wyzSx(float *xw,float *yw, float *m, int n, float x){
	int q =1;
	for (int i =2;i<=n ;++i){
		if(xw[i-1] <= x && x <= xw[i]){
			 q=i;
		}
		float h = (x_max - x_min) / (n - 1);
		float A = (yw[q] - yw[q-1])/h - h/6 * (m[q] - m[q-1]);
		float B = yw[q-1] - m[q-1]*h*h/6;
		float sx = m[q-1] * pow(xw[q] -x ,3)/(6*h) + m[q] * pow(x - xw[q-1],3)/(6-h) + A*(x-xw[q-1])+ B;
		return sx;
	}

}

void print(float* xw,float* yw,float* m,float q,float p,int n,float x,FILE* fp){
	for (float step = q; step<= p; step += x){
		fprintf(fp,"%f %f\n",step , wyzSx(xw,yw,m,n,step));

	}
	fprintf(fp,"\n\n");
	FILE *fp3;
	fp3=fopen("pochodne.dat","w");
	
	print_derative(xw,yw,m,q,p,10,x,fp3);

	fclose(fp3);

}


void interpolate(float (*fun)(float), float q, float p, int n,FILE* fp){
	float* xw = vector(1, n);
  	float* yw = vector(1, n);
  	float* m = vector(1, n);
	float x=0.01;
	
	float h = (p - q) / (n - 1);

	xw[1] = x_min;
  	xw[n] = x_max;
  	yw[1] = fun(x_min);
  	yw[n] = fun(x_max);
	for (int i = 2; i < n; ++i){
		xw[i] = x_min + (i-1)*h;
		yw[i] = fun(xw[i]);
	}
	wyzM(xw,yw,m,n,alpha,betha);

	print(xw,yw,m,q,p,n,x,fp);

	free_vector(xw, 1, n);
	free_vector(yw, 1, n);
	free_vector(m, 1, n);
}

float fun1 (float x){
	return 1/(1 + x * x);
}

float fun2(float x) {
	return cos(2*x); 
}

float derivative2nd(float (*fun)(float), float x, float dx) {
  return (fun(x - dx) - 2*fun(x) + fun(x + dx)) / (dx*dx);
}

void print_derative(float* xw,float* yw,float* m,float q,float p,int n,float x,FILE* fp){
	for (int i = 1; i <= n; ++i){

   		fprintf(fp,"%f  %f  %f\n", xw[i], m[i], derivative2nd(fun1, xw[i], 0.01));
	}
  	fprintf(fp,"\n\n");

	
}



int main(void) {

	int table_n[3] ={5,8,21};
	float (*fun)(float)=fun1;
	FILE *fp;
	fp=fopen("f1.dat","w");
	for (int i =0 ; i<3;i++){
		interpolate(fun,x_min,x_max,table_n[i],fp);
	}
	fclose(fp);

	float (*fun5)(float)=fun2;
	FILE *fp2;
	fp2=fopen("f2.dat","w");
	
	for (int i =0 ; i<3;i++){
		interpolate(fun5,x_min,x_max,table_n[i],fp2);
	}
	fclose(fp2);
	
}