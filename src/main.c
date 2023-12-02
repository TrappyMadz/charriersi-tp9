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
    struct sJoueur* groupe = NULL;
    int int_nbJoueur;
    int i;
    int ipioche = 0;
    struct sCarte paquet[52];


    initialisation(paquet,ipioche);
    int_nbJoueur = nbJoueur();
    groupe = enregistrement(int_nbJoueur);
    printf("Nombre de joueurs : %d\n",int_nbJoueur);
    ipioche = distrib(groupe, int_nbJoueur, paquet, ipioche);
    
    printf("Nombre de cartes piochées : %d\n",ipioche);


    for (i = 0 ; i <= int_nbJoueur ; i++)
    {
        free(groupe[i].nom);
    }
    free(groupe);
    return 0;
}   