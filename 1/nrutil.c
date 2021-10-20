#include "nrutil.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


float** matrix(int a1,int n1,int a2,int n2){
    float **m;
    m=(float**)malloc(sizeof(float*)*n1);

    for(int i=0;i<n2;i++){
        m[i]=(float*)malloc(sizeof(float)*n2);
    }
    return m;

}

void free_matrix(float ** m, int a1, int n1, int a2, int n2){
    for(int i=0;i<n2;i++){
        free(m[i]);
    }
    free(m);
}