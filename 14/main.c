#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include"gammln.c"
#include"nrutil.h"
#include"nrutil.c"
#include"grammp.c"
#include"gcf.c"
#include"gser.c"


#define N 10000

unsigned long RJ(unsigned long x, int a, int c, unsigned long m){
    return (a*x+c)%m;
}

double gestosc(double x, double mi, double sig){

    return (1/(sig*sqrt(2*3.14)))*exp(-(pow(x-mi,2)/(2*pow(sig,2))));
}

double F(double x, double mi, double sig){

    return (1-erf((x-mi)/(sqrt(2)*sig)))/2;
}

int main(void){
	FILE * file1 = fopen("U.dat","w");
	FILE * file2 = fopen("U_hist.dat","w");
	FILE * file3 = fopen("N_hist.dat","w");
    int a=123, c=1;
    unsigned long Xp=10, Xi, m=pow(2,15);
    double xp, xi, sum=0,mi;
    double tab[N];

	double tab2[N];
	int a2 = 69069, c2 = 1;
	unsigned long m2=pow(2,32);

    tab[0]=(RJ(10, a, c, m))/(m+1.);
    sum=tab[0];
    for(int i=1;i<N;i++) {
        Xi=RJ(Xp, a, c, m);
        tab[i]=Xi/(m+1.) ;
        fprintf(file1,"%f\t%f\n",tab[i-1],tab[i]);       
        sum+=tab[i];
        Xp=Xi;
    }
	fprintf(file1,"\n\n"); 
	printf("%f\n\n",sum/N);
	Xp=10;
	double sum2=0;
	tab2[0]=(RJ(10, a2, c2, m2))/(m2+1.);
    sum2=tab2[0];
	for(int i=1;i<N;i++) {
        Xi=RJ(Xp, a2, c2, m2);
        tab2[i]=Xi/(m2+1.) ;
        fprintf(file1,"%f\t%f\n",tab2[i-1],tab2[i]);       
        sum2+=tab2[i];
        Xp=Xi;
    }
	printf("%f\n\n",sum2/N);
    int sum3=0;

    for(int i=0;i<N;i++) {
        sum3+=pow(tab[i]-mi,2);
    }

    double sig=sqrt(sum3/N);
	printf("%f \n",sig);

    int k=12;
    double xmin=0,xmax=1;
    double d=(xmax-xmin)/(double)k;

    int traf[k],j;

	int traf2[k],j2;

     for(int i=0;i<k;i++)traf[i]=0;
     for(int i=0;i<N;i++) {
        j=(int)((tab[i]-xmin)/d);
        traf[j]=traf[j]+1;
    }

	 for(int i=0;i<k;i++)traf2[i]=0;
     for(int i=0;i<N;i++) {
		
        j2=(int)((tab2[i]-xmin)/d);

        traf2[j2]=traf2[j2]+1;
    }
    
    for(int i=0;i<k;i++)fprintf(file2,"%f\t%f\n",xmin+d*(i+0.5), (double)traf[i]/N);
	fprintf(file2, "\n\n");
	for(int i=0;i<k;i++)fprintf(file2,"%f\t%f\n",xmin+d*(i+0.5), (double)traf2[i]/N);



	FILE * file4 = fopen("rozklad_normalny.dat","w");


    int dd=1;           
    double mi0=0.2, sig0=0.5;       
    xmin=mi0-3*sig0;                
    xmax=mi0+3*sig0;
    double wid=xmax-xmin;           
    double U1,u1,U2,u2;
    double Up1=10,Up2=10;
    double p[k];
    sum=0;
    int n=0;

    while(n<N){
        U1=RJ(Up1, a, c, m);
        u1=(U1/(m+1.))*wid+xmin;
        U2=RJ(U1, a, c, m);
        u2=(U2/(m+1.));
        if(u2<=gestosc(u1,mi0,sig0)){
            tab[n]=u1;
            sum+=tab[n];
            n++;}
        
        
        Up1=U2;
    }

    mi=(double)sum/(double)N; 
    sum=0;

    for(int i=0;i<N;i++) {
        fprintf(file4,"%f\n",tab[i]);
        sum+=pow(tab[i]-mi,2);
    }

    double war=(sum/N);
    sig=sqrt(war);

    printf("\n%f\t%f\t%f\n\n",mi,war,sig);
      


    

    d=(xmax-xmin)/(double)k;

    for(int i=0;i<k;i++)traf[i]=0;
     for(int i=0;i<N;i++) {
        j=(int)((tab[i]-xmin)/d);
        traf[j]=traf[j]+1;
    }
    
    double S=0;

    for(int i=0;i<k;i++){
        p[i]=F(xmin+i*d,mi0,sig0)-F(xmin+(i+1)*d,mi0,sig0);
        fprintf(file3,"%f\t%f\n",xmin+d*(i+0.5), (double)traf[i]/N);
        S+=pow(traf[i]-N*p[i],2)/(N*p[i]);

    }

    printf("%f\n\n",S);
    double poz=gammp((k-2-1)/2,S/2);
    double alfa = 1 - poz;

    printf("%f\t%f\n",poz,alfa);

	fclose(file1);
	fclose(file2);
	fclose(file3);
	fclose(file4);
    return 0;
}