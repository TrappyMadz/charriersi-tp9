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
    int nbJoueur = 0;
    int i;

    groupe = enregistrement(nbJoueur);
    printf("%s",groupe[0].nom);
    for (i = 0 ; i < nbJoueur ; i++)
    {
        free(groupe[i].nom);
    }
    free(groupe);
    return 0;
}   