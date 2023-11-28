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

#include "utiles.h"

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
    // Déclaration des variables
    // Choix du menu
    int int_choix;
    // Vérification
    int int_verif;
    // Taille du tableau et Tableau
    int int_taille;
    int* pint_tab;

    printf("----------------------------------\n");
	printf("---------------Menu---------------\n");
	printf("----------------------------------\n");
	printf("----Quelle fonction utiliser ?----\n");
	printf("----------------------------------\n");
	printf("- 1.                             -\n");
	printf("- 2. Retour                      -\n");
	printf("----------------------------------\n");
	printf("----------------------------------\n");

	int_verif = scanf("%d",&int_choix);

	while (int_verif!=1)
	{
		printf("Veuillez entrer une option valide.\n");
		int_verif = scanf("%d",&int_choix);
	}

    switch (int_choix)
    {
    case 1 :


        break;
        
    case 2 :

 	printf("Sortie du programme\n");
        exit(SORTIE);
        break;
 
    default:
        printf("Sortie du programme\n");
        exit(SORTIE);
        break;
    }
    return 0;
}
