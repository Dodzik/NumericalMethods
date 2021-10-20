#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define N 200


struct Point{
	double x;
	double y;

};

typedef struct Point Point;


double d_rand ( const double min , const double max ){
	double r = ( double ) rand () / RAND_MAX ; // Przedzial [0 , 1]
	r = r * ( max - min ) + min ; // Przeskalowanie do [min , max]
	return r;
}

double fun(double x, double y){
	return sin(x) * sin(y) - exp(- pow( x + M_PI/2.0, 2.0) - pow(y - M_PI/2.0,2.0));
}

int main() {
	FILE* fp1 = fopen("w0.dat","w");
	FILE* fp2 = fopen("T.dat", "w");

	Point*	tab = (Point*) malloc(N*sizeof(Point));
	for (int i =0; i<N ; i++){
		tab[i].x = 5.0;
		tab[i].y = 5.0;
	}

	for (int it =0; it<=20; it++){
		double T = 10.0 / pow(2, it);

		for (int k = 0; k < 100; k = k + 1) {

			for (int i = 0; i < N; i = i + 1){
				double dx = d_rand(-1.0,1.0);
				double dy = d_rand(-1.0,1.0);

				double posX = tab[i].x + dx;
				double posY = tab[i].y + dy;
				// fprintf(fp2,"%g %g %g %g\n",posX,posY , tab[i].x,tab[i].y);
				if ( fun(posX,posY) < fun(tab[i].x,tab[i].y) ){
					tab[i].x = posX;
					tab[i].y = posY;
				}
				else if ( d_rand(0,1) < exp(-(fun(posX,posY) - fun(tab[i].x,tab[i].y)/T )) ){
					tab[i].x = posX;
					tab[i].y = posY;
				}

			}
			fprintf(fp1, "%g \n",fun(tab[0].x,tab[0].y));

		}
		
		if(it == 0 || it == 7 || it ==20){
			for (int i = 0; i<N; i++){
				fprintf(fp2, "%g  %g \n",tab[i].x,tab[i].y);
				
			}
			fprintf(fp2,"\n\n");
		}

	}

	fclose(fp1);
	fclose(fp2);
	free(tab);
	return 0;
}