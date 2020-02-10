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
	int cadenas, nb;
	int retval;
	pid_t pid;

	cadenas = DemandeId(KEY);  // Identifier le semaphore
	
	if(cadenas >= 0) // Si le semaphore existe
	{
	
		if((nb = NbProc(cadenas)))
		{
			printf("\nLe semaphore contient %d Processus\n\n", NbProc(cadenas));
		}
		else
		{
			printf("\nLe semaphore contient %d jeton\n\n", NbJeton(cadenas));
		}
			
		pid = getpid();
		printf("Le producteur %d laisse 1 jeton.\n", pid);

		retval = Signale(cadenas);   //*************** Debloque un processus ou laisse un jeton. *****************

		if(retval == 0)
		{
			printf("Le producteur %d jeton depose.\n", pid);
		}
		else
		{
			printf("Probleme d'execution !");
		}
	}
	else
	{
		fprintf(stderr, "Le programme ne trouve cette cle de semaphore.\n");
	}

	return 0;
}
