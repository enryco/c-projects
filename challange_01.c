//
//  main.c
//  Challange01
//
//  Created by Enrico Scherlies on 01.10.13.
//  Copyright (c) 2013 Enrico Scherlies. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define b 1726


int nnf(double **larray, char name[b][10]);


int main()
{
    double cor[b][2];
    char name[b][10];
    int randliste[20];
    srand(1);
    int i=0, k=0, mm=0; // mm ist die Zeile an der sich die Koordinaten für MainManchester und speater des neuen Startbezirkes befinden
    
    /********************************************************
     *   Oeffnen der Datei und Einlesen in Arrays           *
     *******************************************************/
    
    FILE *fptr = fopen("postcodes.txt", "r");
    
    for (int i=0; i<b; i++) {
        fscanf(fptr,"%s %lf %lf",name[i],&cor[i][0],&cor[i][1]);
    }
    
    /********************************************************
     *           Erstellen des Laengen Arrays               *
     *******************************************************/
    
    /* Speicher fuer das 1726 mal 1726 Array allokatieren */
    
    double **larray=(double **)malloc(b*sizeof(double));
    for (i=0; i<b; i++) {
        larray[i] = (double *)malloc(b*sizeof(double));
    }
    
    /* Laengen berechnen und speichern */
    for (i=0;i<b; i++) {
        for (k=0; k<b; k++) {
            larray[i][k] = sqrt(pow(cor[i][0]-cor[k][0], 2)+pow(cor[i][1]-cor[k][1], 2));
        }
    }
    
    /* Generieren von 20 zufälligen Zahlen zw 1 und 1726 */
    for (int i=0; i<20; i++) {
        randliste[i]=rand()%b+1;
        //printf("%i\n",randliste[i]);
    }
    
    /* Position der Koordinaten von M1_2EA zwischenspeichern */
    i=0;
    while (i!=1) {
        int comp = strcmp(name[mm],"M1_2EA");
        if (comp==0) {
            i++;
        }
        else mm++;
    }
    
    //printf("%i %s hat x = %lf und y = %lf\r\r",mm,name[mm],cor[mm][0],cor[mm][1]);
    
    
    /* Ausgeben 20 zufälliger Bezirke */
    printf("Die 20 Zufälligen Bezirke sind:\n");
    for (int i=0; i<20; i++) {
        
        //printf("%i -",i);
        printf("%s",name[randliste[i]]);
        fprintf(stdout," \t%lf \t%lf",cor[randliste[i]][0], cor[randliste[i]][1]);
        printf("\tPosition #%i\n",randliste[i]);
    }
    
    
    /********************************************************
     *   Algorithmus zur Bestimmung des nächsten Nachbarn   *
     *******************************************************/
    
    
    printf("\nDie Reihenfolge fuer den kuerzesten Weg ist:\n");
    double l[20];
    int NN; // Naechster Nachbar
    
    for (int z=20; z>0;z--) {
        NN=0;
        //printf("neuer startbezirk(mm) ist %s\n",name[mm]);
        for (i=0; i<z; i++) {
            l[i] = larray[randliste[i]][mm];
            //printf("%i \t%lf - \n",i,l[i]);
            if (l[i]<l[NN]) {
                NN=i;}
        }
        
        //printf("(%i/%i | %i ) --- %s\n",NN,z,randliste[NN],name[randliste[NN]]);
        mm=randliste[NN];
        for (i=NN; i<z; i++) {
            randliste[i]=randliste[i+1];
        }
        printf("%s\n",name[mm]);
        
    }
    printf("\n");
    nnf(larray,name);
}


int nnf(double **larray, char name[b][10]) {
    
    char bezirk[10];
    int i=0, pos_A=0, pos_B=0;
    
    printf("Funktion zur Berechnung des naechsten Nachbarn.\n");
    printf("Geben Sie die PLZ des Bezirkes ein: ");
    scanf("%s",bezirk);
    
    while (i!=1) {
        
        if (strcmp(bezirk, name[pos_A])==0) {
            i=1;
            for (int i=0; i<b; i++) {
                
                if (larray[pos_A][i]!=0) {
                    if (larray[pos_A][i]<larray[pos_A][pos_B]) {
                        pos_B=i;
                    }
                }
            }
            printf("Der naechste Bezirk zu %s ist %s mit dem Abstand von %lf",bezirk,name[pos_B],larray[pos_B][pos_A]);
            
        } else pos_A++;
        
        if (pos_A==1727) {
            printf("Keinen Bezirk mit der PLZ %s gefunden...",bezirk);
            i=1;
        }
        
    }
    
    
    return 0;
}



