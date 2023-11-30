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
    struct sCarte paquet[52];
    initialisation(paquet);
    for (int i = 0; i < 52; i++) 
    {
        printf("Carte %d - Couleur: %d, Valeur: %d\n", i + 1, paquet[i].eCouleur, paquet[i].eValeurs);
    }
    return 0;
}   