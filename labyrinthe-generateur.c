#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int colonnes, lignes;


int testResolvable(char labyrinthe[10][10], int caseVerif[10][10], int x, int y) {
    if (x < 0 || x >= colonnes || y < 0 || y >= lignes) return 0;
    if (labyrinthe[y][x] == '#' || caseVerif[y][x] == 1) return 0;
    if (x == colonnes - 1 && y == lignes - 1) return 1;
    caseVerif[y][x] = 1;
    if (testResolvable(labyrinthe, caseVerif, x + 1, y) ||
        testResolvable(labyrinthe, caseVerif, x - 1, y) ||
        testResolvable(labyrinthe, caseVerif, x, y + 1) ||
        testResolvable(labyrinthe, caseVerif, x, y - 1)) {
        return 1;
    }
    return 0;
}


void labyFichierTxt(char labyrinthe[10][10]){
    FILE* flux = NULL;
    flux = fopen("labyrinthe.txt","w");
    if(flux!=NULL){
        for(int j=0; j<lignes; j++){
            for(int i=0; i<colonnes; i++){
                fprintf(flux, "%c", labyrinthe[j][i]);   //mettre "%c" car fprintf a pour argument une chaine de caractere et pas un char
            }
            fprintf(flux, "\n");
        }
        fclose(flux);
    }
}


int main(void) {

    // choix longueur (x), largeur (y)
    int modeDim=0;
    srand((unsigned)time(NULL));
    while (modeDim!=1 && modeDim!=2){
        printf("Voulez-vous que les dimensions du labyrinthe soient aleatoires ou choisies par vous?\n");
        printf("Tapez: 1-Aleatoires  2-Choisies par vous\n");
        
        scanf("%d",&modeDim);
        if (modeDim == 1){
            colonnes = rand()%7 + 3;
            lignes = rand()%7 + 3;
        }
        else if (modeDim == 2){
            printf("Entrez la longueur du labyrinthe (nombre de colonnes)\n");
            scanf("%d",&colonnes);
            printf("Entrez la largeur du labyrinthe (nombre de lignes)\n");
            scanf("%d",&lignes);
        }
        
    }
    printf("%d  %d \n",colonnes,lignes);
    char labyrinthe[10][10];
    char CARACTERES[2] = {'#','.'}, caractere; //#:mur   .: vide   potentiellement à modifier
    int caractereNb, resolvable=0;
    while(resolvable==0){
        for(int j=0; j<lignes; j++){                    // création labyrinthe
            for(int i=0; i<colonnes; i++){
                caractereNb = rand()%5;                 // probabilité d'avoir un mur de 1/5 (pas parfait)
                if (caractereNb > 0){
                    caractereNb = 1;
                }
                caractere = CARACTERES[caractereNb];
                labyrinthe[j][i] = caractere;
            }
        }
        labyrinthe[0][0] = '.';
        labyrinthe[colonnes-1][lignes-1] = '.';

        int caseVerif[10][10]; 
        if(testResolvable(labyrinthe, caseVerif, 0, 0)){    // test de resolvabilité
            resolvable = 1;
        }
    }
    labyFichierTxt(labyrinthe);
    printf("Voici votre labyrinthe\n");     // affichage du labyrinthe
    for(int j=0; j<lignes; j++){
        for(int i=0; i<colonnes; i++){
            printf(" %c ", labyrinthe[j][i]); // espace entre chaque caractère
        }
        printf("\n");
    }
}