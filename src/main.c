/*!
\file main.c
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Menu de séléction
*/

// Importations
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "jeu.h"
#include "utile.h"

// Définitions
#define ERREUR -1
#define SORTIE 0

/*!
\fn int main (int argc, char** argv)
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Affichage du menu
\param argc nombre d'arguments en entrée
\param argv valeur des arguments en entrée
\return 0 si tout c'est bien passé
*/
int main(int argc, char ** argv) 
{
    srand(time(NULL));
    
    struct sJoueur groupe[5];
    int int_nbJoueur = 1;
    int ipioche = 0;
    struct sCarte paquet[52];
    int int_pts;

    /*
    initialisation(paquet,ipioche);
    int_nbJoueur = ask("Veuillez entrer le nombre de joueurs (max 4) :\n", 1, 4);
    enregistrement(int_nbJoueur, groupe);
    printf("Nombre de joueurs : %d\n",int_nbJoueur);
    ipioche = distrib(groupe, int_nbJoueur, paquet, ipioche);
    printf("Nombre de cartes piochées : %d\n",ipioche);
    int_pts = points(groupe, 0);
    printf("Nombre de points : %d",int_pts);
    */

    enregistrement(int_nbJoueur,groupe);
    printf("%s\n", groupe[0].nom);
    groupe[0].argent = 200;
    mise(groupe, 0, 1);
    printf("%d\n",groupe[0].mise);


    return 0;
}   