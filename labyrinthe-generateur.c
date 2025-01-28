#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int nbColonnes, nbLignes;
#define MAX_SIZE 20

int testResolvableRecursive(char labyrinthe[MAX_SIZE][MAX_SIZE], int caseVerif[MAX_SIZE][MAX_SIZE], int x, int y)
{
    if (x < 0 || x >= nbColonnes || y < 0 || y >= nbLignes || labyrinthe[y][x] == '#' || caseVerif[y][x] == 1)
        return 0;

    if (x == nbColonnes - 1 && y == nbLignes - 1)
        return 1;

    caseVerif[y][x] = 1;

    int longueurs[4];
    longueurs[0] = testResolvableRecursive(labyrinthe, caseVerif, x + 1, y);
    longueurs[1] = testResolvableRecursive(labyrinthe, caseVerif, x - 1, y);
    longueurs[2] = testResolvableRecursive(labyrinthe, caseVerif, x, y + 1);
    longueurs[3] = testResolvableRecursive(labyrinthe, caseVerif, x, y - 1);

    int minLongueur = 0;
    for (int i = 0; i < 4; i++)
    {
        if (longueurs[i] > 0 && (minLongueur == 0 || longueurs[i] < minLongueur))
        {
            minLongueur = longueurs[i];
        }
    }
    caseVerif[y][x] = 0; // pour pouvoir passer par la case lors des futurs chemins
    if (minLongueur > 0)
    {
        return minLongueur + 1;
    }
    return 0;
}

int testResolvable(char labyrinthe[MAX_SIZE][MAX_SIZE])
{
    int caseVerif[MAX_SIZE][MAX_SIZE];
    for (int j = 0; j < nbLignes; j++)
    {
        for (int i = 0; i < nbColonnes; i++)
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
        for (int j = 0; j < nbLignes; j++)
        {
            for (int i = 0; i < nbColonnes; i++)
            {
                fprintf(flux, "%c", labyrinthe[j][i]); // mettre "%c" car fprintf a pour argument une chaine de caractere et pas un char
            }
            fprintf(flux, "\n");
        }
        fclose(flux);
    }
}

int compterImpasses(char labyrinthe[MAX_SIZE][MAX_SIZE])
{
    int impasses = 0;
    for (int y = 0; y < nbLignes; y++)
    {
        for (int x = 0; x < nbColonnes; x++)
        {
            if (labyrinthe[y][x] == '.')
            {
                int voisins = 0;
                if (x > 0 && labyrinthe[y][x - 1] == '.')
                    voisins++;
                if (x < nbColonnes - 1 && labyrinthe[y][x + 1] == '.')
                    voisins++;
                if (y > 0 && labyrinthe[y - 1][x] == '.')
                    voisins++;
                if (y < nbLignes - 1 && labyrinthe[y + 1][x] == '.')
                    voisins++;

                if (voisins == 1)
                {
                    impasses++;
                }
            }
        }
    }
    return impasses;
}

// Evalue la difficulté du labyrinthe
void evaluerDifficulte(char labyrinthe[MAX_SIZE][MAX_SIZE], int longueurChemin)
{
    int impasses = compterImpasses(labyrinthe);

    printf("Nombre d'impasses: %d\n", impasses);

    int difficulte = impasses + longueurChemin;
    if (difficulte < 15)
    {
        printf("Difficulte: Facile\n");
    }
    else if (difficulte < 30)
    {
        printf("Difficulte: Moyen\n");
    }
    else
    {
        printf("Difficulte: Difficile\n");
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
            nbColonnes = rand() % 7 + 5;
            nbLignes = rand() % 7 + 5;
        }
        else if (modeDim == 2)
        {
            while (nbColonnes < 1 || nbColonnes > 20)
            {
                printf("Entrez la longueur du labyrinthe (nombre de colonnes, maximum 20)\n");
                scanf("%d", &nbColonnes);
            }
            while (nbLignes < 1 || nbLignes > 20)
            {
                printf("Entrez la largeur du labyrinthe (nombre de lignes, maximum 20)\n");
                scanf("%d", &nbLignes);
            }
        }
    }
    printf("%d  %d \n", nbColonnes, nbLignes);
    char labyrinthe[MAX_SIZE][MAX_SIZE];
    char CARACTERES[2] = {'#', '.'}; // #:mur   .: vide   potentiellement à modifier
    int longueurChemin = 0;
    while (longueurChemin == 0)
    {
        for (int j = 0; j < nbLignes; j++)
        { // création labyrinthe
            for (int i = 0; i < nbColonnes; i++)
            {
                int caractereNb = rand() % 2;
                labyrinthe[j][i] = CARACTERES[caractereNb];
            }
        }
        labyrinthe[0][0] = '.';
        labyrinthe[nbLignes - 1][nbColonnes - 1] = '.';

        // test de resolvabilité
        longueurChemin = testResolvable(labyrinthe);
    }
    labyFichierTxt(labyrinthe);
    printf("Voici votre labyrinthe (resolvable en %d mouvements minimum)\n", longueurChemin - 1); // affichage du labyrinthe
    for (int j = 0; j < nbLignes; j++)
    {
        for (int i = 0; i < nbColonnes; i++)
        {
            printf(" %c ", labyrinthe[j][i]); // espace entre chaque caractère
        }
        printf("\n");
    }
    evaluerDifficulte(labyrinthe, longueurChemin);
    printf("Entrez un caractere pour quitter...\n");
    scanf("%d"); // pas mettre %c car il va prendre le \n du terminal
    return 0;
}