#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IT_MAX 20;

double licz_r(double* tab_1, double* tab_2,int n , double x0){
	tab_2[n] = 0.0;
	for (int i = n - 1; i >= 0; i--){
		tab_2[i] = tab_1[i+1] + x0*tab_2[i+1];
	}
	return tab_1[0] + x0*tab_2[0];
}

int main(void) {
	FILE *fp;
	fp=fopen("dane.dat","w");
	int N = 5;
	double* tab_1 =(double*)malloc((N+1)*sizeof(double));
	double* tab_2 =(double*)malloc((N+1)*sizeof(double)); 
	double* tab_3 =(double*)malloc((N+1)*sizeof(double));

	tab_1[0] = 240.0;
	tab_1[1] = -196.0;
	tab_1[2] = -92.0;
	tab_1[3] = 33.0;
	tab_1[4] = 14.0;
	tab_1[5] = 1.0;

	double x0 = 0.0;
	double Rj = 0.0;
	double Rj_prim = 0.0;
	double x1 = 0.0;
	int  n;

	for(int L=1;L <= N; L++){

		n= N - L + 1;	
		x0 = 0.0;
		for(int it = 1; it <= 20 ; it++){

			Rj = licz_r(tab_1,tab_2,n,x0);
			Rj_prim = licz_r(tab_2,tab_3,n-1,x0);
			x1 = x0 - Rj/Rj_prim;
			//printf("L = %d ,it =  %d, x0 = %.4ef ,Rj = %.4ef ,Rj_prim = %.4ef \n",L, it, x0, Rj,Rj_prim);
			fprintf(fp,"L = %d ,it =  %d, x0 = %.4ef ,Rj = %.4ef ,Rj_prim = %.4ef \n",L, it, x0, Rj,Rj_prim);
			if(fabs(x1-x0)<1.0E-7){

				break;
			}
			x0=x1;

		}

		for (int i = 0 ;i<=(n-1);i++){
			tab_1[i] = tab_2[i];
		}

		//printf("=============================\n\n");
		fprintf(fp,"=============================\n\n");

	}
	fclose(fp);
	return 0;
}