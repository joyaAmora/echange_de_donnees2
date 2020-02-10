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
	#pragma region -- Variables et fichier
	int cadenas, cadenas1;

	#pragma region -- Ouverture fichier en reset
    FILE *U_P1, *U_P2, *U_P3, *U_P4, *U_Px, *U_Pseq;
    U_P1 = fopen("P1.txt", "w");
	U_P2 = fopen("P2.txt", "w");
	U_P3 = fopen("P3.txt", "w");
	U_P4 = fopen("P4.txt", "w");
	U_Px = fopen("Px.txt", "w");
	U_Pseq = fopen("Pseq.txt", "w");
	#pragma endregion

	#pragma region -- Test des fichiers
	if(U_P1 == NULL)	
        printf("--------------------- P1.txt -> Probleme de fichier\n");
    else
        printf("--------------------- P1.txt -> Fichier ok\n");
	
	if(U_P2 == NULL)	
        printf("--------------------- P2.txt -> Probleme de fichier\n");
    else
        printf("--------------------- P2.txt -> Fichier ok\n");
	
	if(U_P3 == NULL)	
        printf("--------------------- P3.txt -> Probleme de fichier\n");
    else
        printf("--------------------- P3.txt -> Fichier ok\n");

	if(U_P4 == NULL)	
        printf("--------------------- P4.txt -> Probleme de fichier\n");
    else
        printf("--------------------- P4.txt -> Fichier ok\n");

	if(U_Px == NULL)	
        printf("--------------------- Px.txt -> Probleme de fichier\n");
    else
        printf("--------------------- Px.txt -> Fichier ok\n");

	if(U_Pseq == NULL)	
    {
		printf("--------------------- Pseq.txt -> Probleme de fichier\n");
		fprintf(U_Pseq, "%c", 0);
	}
    else
        printf("--------------------- Pseq.txt -> Fichier ok\n");
	#pragma endregion

	#pragma region -- Fermeture des ficher
	fclose(U_P1);
	fclose(U_P2);
	fclose(U_P3);
	fclose(U_P4);
	fclose(U_Px);
	fclose(U_Pseq);
	#pragma endregion
	#pragma endregion

	#pragma region -- Semaphores key et key_fin
	cadenas = InitSemaphore(KEY, 1);  // Met en place un semaphore avec jetons_de_depart jeton(s)
	cadenas1 = InitSemaphore(KEY_fin, jetons_de_depart);  // Met en place un semaphore avec jeton_de_depart 0 qui cumule a la fin de chaque P qui termine 

	if(cadenas >= 0) // Creation OK
	{
		fprintf(stderr, "Le semaphore %d est en place, CONS et PROD peuvent commencer.\n", KEY);
	}

	if(cadenas1 >= 0) // Creation OK
	{
		fprintf(stderr, "Le semaphore %d est en place, CONS et PROD peuvent commencer.\n", KEY_fin);
	}
	#pragma endregion

	return 0;
}
