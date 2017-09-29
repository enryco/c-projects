#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define n 4
#define m 2

int fac(int f);

int main () {
    
    
    double Y[n][m];
    //double L[n][n];
    //double B[n][m];
    
    /* Matrix L - allocate memory */
    
    double **L=(double **)malloc(n*sizeof(double));
    for (int i=0; i<n; i++) {
        L[i] = (double *)malloc(n*sizeof(double));
    }
    
    /* Matrix B - allocate memory */
    
    double **B=(double **)malloc(n*sizeof(double));
    for (int i=0; i<n; i++) {
        B[i] = (double *)malloc(m*sizeof(double));
    }
    
    /* Matrix Y - allocate memory
    
    double **Y=(double **)malloc(n*sizeof(double));
    for (int i=0; i<n; i++) {
        Y[i] = (double *)malloc(m*sizeof(double));
    }
    */
    
    /******************************************************/
    /* filling matrices L and B randomly between -1 and 1 */
    /******************************************************/
    
    time_t t;
    time(&t);
    srand((int)t); // time in [s] as initializor
    
    // lower triangular matrix L
    for (int i=0; i<n; i++) {
        
        for (int k=0; k<i+1; k++) {
            
            L[i][k]=i+1+0.1*(k+1);
            //printf("%lf\t",L[i][k]);
            
        }
        
        //printf("\n");
        
    }
    
    printf("\n\n");
    
    // matrix B
    for (int i=0; i<n; i++) {
        
        for (int k=0; k<m; k++) {
            
            B[i][k]=i+1+3*k;
            //printf("%lf\t",B[i][k]);
            
        }
        
        //printf("\n");
        
    }
    
    printf("\n");
    printf("\n");

    /******************************************************/
    /*          the  algorithm                            */
    /******************************************************/
    
    //unter annahme einer n*1 matrix Y
    
    //initialisierungsschritt
    
    for (int k=0; k<m; k++) {
        
    
        Y[0][k]=B[0][k]/L[0][0];
    
        for (int i=1; i<n; i++) {
        
            double res=0.0;
            for (int j=i; j>=0; j--) {
                res-=L[i][j-1]*Y[j-1][k];
                //printf("L=%lf\tY=%lf\n",L[i][j-1],Y[j-1][k]);
            }
            //printf("Res=\t%lf\n",res);
            //printf("B=\t%lf\nL=\t%lf\n",B[i][k],L[i][i]);

            Y[i][k]=(B[i][k]+res)/L[i][i];
            //printf("%lf\n",Y[i][k]);
        
        }
    
    }
    
    //Output
    
    printf("\n__________\n");
    for (int i=0; i<n; i++) {
        
        for (int k=0; k<m; k++) {
            
            printf("%lf\t",Y[i][k]);
            
        }
        
        printf("\n");
        
    }

    
    
}

int fac(int f) {
    
    int r=f;
    while (--r) f*=r;
    return f;
    
}