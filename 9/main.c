#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define frand() ((double)rand())/(RAND_MAX+1.0)
#define N 201

int main() {
	double x_min = -4.0;
	double x_max = 4.0;
	double sigma = (x_max - x_min)/16, x0 = 2.0;
	double deltaX = (x_max - x_min) / (N-1.0), x[N], y[N];
	double Alpha, Betha, ySzum[N];
	double phi[51][N];

	FILE * fp1 = fopen("Gram.dat", "w");

	for(int i = 0; i < N; i++) {
		x[i] = x_min + i * deltaX;
		y[i] = sin((14*M_PI*x[i])/(x_max-x_min))*(exp(-(x[i]-x0) * (x[i]-x0) / (2 * sigma * sigma)) + exp(-(x[i]+x0) * (x[i]+x0) / (2 * sigma * sigma)));
	}

	for(int i = 0; i < N; i++)
		phi[0][i] = 1;

	for(int j = 1; j < 51; j++) {
		double aAlpha = 0, bAlpha = 0, aBetha = 0, bBetha = 0;
		for(int i = 0; i < N; i++) {
			aAlpha += x[i] * phi[j-1][i] * phi[j-1][i];
			bAlpha += phi[j-1][i] * phi[j-1][i];

			aBetha += x[i] * phi[j-2][i] * phi[j-1][i];
			bBetha += phi[j-2][i] * phi[j-2][i];

		}
		Alpha = aAlpha/bAlpha;
		if(j != 1)
				Betha = aBetha/bBetha;
			else Betha = 0;

		for (int i = 0; i < N; i++) {
			phi[j][i] = (x[i] - Alpha) * phi[j-1][i] - Betha * phi[j-2][i];
		}
	}

	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < N; j++) {
			fprintf(fp1, "%f %f\n", x[j], phi[i][j]/phi[i][0]);
		}
		fprintf(fp1, "\n\n");
	}


	for(int i = 0; i < N; i++) {
		ySzum[i] = y[i] + (frand() - 0.5)/ 5;
	}

	fclose(fp1);

	FILE * fp2 = fopen("approx.dat", "w");


	FILE * fp3 = fopen("pkt.dat", "w");
	for(int i = 0 ;i< N ;i++){
		fprintf(fp3,"%f %f\n",x[i],ySzum[i]);
	}
	int m = 10;
	int m2 = 30;
	int m3 = 50;

	double c, s;
	double F;

	for(int k = 0; k < N; k++) {
		F = 0;
		for (int j = 0; j <= m; j++) {
			c = 0;
			s = 0;

			for(int i = 0; i < N ; i++) {
				c += ySzum[i] * phi[j][i];
				s += phi[j][i] * phi[j][i];
			}
			F += c/s * phi[j][k];
		}

		fprintf(fp2, "%f %f \n",  x[k], F);
	}
	fprintf(fp2,"\n\n");
	for(int k = 0; k < N; k++) {
		F = 0;
		for (int j = 0; j <= m2; j++) {
			c = 0;
			s = 0;

			for(int i = 0; i < N ; i++) {
				c += ySzum[i] * phi[j][i];
				s += phi[j][i] * phi[j][i];
			}
			F += c/s * phi[j][k];
		}

		fprintf(fp2, "%f %f \n",  x[k], F);
	}
	fprintf(fp2,"\n\n");
	for(int k = 0; k < N; k++) {
		F = 0;
		for (int j = 0; j <= m3; j++) {
			c = 0;
			s = 0;

			for(int i = 0; i < N ; i++) {
				c += ySzum[i] * phi[j][i];
				s += phi[j][i] * phi[j][i];
			}
			F += c/s * phi[j][k];
		}
		 fprintf(fp2, "%f %f \n",  x[k], F);
		// fprintf(fp2, "%f %f %f %f\n", x[k], ySzum[k], y[k], F);
	}

	fclose(fp2);
	fclose(fp3);
	return 0;
}