/*****************************************************************

	--> server-mux-pt.c

	Module d'utilisation d'un serveur connexion unique via un socket TCP sur Unix

	pour compiler 	==> gcc -pthread prog.c -o prog
	ou		==> gcc prog.c -o prog -lpthread

	Stevens Gagnon
	Departement Informatique
	College Shawinigan

******************************************************************/

	#define MAX_BUFFER 100

// ---- Parametres specifique au serveur

	#define ADR_LISTEN	"INADDR_ANY"		// "INADDR_ANY" ou "192.168.2.2"
	#define port_net  2083	//--> Port sur lequel le serveur attend

	#define nb_demo 5	//--> nombre de connexions terminer avant la fin du programme

/* ------------------------------------------------------------- */


	#include <pthread.h>

	#include "sg_tcp.h"

	pthread_mutex_t copie;

//---------------------------------------------------------------- Processus Client
void * connexion (long *cli)
{
	int n, lg;
	long client;
	char buffer_in[MAX_BUFFER+1];
    char buffer_out[MAX_BUFFER+1];

    client = *cli;
    pthread_mutex_unlock(&copie); // J'ai copie mon Socket dans une variable privee


    buffer_in[MAX_BUFFER] = 0;
    buffer_out[MAX_BUFFER] = 0;

	printf("\n---------------- Serveur ----------------\n");

	bzero(buffer_in, MAX_BUFFER);

	if ((lg = recv(client,buffer_in, MAX_BUFFER, 0)) < 0)
	{
		perror("\n\nERREUR connexion-read\n\n");
	}
	else
	{
		buffer_in[lg] = 0;
		printf("\nDatagram recu: \nLongueur(%i) \n-->%s<--\n\n", lg, buffer_in);

	 	bzero(buffer_out,MAX_BUFFER);
	 	snprintf( buffer_out, MAX_BUFFER, "}%s{", buffer_in );

		printf("\nDtatagramme transmit: \nLongueur(%i) \n-->%s<--\n\n", lg+2, buffer_out);
		if ((n = send(client,buffer_out,strlen(buffer_out), 0)) < 0)
			perror("\n\nERREUR connexion-write\n\n");

		close(client);
		pthread_exit(NULL);
	}

	return 0;
}

//------------------------------------------------------------------ main

int
main(void)
{
	int 		serveur;
	int			client;
	int			demo;

	pthread_t thread;
	pthread_t list_thread[nb_demo];


	if( ! pthread_mutex_init(&copie, NULL))
	{
		serveur = setup_tcp_serveur(ADR_LISTEN, port_net, MAX_BUFFER, 0, 0);

		if ( serveur != -1 )
		{
			printf("\n*****************************************************************\n");
			printf("DEBUT du programme serveur d'invitations pour %i connexions\n",nb_demo);
			printf("*****************************************************************\n");


			demo = nb_demo-1;
			while( demo >= 0 )
			{
				pthread_mutex_lock(&copie); // Laisser copier le Socket par le pThread
				client = accept_tcp_client(serveur);

				if (client != -1)
				{
					pthread_create(&list_thread[demo--], NULL, (void*)&connexion, &client);
				}
				else
				{
					pthread_mutex_unlock(&copie);
				}
			}

			close(serveur);

			printf("\n*****************************************************************\n");
			printf("Fin du programme serveur d'invitations pour %i connexions\n",nb_demo);
			printf("*****************************************************************\n");


			// Attendons que tous les clients se terminent avant de fermer le main

			demo = nb_demo-1;
			while( demo >= 0 )
				pthread_join(list_thread[demo--], NULL);

			printf("\n*****************************************************************\n");
			printf("Fin du programme SERVEUR principal\n");
			printf("*****************************************************************\n\n");

		}
	}
	else
		printf("Mutex\n");

	pthread_mutex_destroy(&copie);

	return 0;
}

//------------------------------------------------------------------


