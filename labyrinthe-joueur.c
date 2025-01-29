#include <stdio.h>
#include "labyrinthe-lecture.h"

void afficheDeplacements(char cheminParcouru[TAILLE_MAX][TAILLE_MAX])
{
    printf("\n");
    for (int j = 0; j < nbLignes; j++)
    {
        for (int i = 0; i < nbColonnes; i++)
        {
            printf("%c", cheminParcouru[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    lireFichier();
    int x = 0, y = 0;
    char cheminParcouru[TAILLE_MAX][TAILLE_MAX];
    char deplacement;

    for (int i = 0; i < TAILLE_MAX; i++)
        for (int j = 0; j < TAILLE_MAX; j++)
            cheminParcouru[i][j] = ' ';

    // comptage du nombres de cases avant croisement ou mur
    while (x != nbColonnes - 1 || y != nbLignes - 1)
    {
        int casesDroite = 0, casesGauche = 0, casesHaut = 0, casesBas = 0;
        while (y + casesBas < nbLignes - 1 && labyrinthe[y + casesBas + 1][x] != '#')
        {
            if (casesBas == 0 || (labyrinthe[y + casesBas][x + 1] == '#' || x == nbColonnes - 1) && (labyrinthe[y + casesBas][x - 1] == '#' || x == 0))
            {
                casesBas++;
            }
            else
            {
                break;
            }
        }
        while (x + casesDroite < nbColonnes - 1 && labyrinthe[y][x + casesDroite + 1] != '#')
        {
            if (casesDroite == 0 || (labyrinthe[y + 1][x + casesDroite] == '#' || y == nbLignes - 1) && (labyrinthe[y - 1][x + casesDroite] == '#' || y == 0))
            {
                casesDroite++;
            }
            else
            {
                break;
            }
        }
        while (y - casesHaut > 0 && labyrinthe[y - casesHaut - 1][x] != '#')
        {
            if (casesHaut == 0 || (labyrinthe[y - casesHaut][x + 1] == '#' || x == nbColonnes - 1) && (labyrinthe[y - casesHaut][x - 1] == '#' || x == 0))
            {

                casesHaut++;
            }
            else
            {
                break;
            }
        }
        while (x - casesGauche > 0 && labyrinthe[y][x - casesGauche - 1] != '#')
        {
            if (casesGauche == 0 || (labyrinthe[y + 1][x - casesGauche] == '#' || y == nbLignes - 1) && (labyrinthe[y - 1][x - casesGauche] == '#' || y == 0))
            {
                casesGauche++;
            }
            else
            {
                break;
            }
        }

        printf("Vous pouvez aller:\n");
        casesHaut > 0 ? printf("%d case(s) vers le haut\n", casesHaut) : 0;
        casesGauche > 0 ? printf("%d case(s) vers la gauche\n", casesGauche) : 0;
        casesBas > 0 ? printf("%d case(s) vers le bas\n", casesBas) : 0;
        casesDroite > 0 ? printf("%d case(s) vers la droite\n", casesDroite) : 0;
        if (casesHaut == 0 && casesBas == 0 && casesDroite == 0 && casesGauche == 0)
        {
            printf("Nul part, il semblerait que vous ayez modifie vous meme votre labyrinthe et ayez fait une erreur\n");
        }

        // deplacement
        else
        {
            printf("Deplacez-vous:\n");
        }
        casesHaut > 0 ? printf("Haut: touche z  ") : 0;
        casesGauche > 0 ? printf("Gauche: touche q  ") : 0;
        casesBas > 0 ? printf("Bas: touche s  ") : 0;
        casesDroite > 0 ? printf("Droite: touche d  ") : 0;
        scanf(" %c", &deplacement);
        switch (deplacement)
        {
        case 'z':
            if (casesHaut > 0)
            {
                cheminParcouru[y][x] = '|';
                y--;
                cheminParcouru[y][x] = '0';
            }
            else
            {
                printf("\nDeplacement impossible\n");
            }
            break;
        case 'q':
            if (casesGauche > 0)
            {
                cheminParcouru[y][x] = '-';
                x--;
                cheminParcouru[y][x] = '0';
            }
            else
            {
                printf("\nDeplacement impossible\n");
            }
            break;

        case 's':
            if (casesBas > 0)
            {
                cheminParcouru[y][x] = '|';
                y++;
                cheminParcouru[y][x] = '0';
            }
            else
            {
                printf("\nDeplacement impossible\n");
            }
            break;
        case 'd':
            if (casesDroite > 0)
            {
                cheminParcouru[y][x] = '-';
                x++;
                cheminParcouru[y][x] = '0';
            }
            else
            {
                printf("\nDeplacement impossible\n");
            }
            break;
        }
        afficheDeplacements(cheminParcouru);
    }

    printf("Bravo, vous avez gagne !\n");
    printf("Entrez un caractere pour quitter...\n");
    scanf("%d"); // pas mettre %c car il va prendre le \n du terminal
    return 0;
}