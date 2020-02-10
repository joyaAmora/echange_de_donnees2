/*****************************************************************

	--> server-mux-fork.c

	Module d'utilisation d'un serveur connexion unique via un socket TCP sur Unix

	Stevens Gagnon
	Departement Informatique
	College Shawinigan

******************************************************************/

// Pour simuler une panne du serveur racine
// utilisez "kill" sans option

	#define MAX_BUFFER 100

// ---- Parametres specifique au serveur* ---- Parametres du serveur ---------------------------------- */

	#define ADR_LISTEN	"INADDR_ANY"		// "INADDR_ANY" ou "192.168.2.2" ou "amx.xoox.ca"
	#define port_net  2083	//-->  Port sur lequel le serveur attend

	#define nb_demo 3	//-->  nombre de connexions terminer avant la fin du programme

/* ------------------------------------------------------------- */

#include "sg_tcp.h"

//---------------------------------------------------------------- Code qui sera utilise par le Processus Client

void connexion (long client, int demo)
{
	int n, lg;

	char buffer_in[MAX_BUFFER+1];
	char buffer_out[MAX_BUFFER+1];

    buffer_in[MAX_BUFFER] = 0;
    buffer_out[MAX_BUFFER] = 0;

	printf("\n---------------- DEBUT serveur #%i ----------------\n", demo);

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
	}

	printf("\n---------------- FIN serveur #%i ----------------\n\n\n", demo);
}

//---------------------------------------------------------------- main

int
main()
{
	int 	serveur;
	int		client;
	int		demo;
	int		pid;

	char 		buffer1[MAX_BUFFER],buffer2[MAX_BUFFER];

	serveur = setup_tcp_serveur(ADR_LISTEN, port_net, MAX_BUFFER, 0, 0);

	if ( serveur != -1 )
	{
		printf("\n*****************************************************************\n");
		printf("DEBUT du programme serveur d'invitations pour %i connexions\n",nb_demo);
		printf("*****************************************************************\n");

		demo = 0;
		while( (++demo) <= nb_demo )
		{
			client = accept_tcp_client(serveur);

 			if (client != -1)
			{

				printf("--- AVANT FORK -----> getpid : %i\n", getpid()); // ---------------------> Trace sur le PID pour demonstration

				if ((pid = fork()) < 0)
				{
					perror("\n\nERREUR fork\n\n");    /* Il y a pas eu de nouveau processus */
				}
				else
				{

					printf("--- APRES FORK ----->  getpid : %i - PID : %i\n", getpid(), pid); // -> Trace sur le PID pour demonstration

					if( pid )
					{ // --> Je suis le parent qui attend sur le port : port_net
                                	  // --> Dans mon monde le socket CLIENT ne doit pas etre utilise
						close(client);
					}
					else
					{ // --> Je suis un enfant sur un port dynamique 49100+ !!
                           		  // --> Dans mon monde le socket SERVEUR ne doit pas etre utilise
						
						close(serveur);
						connexion(client, demo);
						close(client);

						exit(EXIT_SUCCESS);	// --> ICI DOIT SE TERMINER LE PROCESSUS ENFANT
									// --> Sinon le processus ENFANT va utiliser du code concu pour le PARENT
					}
				}
			}
		}
		close(serveur);
		printf("\n*****************************************************************\n");
		printf("Fin du programme serveur d'invitations pour %i connexions\n",nb_demo);
		printf("*****************************************************************\n");
	}
}
