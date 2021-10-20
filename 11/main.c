#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "four1.c"
#include "nrutil.c"
#include "nrutil.h"


float ran(){
	float result = (float) rand()/(RAND_MAX + 1.0);
	return result - 0.5;
}

float f0(float t, float omega){
	return sin(omega*t) + sin(2*omega*t) + sin(3*omega*t);
}

float fun( float sigma, float ti){
	return (1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(ti * ti) / (2* sigma * sigma));
}

float g0(float t,float sigma) {
	float result = 1.0/(sigma*sqrt(2*M_PI));
	result *= exp(-t*t/(2*sigma*sigma));
	return result;
}

int main() {
	FILE * file1 = fopen("k8.dat","w");
	FILE * file2 = fopen("k10.dat","w");
	FILE * file3 = fopen("k12.dat","w");
	int k_table[] = {8,10,12};


	for (int i = 0; i<3; i++){
		int k = k_table[0];
		FILE * file;
		if (i ==0) file = file1;
		if (i ==1) file = file2;
		if (i ==2) file = file3;

		int N = pow(2,k);
		float* f = vector(1,N*2);
		float* g1 = vector(1,N*2);
		float* g2 = vector(1,N*2);
		float T = 1.0;
		float t_max = 3 * T;
		float dt = t_max/N;
		float sigma = T/20;
		float omega = 2.0*M_PI/T;


		for (int j = 1; j <= N ; j++){
			float t = dt * (j-1);
			f[2*j-1] = f0(t,omega) + ran();
			f[2*j ] = 0.0;

			g1[2 * j-1] = g0(t,sigma);
			g1[2*j ] = 0.0;

			g2[2 * j-1] = g0(t,sigma);
			g2[2*j ] = 0.0;

			fprintf(file,"%g %g \n", t , f[2*j-1]);
		}

		four1(f, N, 1);
		four1(g1, N, 1);
		four1(g2, N, -1);


		
	

		for (int j = 1; j <= N; j++) {
				float a1 = f[2 * j - 1];
				float b1 = f[2 * j];
				float a2 = g1[2 * j - 1] + g2[2 * j - 1];
				float b2 = g1[2 * j] + g2[2 * j];
				f[2 * j - 1] = a1 * a2 - b1 * b2;
				f[2 * j] = a1 * b2 + a2 * b1;
		}

		four1(f, N, -1);


		float f_max = fabs(f[1]);

		for (int j = 2 ; j<=N;j++){
			f_max = fmax(fabs(f[2*j-1]) , f_max);
		}
		fprintf(file,"\n\n");
		for (int j =1; j<=N ; j++){
			fprintf(file,"%g %g\n", dt*j, f[2 * j-1] * 2.5 / f_max);
		}

		free_vector(f, 1, 2 * N);	
		free_vector(g1, 1, 2 * N);
		free_vector(g2, 1, 2 * N);
		
	}
	
	fclose(file1);
	fclose(file2);
	fclose(file3);
	return 0;
}