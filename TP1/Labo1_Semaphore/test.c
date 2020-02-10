#include <stdio.h>

int main()
{
    int nb = 0;
    int line_p = 0;
    int sum = 0;
    int status;
    char str_int[10]; 
    int c;
    char car;

    FILE *U_fichier;
    U_fichier = fopen("test.txt", "r");

    FILE *U_fichier1;
    U_fichier1 = fopen("test1.txt", "r");

    if(U_fichier == NULL)	
        printf("--------------------- test.txt -> Probleme de fichier\n");
    else
        printf("--------------------- test.txt -> Fichier ok\n");

    if(U_fichier1 == NULL)	
        printf("--------------------- test1.txt -> Probleme de fichier\n");
    else
        printf("--------------------- test1.txt -> Fichier ok\n");
    
    //pour les nombre seulement
    status = fscanf(U_fichier, "%d", &c);
    while (status != EOF)
    {
        line_p += 1;
        printf("%i --- %i\n", line_p, c);

        status = fscanf(U_fichier, "%d", &c);
    } 
    
    status = fscanf(U_fichier1, "%d", &c);
    while (status != EOF)
    {
        line_p += 1;
        printf("%i --- %i\n", line_p, c);

        status = fscanf(U_fichier1, "%d", &c);
    } 


    /*
    status = fscanf(U_fichier, "%1c", &car);
    while (status != EOF)
    {
        if (car == '\n')
           line_p += 1; 
        
        status = fscanf(U_fichier, "%1c", &car);
    } 
    */

    printf("Nb de ligne = %i\n", line_p);

    fclose(U_fichier);
    return 0;
}
