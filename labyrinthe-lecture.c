#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int nbColonnes, nbLignes = 0;
    char labyrintheString[400], labyrinthe[20][20];
    FILE *fichier = fopen("labyrinthe.txt", "r");
    if (fichier != NULL)
    {
        char ligne[21];                           // le nb doit être plus grand que le nb de caracteres: donc 21 car 21>20
        while (fscanf(fichier, "%s", ligne) == 1) // lecture du fichier texte
        {
            if (nbLignes == 0)
            {
                nbColonnes = strlen(ligne);
            }
            nbLignes++;
            strcat(labyrintheString, ligne);
        }
        fclose(fichier);
    }
    // mise en place du labyrinthe dans une matrice
    int caractereIndex = 0;
    for (int i = 0; i < nbLignes; i++)
    {
        for (int j = 0; j < nbColonnes; j++)
        {
            labyrinthe[i][j] = labyrintheString[caractereIndex];
            printf("%c", labyrinthe[i][j]);
            caractereIndex++;
        }
        printf("\n");
    }

    return 0;
}
