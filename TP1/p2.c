/******************************************************************
	
	--> prod.c

	Le programme "ini.c" doit avoir ete execute 1 fois avant "prod.c" et "cons.c"

	Stevens Gagnon
	Departement Informatique
	College Shawinigan
	
******************************************************************/
#include <stdio.h>

#include "jeton.h"
#include "key.h"

int main()
{
	int cadenasPx, nb, cadenasSeq, keyNb;
	int nombre = 0;
	int retval;
	pid_t pid;
	char input[50];
	FILE* fptr;

	cadenasPx = DemandeId(KEY);  // Met en place un semaphore avec jetons_de_depart jeton(s)
    cadenasSeq = DemandeId(KEY1);  // Met en place un semaphore avec jetons_de_depart jeton(s)
	
	if(cadenasPx >= 0) // Si le semaphore existe
	{
		while (nombre >=0)
		{
			printf("Entrez un nombre positif ");
			scanf("%s",input);
			printf("\n");
			sscanf(input, "%d", &nombre);

			
			if (nombre >=0)
			{
				pid = getpid();
				retval = Signale(cadenasPx);   //*************** Debloque un processus *****************
				pid = getpid();
				retval = Signale(cadenasSeq);   //*************** Debloque un processus *****************
				fptr = fopen("P2.txt", "a");  //Écriture dans P1.txt
				fprintf (fptr, "%i\n", nombre);
				fclose(fptr);

				keyNb = NbJeton(cadenasSeq);	//Écriture dans Px.txt
				FILE* fptrx;
				fptrx = fopen("Px.txt", "a");
				fprintf(fptrx, "P1 : %d\n", keyNb);
				fclose(fptrx);

				fptrx = fopen("PSeq.txt", "w");	//Écriture dans PSeq.txt
				fprintf(fptrx, "%d", keyNb);
				fclose(fptrx);
			}
			
		}
	}
	else
	{
		fprintf(stderr, "Le programme ne trouve cette cle de semaphore.\n");
	}

	return 0;
}
