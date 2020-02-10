/*****************************************************************

	--> P3.c (cons / prod)

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
	printf("-------------------------------Initialisation P3-----------------------------------\n");

	#pragma region //Variables et fichiers 
	//Variables semaphore
	int cadenas, cadenas1, nb, nb1;
	int retval;
	pid_t pid;

	//variable fichier
	int nb_P3;
    FILE *U_P3, *U_Px;
    U_P3 = fopen("P3.txt", "a+");

	if(U_P3 == NULL)	
        printf("P3---------------------------- P3.txt -> Probleme de fichier\n");
    else
        printf("P3---------------------------- P3.txt -> Fichier ok\n");
	#pragma endregion


	#pragma region //Programme principale
	cadenas = DemandeId(KEY); // Identifier le semaphore
	cadenas1 = DemandeId(KEY_fin); // Identifier le semaphore   
	

	#pragma region //Initialisation Semaphore key_fin     
	if(cadenas1 >= 0) // Si le semaphore existe
	{	
		printf("P3---- Semaphore KEY_fin ok\n");

		if((nb1 = NbProc(cadenas1)))
		{
			printf("\nP3---- Le semaphore contient %d processus en attente\n\n", nb1);
		}
		else
			printf("\nP3---- Le semaphore contient %d jetons\n\n", NbJeton(cadenas1));
	}	
	else
		fprintf(stderr, "P3---- Le programme ne trouve cette cle de semaphore.\n");
	#pragma endregion*/

	
	if(cadenas >= 0) // Si le semaphore existe
	{
		printf("P3 ------ Semaphore KEY ok\n");
		printf("------------------------------Fin Initialisation P2------------------------------------\n\n");
		do
		{
			#pragma region //Dit si en file ou si jeton disponible
			if((nb = NbProc(cadenas)))
			{
				printf("P3---- Le semaphore contient %d processus en attente\n", nb);
			}
			else
			{
				printf("P3---- Le semaphore contient %d jetons\n", NbJeton(cadenas));
			}
			#pragma endregion
		
			#pragma region //Demande a user le nombre nb_P3
			char scrap;
			printf("P3---- Entrer votre numero ici : ");
			scanf("%i", &nb_P3);
			scanf("%c", &scrap);
			#pragma endregion

			if (nb_P3 >= 0)
			{
				#pragma region //Demande jeton et attend son tour (Attend)
				printf("P3 (%d) demande 1 jeton\n", getpid());
				retval = Attend(cadenas);  //*************** Passe ou attend *****************
				#pragma endregion

				#pragma region //Ces son tour et ecrit dans Px.txt et P3.txt
				if(retval == 0)
				{
					#pragma region //Ecrire dans fichier P3 et Px
					printf("P3 (%d) a obtenu le jeton.\n", getpid());	
					printf("Pause, pour continuer entrer un char");
					char car;
					scanf("%c", &car);
					FILE *U_Px;
					U_Px = fopen("Px.txt", "a+");
					if(U_Px == NULL)	
						printf("P3-------------------------- Px.txt -> Probleme de fichier\n");
					else
					{	
						printf("P3-------------------------- Px.txt -> Fichier ok\n");

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

						fprintf(U_Px, "P3 : %i\n", line_Px);  //Ecrire dans Px    
						fprintf(U_P3, "%i\n", nb_P3);         //Ecrire dans P3
						printf("P3---- Ecriture dans Px et P3 effectué.\n");
						fclose(U_Px);
					}
					#pragma endregion

					#pragma region //Ajoute un jeton et le depose (signale)
					pid = getpid();       //Remet un jeton
					printf("P3 (%d) laisse 1 jeton.\n", pid);

					retval = Signale(cadenas);   //*************** Debloque un processus ou laisse un jeton. *****************

					if(retval == 0)
						printf("P3 (%d) jeton depose.\n\n\n", pid);
					else
						printf("P3---- Probleme d'execution !");
					#pragma endregion
				}
				#pragma endregion
			
				#pragma region //Trouble avec semaphore
				else
				{
					printf("P3---- Probleme d'execution \n");
				}
				#pragma endregion
			}
		} while (nb_P3 >= 0);
	}
	else   //Semaphore existe pas
	{
		fprintf(stderr, "P3---- Le programme ne trouve cette cle de semaphore.\n");
	}
	#pragma endregion


	#pragma region //Fin de P3
	fclose(U_P3);
	pid = getpid();       //Remet un jeton
	printf("P3 (%d) laisse 1 jeton dans cadenas1\n", pid);

	retval = Signale(cadenas1);   //*************** Debloque un processus ou laisse un jeton. *****************

	if(retval == 0)
		printf("P3 (%d) jeton depose.\n", pid);
	else
		printf("P3--- Probleme d'execution !");
	
	printf("*****************P3 se ferme**************************\n");
	#pragma endregion

	return 0;
}