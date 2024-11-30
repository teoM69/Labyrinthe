#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int colonnes, lignes;
#define MAX_SIZE 20

int testResolvableRecursive(char labyrinthe[MAX_SIZE][MAX_SIZE], int caseVerif[MAX_SIZE][MAX_SIZE], int x, int y)
{
    if (x < 0 || x >= colonnes || y < 0 || y >= lignes)
        return 0;
    if (labyrinthe[y][x] == '#' || caseVerif[y][x] == 1)
        return 0;
    if (x == colonnes - 1 && y == lignes - 1)
        return 1;
    caseVerif[y][x] = 1;
    if (testResolvableRecursive(labyrinthe, caseVerif, x + 1, y) ||
        testResolvableRecursive(labyrinthe, caseVerif, x - 1, y) ||
        testResolvableRecursive(labyrinthe, caseVerif, x, y + 1) ||
        testResolvableRecursive(labyrinthe, caseVerif, x, y - 1))
    {
        return 1;
    }
    return 0;
}

int testResolvable(char labyrinthe[MAX_SIZE][MAX_SIZE])
{
    int caseVerif[MAX_SIZE][MAX_SIZE];
    for (int j = 0; j < lignes; j++)
    {
        for (int i = 0; i < colonnes; i++)
        {
            caseVerif[j][i] = 0;
        }
    }
    return testResolvableRecursive(labyrinthe, caseVerif, 0, 0);
}

void labyFichierTxt(char labyrinthe[MAX_SIZE][MAX_SIZE])
{
    FILE *flux = NULL;
    flux = fopen("labyrinthe.txt", "w");
    if (flux != NULL)
    {
        for (int j = 0; j < lignes; j++)
        {
            for (int i = 0; i < colonnes; i++)
            {
                fprintf(flux, "%c", labyrinthe[j][i]); // mettre "%c" car fprintf a pour argument une chaine de caractere et pas un char
            }
            fprintf(flux, "\n");
        }
        fclose(flux);
    }
}

int main(void)
{

    // choix longueur (x), largeur (y)
    int modeDim = 0;
    srand((unsigned)time(NULL));
    while (modeDim != 1 && modeDim != 2)
    {
        printf("Voulez-vous que les dimensions du labyrinthe soient aleatoires ou choisies par vous?\n");
        printf("Tapez: 1-Aleatoires  2-Choisies par vous\n");

        scanf("%d", &modeDim);
        if (modeDim == 1)
        {
            colonnes = rand() % 7 + 5;
            lignes = rand() % 7 + 5;
        }
        else if (modeDim == 2)
        {
            printf("Entrez la longueur du labyrinthe (nombre de colonnes)\n");
            scanf("%d", &colonnes);
            printf("Entrez la largeur du labyrinthe (nombre de lignes)\n");
            scanf("%d", &lignes);
        }
    }
    printf("%d  %d \n", colonnes, lignes);
    char labyrinthe[MAX_SIZE][MAX_SIZE];
    char CARACTERES[2] = {'#', '.'}; // #:mur   .: vide   potentiellement à modifier
    int resolvable = 0;
    while (resolvable == 0)
    {
        for (int j = 0; j < lignes; j++)
        { // création labyrinthe
            for (int i = 0; i < colonnes; i++)
            {
                int caractereNb = rand() % 2 > 0 ? 1 : 0; // probabilité d'avoir un mur de 1/5 (pas parfait)
                labyrinthe[j][i] = CARACTERES[caractereNb];
            }
        }
        labyrinthe[0][0] = '.';
        labyrinthe[colonnes - 1][lignes - 1] = '.';

        labyFichierTxt(labyrinthe);

        // test de resolvabilité
        resolvable = testResolvable(labyrinthe);
    }
    labyFichierTxt(labyrinthe);
    printf("Voici votre labyrinthe\n"); // affichage du labyrinthe
    for (int j = 0; j < lignes; j++)
    {
        for (int i = 0; i < colonnes; i++)
        {
            printf(" %c ", labyrinthe[j][i]); // espace entre chaque caractère
        }
        printf("\n");
    }
}