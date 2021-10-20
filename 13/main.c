#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "gauher.c"
#include "gaulag.c"
#include "gauleg.c"
#include "gammln.c"
#include "nrutil.c"
#include "nrutil.h"


float fun1(float x){
	return 1/(x * sqrt(x*x - 1));
}
float fun2_her(float x){
	return log(fabs(x))*exp(-(x*x));
}
float fun2(float x){
	return log(x)*exp(-(x*x));
}
float fun3(float x){
	return sin(2*x)*exp(-2*x);
}

int main() {
	FILE * file1 = fopen("out.dat","w");
	float c1_a = 3.14/3;
	float c2_a = -0.8700577;
	float c3_a = 2/13;
	for(int n = 2; n<=100 ; n++){
		float* v1 = vector(1 , n);
		float* v2 = vector(1 , n);

		float a = 2.0;
		float b = 1.0;
		float c1 = 0.0;
		gauleg(b,a,v1,v2,n);

		for(int i = 1 ; i <= n ; i++){
			c1 += v2[i] * fun1(v1[i]);
		}
		float val = fabs(c1 - c1_a);

		fprintf(file1,"%d\t%f\n",n ,val);

		free_vector(v1,1,n);
		free_vector(v2,1,n);
	}
	fprintf(file1,"\n\n");

	for(int n = 2; n<=100 ; n = n + 2){
		float* v1 = vector(1 , n);
		float* v2 = vector(1 , n);

		
		float c2 = 0.0;
		gauher(v1,v2,n);

		for(int i = 1 ; i <= n ; i++){
			c2 += v2[i] * fun2_her(v1[i])/2 ;
		}
		float val = fabs(c2 - c2_a);

		fprintf(file1,"%d\t%f\n",n ,val);

		free_vector(v1,1,n);
		free_vector(v2,1,n);
	}
	fprintf(file1,"\n\n");

	for(int n = 2; n<=100 ; n++){
		float* v1 = vector(1 , n);
		float* v2 = vector(1 , n);

		float a = 5.0;
		float b = 0.0;
		float c3 = 0.0;
		gauleg(b,a,v1,v2,n);

		for(int i = 1 ; i <= n ; i++){
			c3 += v2[i] * fun2(v1[i]);
		}
		float val = fabs(c3 - c2_a);

		fprintf(file1,"%d\t%f\n",n ,val);

		free_vector(v1,1,n);
		free_vector(v2,1,n);
	}
	fprintf(file1,"\n\n");


	for(int n = 2; n<=10 ; n++){
		float* v1 = vector(1 , n);
		float* v2 = vector(1 , n);


		float c3 = 0.0;
		gaulag(v1,v2,n,0.0);

		for(int i = 1 ; i <= n ; i++){
			c3 += v2[i] * fun3(v1[i]);
		}
		float val = fabs(c3 - c3_a);

		fprintf(file1,"%d\t%f\n",n ,val);

		free_vector(v1,1,n);
		free_vector(v2,1,n);
	}
	
	fclose(file1);

	return 0;
}