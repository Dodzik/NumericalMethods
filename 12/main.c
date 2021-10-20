#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int n = 8;
double b =1.0;
double a = 0.0;

double fun(double x) {
	return log(x*x*x + 3*x*x + x + 0.1) * sin(18*x);
}

double Simp(double h,int N){
	double cout =0.0;
	// printf("%f\n",h);
	for (int i =0 ; i<N+1; i++){
		double x = a + 2*i*h;
		cout += h/3.0 * (fun(x) + 4*fun(x+h) + fun(x+ 2*h ) );
		// printf("%f\n",cout);
	}
	// printf("%f   krowa\n",cout);
	return cout;
}

void print_mat(double D[][n+1]){
	for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < n+1; ++j) {
            printf("%.3lf  ", D[i][j]);
        }
        printf("\n");
    }
}

// double queue (double D[][n+1], int w, int k) {
double queue (double D[][n+1], int w, int k) {
	// printf("%f \n",(pow(4.0, k)*D[w][k-1] - D[w-1][k-1]));
	// printf("%f \n",(pow(4.0, k) - 1.0));
	// printf("\n\n");
	return (pow(4.0, k)*D[w][k-1] - D[w-1][k-1]) / (pow(4.0, k) - 1.0);
}

double Mil(double h, int n){
	double cout=0;
	for(int i=0; i<n+1;i++){
		double x = a + 4*i*h;
		cout += 4.0 * h/90.0 * (7*fun(x) + 32*fun(x+h) + 12*fun(x+ 2*h ) + 32*fun(x+ 3*h ) + 7*fun(x+ 4*h ) );
	}
	return cout;
}

int main() {
	FILE * file1 = fopen("output.dat","w");

	fprintf(file1,"w\t\tD[w,0]\t\t\tD[w,w]\n");
	// int n = 8;
	// double b =1.0;
	// double a = 0.0;
	double D [n+1][n+1];
	for(int i =0;i<n+1;i++){
		for(int j =0;j<n+1 ; j++){
			D[i][j] = 0;
		}
	}
	
	for (int w =0; w<=n;w++){
		int N = pow(2,w+1);
		// printf("%d ",N);
		double h_w = (b - a) / (N);
		// printf("%f ",h_w);
		D[w][0] = Simp(h_w , N/2 - 1);
		// printf("%.3f \n\n\n",D[w][0]);
		if (w >=1) {
			for (int k = 1; k<=w ; k++){
				D[w][k] = queue(D, w, k);
				// printf("%.3f  " , D[w][k]);
			}
			// printf("kolejny loop\n");
		}

		fprintf(file1,"%d\t %.11lf\t%.11lf\n",w,D[w][0],D[w][w]);

	}
	print_mat(D);
	
	fprintf(file1,"\n\n");
	printf("\n\n");

	double D2 [n+1][n+1];
	for(int i =0;i<n+1;i++){
		for(int j =0;j<n+1 ; j++){
			D2[i][j] = 0;
		}
	}

	for (int w =0; w<=n;w++){
		int N = pow(2,w+2);
		// printf("%d ",N);
		double h_w = (b - a) / (N);
		// printf("%f ",h_w);
		D2[w][0] = Mil(h_w , N/4 - 1);
		// printf("%.3f \n\n\n",D[w][0]);
		if (w >=1) {
			for (int k = 1; k<=w ; k++){
				D2[w][k] = queue(D2, w, k);
				// printf("%.3f  " , D[w][k]);
			}
			// printf("kolejny loop\n");
		}

		fprintf(file1,"%d\t%.11lf\t%.11lf\n",w,D2[w][0],D2[w][w]);

	}
	print_mat(D2);


	fclose(file1);

	return 0;
}