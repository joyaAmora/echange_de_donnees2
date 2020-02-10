/*****************************************************************

	--> P2.c (cons / prod)

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
	printf("-------------------------------Initialisation P2--------------------------------------\n");

	#pragma region //Variables et fichiers 
	//Variables semaphore
	int cadenas, cadenas1, nb, nb1;
	int retval;
	pid_t pid;

	//variable fichier
	int nb_P2;
    FILE *U_P2, *U_Px;
    U_P2 = fopen("P2.txt", "a+");

	if(U_P2 == NULL)	
        printf("P2---------------------------- P2.txt -> Probleme de fichier\n");
    else
        printf("P2---------------------------- P2.txt -> Fichier ok\n");
	#pragma endregion


	#pragma region //Programme principale
	cadenas = DemandeId(KEY); // Identifier le semaphore
	cadenas1 = DemandeId(KEY_fin); // Identifier le semaphore   
	

	#pragma region //Initialisation Semaphore key_fin     
	if(cadenas1 >= 0) // Si le semaphore existe
	{	
		printf("P2---- Semaphore KEY_fin ok\n");

		if((nb1 = NbProc(cadenas1)))
		{
			printf("\nP2---- Le semaphore contient %d processus en attente\n\n", nb1);
		}
		else
			printf("\nP2---- Le semaphore contient %d jetons\n\n", NbJeton(cadenas1));
	}	
	else
		fprintf(stderr, "P2---- Le programme ne trouve cette cle de semaphore.\n");
	#pragma endregion*/

	
	if(cadenas >= 0) // Si le semaphore existe
	{
		printf("P2 ------ Semaphore KEY ok\n");
		printf("------------------------------Fin Initialisation P2------------------------------------\n\n");
		do
		{
			#pragma region //Dit si en file ou si jeton disponible
			if((nb = NbProc(cadenas)))
			{
				printf("P2---- Le semaphore contient %d processus en attente\n", nb);
			}
			else
			{
				printf("P2---- Le semaphore contient %d jetons\n", NbJeton(cadenas));
			}
			#pragma endregion
		
			#pragma region //Demande a user le nombre nb_P2
			char scrap;
			printf("P2---- Entrer votre numero ici : ");
			scanf("%i", &nb_P2);
			scanf("%c", &scrap);
			#pragma endregion

			if (nb_P2 >= 0)
			{
				#pragma region //Demande jeton et attend son tour (Attend)
				printf("P2 (%d) demande 1 jeton\n", getpid());
				retval = Attend(cadenas);  //*************** Passe ou attend *****************
				#pragma endregion

				#pragma region //Ces son tour et ecrit dans Px.txt et P2.txt
				if(retval == 0)
				{
					#pragma region //Ecrire dans fichier P2 et Px
					printf("P2 (%d) a obtenu le jeton.\n", getpid());	
					printf("Pause, pour continuer entrer un char");
					char car;
					scanf("%c", &car);
					FILE *U_Px;
					U_Px = fopen("Px.txt", "a+");
					if(U_Px == NULL)	
						printf("P2-------------------------- Px.txt -> Probleme de fichier\n");
					else
					{	
						printf("P2-------------------------- Px.txt -> Fichier ok\n");
						
						//Nombre de ligne dans fichier Px.txt
						char car;
						int line_Px = 1, status;
						status = fscanf(U_Px, "%1c", &car);
						while (status != EOF)
						{
							if (car == '\n')
								line_Px += 1; 
							
							status = fscanf(U_Px, "%1c", &car);
						} 

						fprintf(U_Px, "P2 : %i\n", line_Px);  //Ecrire dans Px    
						fprintf(U_P2, "%i\n", nb_P2);         //Ecrire dans P2
						printf("P2---- Ecriture dans Px et P2 effectué.\n");
						fclose(U_Px);
					}
					#pragma endregion

					#pragma region //Ajoute un jeton et le depose (signale)
					pid = getpid();       //Remet un jeton
					printf("P2 (%d) laisse 1 jeton.\n", pid);

					retval = Signale(cadenas);   //*************** Debloque un processus ou laisse un jeton. *****************

					if(retval == 0)
						printf("P2 (%d) jeton depose.\n\n\n", pid);
					else
						printf("P2---- Probleme d'execution !");
					#pragma endregion
				}
				#pragma endregion
			
				#pragma region //Trouble avec semaphore
				else
				{
					printf("P2---- Probleme d'execution \n");
				}
				#pragma endregion
			}
		} while (nb_P2 >= 0);
	}
	else   //Semaphore existe pas
	{
		fprintf(stderr, "P2---- Le programme ne trouve cette cle de semaphore.\n");
	}
	#pragma endregion


	#pragma region //Fin de P2
	fclose(U_P2);
	pid = getpid();       //Remet un jeton
	printf("P2 (%d) laisse 1 jeton dans cadenas1\n", pid);

	retval = Signale(cadenas1);   //*************** Debloque un processus ou laisse un jeton. *****************

	if(retval == 0)
		printf("P2 (%d) jeton depose.\n", pid);
	else
		printf("P2--- Probleme d'execution !");
	
	printf("*****************P2 se ferme**************************\n");
	#pragma endregion

	return 0;
}
