/*****************************************************************

	--> ini.c

	Executez 1 fois avant "prod.c" et "cons.c"
	
	Stevens Gagnon
	Departement Informatique
	College Shawinigan
	
******************************************************************/
#include <stdio.h>

#include "jeton.h"
#include "key.h"

#define jetons_de_depart 0

   
int main()
{
	int cadenasPx;
    int cadenasSeq;

	FILE* fptr1;
	fptr1 = fopen("P1.txt", "w");
	FILE* fptr2;
	fptr2 = fopen("P2.txt", "w");
	FILE* fptr3;
	fptr3 = fopen("P3.txt", "w");
	FILE* fptr4;
	fptr4 = fopen("P4.txt", "w");
	FILE* fptrx;
	fptrx = fopen("Px.txt", "w");
	FILE* fptrSeq;
	fptrSeq = fopen("PSeq.txt", "w");

	cadenasPx = InitSemaphore(KEY, jetons_de_depart);  // Met en place un semaphore avec jetons_de_depart jeton(s)
    cadenasSeq = InitSemaphore(KEY1, jetons_de_depart);  // Met en place un semaphore avec jetons_de_depart jeton(s)
    
	
	if(cadenasPx >= 0) // Creation OK
	{
		fprintf(stderr, "Le semaphore %d est en place, CONS et PROD peuvent commencer.\n", KEY);
	}
    	if(cadenasSeq >= 0) // Creation OK
	{
        fprintf(stderr, "Le semaphore %d est en place, CONS et PROD peuvent commencer.\n", KEY1);
	}

	return 0;
}
