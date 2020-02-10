/*****************************************************************

	--> C.c (cons)

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
	printf("-------------------------------Initialisation C--------------------------------------\n");

    #pragma region //Variables et fichiers 
	//Variables semaphore
	int cadenas1, nb1;
    int nb_jeton = 0;
	int retval;
	pid_t pid;

	//variable fichier
	int line_P = 0;
    int line_Px = 0;
    int nb_P, sum_P = 0;
    int status;
    char car;

    #pragma region //Ouverture fichier en lecture (p1 a P4, Px) écriture (Pseq)
    FILE *U_P1, *U_P2, *U_P3, *U_P4, *U_Px, *U_Pseq;
    U_P1 = fopen("P1.txt", "r");
	U_P2 = fopen("P2.txt", "r");
	U_P3 = fopen("P3.txt", "r");
	U_P4 = fopen("P4.txt", "r");
	U_Px = fopen("Px.txt", "r");
	U_Pseq = fopen("Pseq.txt", "a+");
	#pragma endregion

	#pragma region //Test des fichiers
	if(U_P1 == NULL)	
        printf("C--------------------- P1.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- P1.txt -> Fichier ok\n");
	
	if(U_P2 == NULL)	
        printf("C--------------------- P2.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- P2.txt -> Fichier ok\n");
	
	if(U_P3 == NULL)	
        printf("C--------------------- P3.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- P3.txt -> Fichier ok\n");

	if(U_P4 == NULL)	
        printf("C--------------------- P4.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- P4.txt -> Fichier ok\n");

	if(U_Px == NULL)	
        printf("C--------------------- Px.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- Px.txt -> Fichier ok\n");

	if(U_Pseq == NULL)	
		printf("C--------------------- Pseq.txt -> Probleme de fichier\n");
    else
        printf("C--------------------- Pseq.txt -> Fichier ok\n");
	#pragma endregion

	#pragma endregion

    #pragma region //Programme principale
	 
	cadenas1 = DemandeId(KEY_fin); // Identifier le semaphore  
    if(cadenas1 >= 0) // Si le semaphore existe
	{	
		printf("P1---- Semaphore KEY_fin ok\n");
        printf("------------------------------Fin Initialisation C------------------------------------\n\n");

        #pragma region //Attend l'arriver des 4 jetons (Attend)
        do
        {
            printf("C (%d) demande 1 jeton\n", getpid());
            retval = Attend(cadenas1);  //*************** Passe ou attend *****************
            nb_jeton++;
            printf("C ---- Il y a %i / 4 de processus P qui ont terminé!!", nb_jeton);
        } while (nb_jeton < 4);
        #pragma endregion   
            
        #pragma region //Trouver le nombre de ligne dans fichier P1 a P4 et Px
        //Nombre de ligne dans fichier P1.txt
        status = fscanf(U_P1, "%d", &nb_P);
        while (status != EOF)
        {
            line_P += 1;
            sum_P += nb_P;
            status = fscanf(U_P1, "%d", &nb_P);
        } 
        printf("\nLigne de P1 --> %i", line_P);

        //Nombre de ligne dans fichier P2.txt
        status = fscanf(U_P2, "%d", &nb_P);
        while (status != EOF)
        {
            line_P += 1;
            sum_P += nb_P;
            status = fscanf(U_P2, "%d", &nb_P);
        }
        printf("\nLigne de P2 --> %i", line_P);

        //Nombre de ligne dans fichier P3.txt
        status = fscanf(U_P3, "%d", &nb_P);
        while (status != EOF)
        {
            line_P += 1;
            sum_P += nb_P;
            status = fscanf(U_P3, "%d", &nb_P);
        }
        printf("\nLigne de P3 --> %i", line_P);

        //Nombre de ligne dans fichier P4.txt
        status = fscanf(U_P4, "%d", &nb_P);
        while (status != EOF)
        {
            line_P += 1;
            sum_P += nb_P;
            status = fscanf(U_P4, "%d", &nb_P);
        }
        printf("\nLigne de P4 --> %i", line_P);

        //Nombre de ligne dans fichier Px.txt
        status = fscanf(U_Px, "%1c", &car);
        while (status != EOF)
        {
            if (car == '\n')
                line_Px += 1; 
            
            status = fscanf(U_Px, "%1c", &car);
        } 
        #pragma endregion

        #pragma region //Affiche le total de ligne et dit si concored ou pas
        printf("\nIl y a %i ligne(s) dans les fichiers P1 a P4.  \nIl y a %i ligne(s) dans le fichier Px.\n", line_P, line_Px);
       
        if (line_P == line_Px)
        {
            printf("C ---- Voici la sommes --> %i <--\n", sum_P);
            printf("Le nombre de ligne concorde!!\n");
		    fprintf(U_Pseq, "%i", line_Px);    //Ecrire dans Px
        }    
        else
            printf("Le nombre de ligne ne concorde pas!!\n");

        #pragma endregion
	
	}	
	else
		fprintf(stderr, "P1---- Le programme ne trouve cette cle de semaphore.\n");
	#pragma endregion

    #pragma region //Fin de programme
    
    #pragma region //Fermeture des ficher
	fclose(U_P1);
	fclose(U_P2);
	fclose(U_P3);
	fclose(U_P4);
	fclose(U_Px);
	fclose(U_Pseq);
	#pragma endregion

    printf("Fini Bye bye");
    #pragma endregion

	return 0;
}