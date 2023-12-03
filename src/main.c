/*!
\file main.c
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Lancement du jeu
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
\date 3 décembre 2023
\brief Lancement du jeu
\param argc nombre d'arguments en entrée
\param argv valeur des arguments en entrée
\return int_good qui est égale à 0 si tout c'est bien passé
*/
int main(int argc, char ** argv) 
{
    // Déclaration des variables
    // Tout s'est bien passé ?
    int int_good;
    // Initialisation de l'aléatoire
    srand(time(NULL));
    // Groupe de joueurs
    struct sJoueur groupe[5];
    // Paquet de cartes
    struct sCarte paquet[52];
    
    // Jeu
    int_good = tourJeu(groupe, paquet);


    return int_good;
}   