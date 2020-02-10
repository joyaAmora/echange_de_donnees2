/*****************************************************************

	--> P4.c (cons / prod)

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
	printf("-------------------------------Initialisation P4--------------------------------------\n");

	#pragma region //Variables et fichiers 
	//Variables semaphore
	int cadenas, cadenas1, nb, nb1;
	int retval;
	pid_t pid;

	//variable fichier
	int nb_P4;
    FILE *U_P4, *U_Px;
    U_P4 = fopen("P4.txt", "a+");

	if(U_P4 == NULL)	
        printf("P4---------------------------- P4.txt -> Probleme de fichier\n");
    else
        printf("P4---------------------------- P4.txt -> Fichier ok\n");
	#pragma endregion


	#pragma region //Programme principale
	cadenas = DemandeId(KEY); // Identifier le semaphore
	cadenas1 = DemandeId(KEY_fin); // Identifier le semaphore   
	

	#pragma region //Initialisation Semaphore key_fin
	if(cadenas1 >= 0) // Si le semaphore existe
	{	
		printf("P4---- Semaphore KEY_fin ok\n");

		if((nb1 = NbProc(cadenas1)))
		{
			printf("\nP4---- Le semaphore contient %d processus en attente\n\n", nb1);
		}
		else
			printf("\nP4---- Le semaphore contient %d jetons\n\n", NbJeton(cadenas1));
	}	
	else
		fprintf(stderr, "P4---- Le programme ne trouve cette cle de semaphore.\n");
	#pragma endregion

	
	if(cadenas >= 0) // Si le semaphore existe
	{
		printf("P4 ------ Semaphore KEY ok\n");
		printf("------------------------------Fin Initialisation P4------------------------------------\n\n");
		do
		{
			#pragma region //Dit si en file ou si jeton disponible
			if((nb = NbProc(cadenas)))
			{
				printf("P4---- Le semaphore contient %d processus en attente\n", nb);
			}
			else
			{
				printf("P4---- Le semaphore contient %d jetons\n", NbJeton(cadenas));
			}
			#pragma endregion
		
			#pragma region //Demande a user le nombre nb_P4
			char scrap;
			printf("P4---- Entrer votre numero ici : ");
			scanf("%i", &nb_P4);
			scanf("%c", &scrap);
			#pragma endregion

			if (nb_P4 >= 0)
			{
				#pragma region //Demande jeton et attend son tour (Attend)
				printf("P4 (%d) demande 1 jeton\n", getpid());
				retval = Attend(cadenas);  //*************** Passe ou attend *****************
				#pragma endregion

				#pragma region //Ces son tour et ecrit dans Px.txt et P2.txt
				if(retval == 0)
				{
					#pragma region //Ecrire dans fichier P4 et Px
					printf("P4 (%d) a obtenu le jeton.\n", getpid());	
					printf("Pause, pour continuer entrer un char");
					char car;
					scanf("%c", &car);
					FILE *U_Px;
					U_Px = fopen("Px.txt", "a+");
					if(U_Px == NULL)	
						printf("P4-------------------------- Px.txt -> Probleme de fichier\n");
					else
					{	
						printf("P4-------------------------- Px.txt -> Fichier ok\n");
						
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

						fprintf(U_Px, "P4 : %i\n", line_Px);  //Ecrire dans Px    
						fprintf(U_P4, "%i\n", nb_P4);         //Ecrire dans P4
						printf("P4---- Ecriture dans Px et P4 effectué.\n");
						fclose(U_Px);
					}
					#pragma endregion

					#pragma region //Ajoute un jeton et le depose (signale)
					pid = getpid();       //Remet un jeton
					printf("P4 (%d) laisse 1 jeton.\n", pid);

					retval = Signale(cadenas);   //*************** Debloque un processus ou laisse un jeton. *****************

					if(retval == 0)
						printf("P4 (%d) jeton depose.\n\n\n", pid);
					else
						printf("P4---- Probleme d'execution !");
					#pragma endregion
				}
				#pragma endregion
			
				#pragma region //Trouble avec semaphore
				else
				{
					printf("P4---- Probleme d'execution \n");
				}
				#pragma endregion
			}
		} while (nb_P4 >= 0);
	}
	else   //Semaphore existe pas
	{
		fprintf(stderr, "P4---- Le programme ne trouve cette cle de semaphore.\n");
	}
	#pragma endregion


	#pragma region //Fin de P4
	fclose(U_P4);
	pid = getpid();       //Remet un jeton
	printf("P4 (%d) laisse 1 jeton dans cadenas1\n", pid);

	retval = Signale(cadenas1);   //*************** Debloque un processus ou laisse un jeton. *****************

	if(retval == 0)
		printf("P4 (%d) jeton depose.\n", pid);
	else
		printf("P4--- Probleme d'execution !");
	
	printf("*****************P4 se ferme**************************\n");
	#pragma endregion

	return 0;
}