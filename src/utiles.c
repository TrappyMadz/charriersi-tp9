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

#include "utiles.h"

// Définitions
#define ERREUR -1

// Affichage d'un tableau
void afftab(int* tint_tab, int int_taille)
{
	// Déclaration des variable
    // Compteur de boucle
	int int_i;

	// Affichage
	printf("|");
	for (int_i = 0 ; int_i < int_taille; int_i++)
	{
		printf("%d|",tint_tab[int_i]);
	}
    printf("\n");
}

// Demande d'un tableau d'entier à l'utilisateur
int* eTab(int int_taille)
{
    // Déclaration des variables
    // Vérification
    int int_verif;
    // Compteur de boucle
    int int_i;
    // Tableau
    int* pint_tab;

    // Allocation du tableau
    pint_tab = (int*)malloc(int_taille * sizeof(int));
    if (pint_tab == NULL)
    {
        fprintf(stderr, "Erreur d'allocation.\n");
        exit(ERREUR);
    }

    // Boucle pour permettant de demander chaque entier dans le tableau
    for (int_i = 0 ; int_i <= int_taille-1 ; int_i++)
    {
        // Vérification et demande
        int_verif = 0;
        while (int_verif != 1)
        {
            printf("Entrez le contenu de la case %d :\n",int_i+1);
            int_verif = scanf("%d",&pint_tab[int_i]);
        }
    }

    return pint_tab;
}
