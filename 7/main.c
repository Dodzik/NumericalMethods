#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

double x_min = -5.00;
double x_max = 5.00;

double czebysz(int n, int m){
	return 0.5 * ( (x_max - x_min) * cos(PI*(2.0 * (double)m + 1.0) / (2.0 * (double)n + 2.0) ) + (x_min + x_max));
}

double lagraunge(double x, int n, double xm[], double ym[]){
    double wiel = 0.0;

    for(int i = 0; i <= n; i++) {
        double tmp = 1.0;

        for(int j = 0; j <= n; j++) {

            if(j!=i){
                tmp *= (x - xm[j]) / (xm[i] - xm[j]);
				
            }
        }
        wiel += ym[i] * tmp;
		
    }
	// printf("%g\n",wiel);
    return wiel;
}

void wyk(double x[], double y[], double xm[], double ym[],int n){
	for (int i = 0; i<n;i++){
		x[i] = 0.0;
		y[i] = 0.0;
		xm[i] = 0.0;
		ym[i] = 0.0;

		x[i] = x_min + ((x_max - x_min)/(double)n) *i;
		y[i] = exp(-(x[i] * x[i]));

		xm[i] = czebysz(n,i);
		ym[i] = exp(-(xm[i] * xm[i]));
	}
}

// void dopliku(double x[],double y[],int n,FILE *f){
// 	 for(int i = 0; i <= n; i++) {
//         fprintf(f,"%g %g \n", x[i], y[i]);
//     }
//     fprintf(f,"\n \n");
// }
void prt(double x[],double y[],int n){
	 for(int i = 0; i <= n; i++) {
        printf("%g %g \n", x[i], y[i]);
    }
    printf("\n \n");
}

void wyp(double *x, double *y,int n,FILE * f){
	for (int i= 0; i<1000; i++){
	  	double zn = x_min + 0.01 * i;
    	double wiel = lagraunge(zn, (n-1), x, y);

        fprintf(f,"%g %.4ef\n",zn, wiel);
    }
    fprintf(f,"\n\n");
}


int main(void) {
	FILE *fp;
	fp=fopen("zad_1.dat","w");
	int n1 = 5;
	double x1[n1+1];
	double y1[n1+1];
	double xm1[n1+1];
	double ym1[n1+1];
	wyk(x1,y1,xm1,ym1,n1);
	
	

	int n2 = 10;
	double x2[n2+1];
	double y2[n2+1];
	double xm2[n2+1];
	double ym2[n2+1];
	wyk(x2,y2,xm2,ym2,n2);

	int n3 = 15;
	double x3[n3+1];
	double y3[n3+1];
	double xm3[n3+1];
	double ym3[n3+1];
	wyk(x3,y3,xm3,ym3,n3);

	int n4 = 20;
	double x4[n4+1];
	double y4[n4+1];
	double xm4[n4+1];
	double ym4[n4+1];
	wyk(x4,y4,xm4,ym4,n4);

	prt(x1,y1,n1);
	prt(x2,y2,n2);
	prt(x3,y3,n3);
	prt(x4,y4,n4);

	prt(xm1,ym1,n1);
	prt(xm2,ym2,n2);
	prt(xm3,ym3,n3);
	prt(xm4,ym4,n4);


	wyp(x1,y1,n1,fp);
	wyp(x2,y2,n2,fp);
	wyp(x3,y3,n3,fp);
	wyp(x4,y4,n4,fp);

	fclose(fp);
	FILE *fp2;
	fp2=fopen("zad_2.dat","w");
	wyp(xm1,ym1,n1,fp2);
	wyp(xm2,ym2,n2,fp2);
	wyp(xm3,ym3,n3,fp2);
	wyp(xm4,ym4,n4,fp2);

	fclose(fp2);

	
}