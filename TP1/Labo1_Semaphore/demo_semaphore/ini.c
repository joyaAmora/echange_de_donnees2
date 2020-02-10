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
	int cadenas;


	#pragma endregion

	cadenas = InitSemaphore(KEY, jetons_de_depart);  // Met en place un semaphore avec jetons_de_depart jeton(s)
	
	if(cadenas >= 0) // Creation OK
	{
		fprintf(stderr, "Le semaphore %d est en place, CONS et PROD peuvent commencer.\n", KEY);
	}

	return 0;
}
