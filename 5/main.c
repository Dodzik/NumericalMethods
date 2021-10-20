#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "tred2.c"
#include "tqli.c"

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

float dot(float* x,float*y, int n){
	float tmp = 0;
	for(int i = 1;i <= n;i++) {
		tmp= tmp + x[i] * y[i]; 
	}
	return tmp;
}
void nor_vector(float* v,int n){
	float nor = sqrt(fabs(dot(v,v,n)));
	for (int i = 1;i <= n; i++){
		v[i] = v[i]/nor;
	}
}

void copy_vector (float* v, float *v_clone, int n) {
	for (int i=1;i<=n;i++){
		v_clone[i]=v[i];
	}
}

float fun(float* v1 , float** W,float*v0,int n){
	for(int i = 1; i<=n;i++){
		v1[i] = dot(W[i],v0,n);
		// printf("%.3f\n",v1[i]);
	}
}
void reduction(float **W,float lamb,float* x,int n){
	for(int i =1; i<=n; i++){
		for(int j = 1;j <=n; j++){
			W[i][j]=W[i][j] -(lamb * x[i]*x[j]);
		}
	}
}

int main(void) {
	FILE *fp;
	fp=fopen("dane.dat","w");
	int n = 7;
	float lamb=0;


	float** A = matrix(1,n,1,n);
	float** W = matrix(1,n,1,n);

	float* d = vector(1,n);
	float* e = vector(1,n);

	float*v0 = vector(1,n);
	float*v1 = vector(1,n);
	for (int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			A[i][j]=sqrt(i+j);
			W[i][j]=sqrt(i+j);
		}
	}
	printf_matrix(A,n,n);

	tred2(A,n,d,e);

	tqli(d,e,n,A);

	printf_matrix(A,n,n);
	printf_matrix(W,n,n);
	fprintf(fp,"Wartości własne: \n");
	for (int q = 1 ; q<=n; q++){
		for(int i = 0; i<=n;i++){
			v0[i] =1;
			
		}
		for (int j=1; j<=8;j++){
			
			fun(v1,W,v0,n);
			lamb = dot(v1,v0,n)/dot(v0,v0,n);
			nor_vector(v1,n);
			copy_vector(v1,v0,n);
			}
			fprintf(fp,"\n");
			reduction(W,lamb,v0,n);
			printf("%.7ef\n",lamb);
			fprintf(fp,"%.7ef\n",lamb);
		
	}
	free_matrix(A, 1, n, 1, n);
  	free_matrix(W, 1, n, 1, n);
  	free_vector(d, 1, n);
 	free_vector(e, 1, n);
 	free_vector(v0, 1, n);
 	free_vector(v1, 1, n);
	fclose(fp);
}