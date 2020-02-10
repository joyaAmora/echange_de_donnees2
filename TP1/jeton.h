/************************************************************************

	--> jeton.h

	Module d'etude du fonctionnement des semaphores

	Stevens Gagnon
	Departement Informatique
	College Shawinigan
	
************************************************************************/
   
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//----------------------------------------------------------------------------
// Creation de la structure du semaphore "IPC_CREAT"
// Avec la cle "key"
// Accessible a tous  0666	:
//								system	= 0
//								User 	= 6
//								Group	= 6
//								Others	= 6
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
int InitSemaphore(int key, int nbjeton)
{
	int id;  // ID du semaphore.
	  
	id = semget(key, 1, 0666 | IPC_CREAT); /* Creation du semaphore avec la cle KEY et les acces 0666. */

	if(id >= 0) // Creation OK
	{
		if( semctl(id, 0, SETVAL, nbjeton) >= 0) 
		{
			return(id);
		}
		else
		{
			fprintf( stderr, "Semaphore non gerable\n");
			return(-1);
		}
	}
	else
	{
		fprintf(stderr, "Ne peut pas creer le semaphore.\n");
		return(-2);
	}
	return -3;
}

//----------------------------------------------------------------------------
// Retourne le nombre de jetons diponibles dans le semaphore

int NbJeton(int id)
{
	int nb_proc;
	  
	return( semctl(id, 0, GETVAL));
}

//----------------------------------------------------------------------------
// Retourne le nombre processus en attentes dans le semaphore


int NbProc(int id)
{
	int nb_proc;
	  
	return( semctl(id, 0, GETNCNT));
}

//----------------------------------------------------------------------------
// Obtenir l'ID du semaphore qui utilise la cle KEY.

int DemandeId(int key)
{
	return( semget(key, 1, 0666));

}

//----------------------------------------------------------------------------
// Laisse passer le premier processus de la liste, si processus il y a, sinon depose 1 jeton de plus
// Retourne ( 0 = OK ) (  -1 = Probleme )

int Signale(int id)
{
	struct sembuf sem_op;
	if(id >= 0)
	{
		sem_op.sem_num = 0;	// Quel semaphore dans le vecteur :
		sem_op.sem_op = 1; 	// Ajouter 1 au nombre de jeton dans le semaphore position 0
		sem_op.sem_flg = 0;	// Force l'execution ˆ attendre la completion de l'operation

		return( semop(id, &sem_op, 1));
	}
	return -1;
}

//----------------------------------------------------------------------------
// Retire 1 jeton du semaphore si disponible, sinon le processus se place en attente d'un jeton
// Retourne ( 0 = OK ) (  -1 = Probleme )

int Attend(int id)
{
	struct sembuf sem_op;
	if(id >= 0)
	{
		sem_op.sem_num = 0;	// Quel semaphore dans le vecteur :
		sem_op.sem_op = -1;	// Soustraire 1 au nombre de jeton dans le semaphore position 0
		sem_op.sem_flg = 0;	// Force l'execution a attendre la completion de l'operation

		return( semop(id, &sem_op, 1)); 
	}
	return -1;
}
