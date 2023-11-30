/*!
\file utiles.c
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Fonctions utiles pour les TP
*/

// Importations
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "jeu.h"

// Définitions
#define ERREUR -1

void initialisation(struct sCarte paquet[52])
{
    // Déclaration des variables
    // Indice du tableau
    int i;
    // Compteurs de boucle
    int int_coul;
    int int_val;
    // Valeurs aléatoire pour le mélange
    int int_Rand;
    // Stockage temporaire pour l'échange de 2 cartes dans le paquet
    struct sCarte tmp;

    // Initialisation : On créer les cartes dans un tableau de 52 cases (tableau de struct)
    i = 0;
    for (int_coul = Pique ; int_coul <= Carreau + 1 ; int_coul++)
    {
        for (int_val = Deux ; int_val <= As ; int_val++)
        {
                paquet[i].eCouleur = int_coul;
                paquet[i].eValeurs = int_val;
                i++;
        }
    }

    // Mélange
    // On prend chaque case du tableau et on la permutte avec une case aléatoire
    for (i = 0 ; i < 52 ; i++)
    {   
        // La formule qui suit se trouve dans le man de la fonction rand. Elle permet d'obtenir un nombre entre 0 et 52. 
        // (la formule originae est : 1+(int)((52.0 * rand())/(RAND_MAX+1.0)) pour un nombre entre 1 et 52;)
        int_Rand = (int)((52.0 * rand())/(RAND_MAX+1.0));
        tmp = paquet[i];
        paquet[i] = paquet[int_Rand];
        paquet[int_Rand] = tmp;
    }
}