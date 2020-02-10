/*****************************************************************

	--> cons.c

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
	int cadenas, nb;
	int retval;

	cadenas = DemandeId(KEY); // Identifier le semaphore
	
	if(cadenas >= 0) // Si le semaphore existe
	{
		if((nb = NbProc(cadenas)))
		{
			printf("\nLe semaphore contient %d processus en attente\n\n", nb);
		}
		else
		{
			printf("\nLe semaphore contient %d jetons\n\n", NbJeton(cadenas));
		}
		
		printf("Le consomateur %d demande 1 jeton\n", getpid() );

		retval = Attend(cadenas);  //*************** Passe ou attend *****************

		if(retval == 0)
		{
			printf("Le consomateur %d a obtenu le jeton.\n", getpid());		}
		else
		{
			printf("Probleme d'execution \n");
		}
	}
	else
	{
		fprintf(stderr, "Le programme ne trouve cette cle de semaphore.\n");
	}

	return 0;
}

