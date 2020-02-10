/*****************************************************************

	--> compteur.c

	Le programme "ini.c" doit avoir ete execute 1 fois avant "compteur.c"
	
	Stevens Gagnon
	Departement Informatique
	College Shawinigan
	
******************************************************************/
#include <stdio.h>

#include "jeton.h"
#include "key.h"

int main()
{
	int compteur;
	int idx = 0, nb = 1;
	int retval;

	compteur = DemandeId(KEY); // Identifier le semaphore
	
	if(compteur >= 0) // Si le semaphore existe
	{
        	while((idx = NbJeton(compteur)) <= 100)
        	{
                retval = Signale(compteur);
            
                printf("SYSTEM = %d ... NB = %i ... je suis PID = %d\n", idx, nb++, getpid());
		
                usleep(500000);
        	}
    	}
	else
	{
		fprintf(stderr, "Le programme ne trouve cette cle de semaphore.\n");
	}
	return 0;
}
