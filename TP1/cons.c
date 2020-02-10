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
	int cadenas, nb, i, total, add, addedNbr, count, c;
	int retval;

	cadenas = DemandeId(KEY); // Identifier le semaphore
	
	if(cadenas >= 0) // Si le semaphore existe
	{
		while (i<4) // valide que les 4 fichiers ont ouverts et fermés
		{
			retval = Attend(cadenas);
			i++;
		}
		
			FILE *fptr1;			// ajouter les nombre de P1 dans Px
			fptr1 = fopen("P1.txt","r");

				while (!feof(fptr1))
				{
					fscanf(fptr1, "%d", &add);
					addedNbr = addedNbr+add;
					add = 0;			
				}
			fclose(fptr1);

			FILE *fptr2;			// ajouter les nombre de P2 dans Px
			fptr2 = fopen("P2.txt","r");

				while (!feof(fptr2))
				{
					fscanf(fptr2, "%d", &add);
					addedNbr = addedNbr+add;
					add = 0;
				}
			fclose(fptr2);

			FILE *fptr3;			// ajouter les nombre de P3 dans Px
			fptr3 = fopen("P3.txt","r");

				while (!feof(fptr3))
				{
					fscanf(fptr3, "%d", &add);
					addedNbr = addedNbr+add;
					add = 0;
				}
			fclose(fptr3);

			FILE *fptr4;			// ajouter les nombre de P4 dans Px
			fptr4 = fopen("P4.txt","r");

				while (!feof(fptr4))
				{
					fscanf(fptr4, "%d", &add);
					addedNbr = addedNbr+add;
					add = 0;
				}
			fclose(fptr4);


			FILE *fp5;
			fp5 = fopen("./text/p1.txt","r");
				for (c = getc(fp5); c != EOF; c = getc(fp5)) 
						if (c == '\n') // Increment count if this character is newline 
							count = count + 1; 
			fclose(fp5);

						FILE *fp6;
			fp6 = fopen("./text/p2.txt","r");
				for (c = getc(fp6); c != EOF; c = getc(fp6)) 
						if (c == '\n') // Increment count if this character is newline 
							count = count + 1; 
			fclose(fp6);

						FILE *fp7;
			fp7 = fopen("./text/p3.txt","r");
				for (c = getc(fp7); c != EOF; c = getc(fp7)) 
						if (c == '\n') // Increment count if this character is newline 
							count = count + 1; 
			fclose(fp7);

			FILE *fp8;
			fp8 = fopen("./text/p4.txt","r");
				for (c = getc(fp8); c != EOF; c = getc(fp8)) 
						if (c == '\n') // Increment count if this character is newline 
							count = count + 1; 
			fclose(fp8);





			int verificationfinale = 0;
			FILE *fp9;
			fp9 = fopen("./text/px.txt","r");

				for (c = getc(fp9); c != EOF; c = getc(fp9)) 
						if (c == '\n') // Increment count if this character is newline 
							verificationfinale = verificationfinale + 1; 
			
			fclose(fp9);

			if(verificationfinale == count)
			{
				printf("\nDonnée équivalente\n");
			}
			else
			{
				printf("\nErreur !\n");
			}

			printf("\nVerification finale: %d\n",verificationfinale);
			printf("count: %d\n",count);

			printf("L somme des 4 P.c: %d \n", addedNbr);
	}
	else
	{
		fprintf(stderr, "Le programme ne trouve cette cle de semaphore.\n");
	}

	return 0;
}

