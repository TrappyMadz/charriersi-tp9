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
#include <string.h>

#include "jeu.h"

// Définitions
#define ERREUR -1
#define FIN_PARTIE 0

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

struct sJoueur* enregistrement(int int_joueurs)
{
    // Déclaration des variables
    // Joueurs
    struct sJoueur* groupe;
    // Argent choisis
    int int_argent;
    // Vérification
    int int_verif;
    // Compteur de boucle
    int i;


    // Nombre de joueur
    printf("Bienvenue ! Combien êtes-vous ?\n");
    int_verif = scanf("%d",&int_joueurs);
    while (int_joueurs <= 0 || int_verif != 1)
    {
        getchar();
        printf("Entrez un nombre valide.\n");
        int_verif = scanf("%d",&int_joueurs);
    }

    groupe = malloc(int_joueurs * sizeof (struct sJoueur));
    if (groupe == NULL)
    {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(ERREUR);
    }

    // Initialisation de chaque joueur
    printf("Bien ! Nous allons procéder à votre enregistrement.\n");
    printf("Premièrement, avec quel montant d'argent voulez-vous commencer ?\n");
    int_verif = scanf("%d", &int_argent);
    getchar();
    while (int_argent <= 0 || int_verif != 1)
    {
        printf("Veuillez entrer une valeur valide.\n");
        int_verif = scanf("%d", &int_argent);
    }
    

    printf("Enfin, il va me falloir vos noms (Maximum 10 caractères) :\n"); 
    for (i = 0 ; i < int_joueurs ; i++)
    {
        groupe[i].nom = malloc(10 * sizeof(char));
        if (groupe[i].nom == NULL)
        {
            fprintf(stderr, "Erreur d'allocation\n");
            exit(ERREUR);
        }

        printf("Joueur %d, entrez votre nom :\n",i+1);
        fgets(groupe[i].nom, 256, stdin);
        if (groupe[i].nom[strlen(groupe[i].nom) - 1] == '\n')
        {
            groupe[i].nom[strlen(groupe[i].nom) - 1] = '\0';
        }
        groupe[i].argent = int_argent;
    }

    printf("Bien, la partie va pouvoir commencer !\n");
    return groupe;
    
}

/*
struct sJoueur tourJoueur(struct sJoueur joueur,int int_joueur, int int_miseMax)
{
    // Déclaration des variables
    // Vérification
    int int_verif;
    // Mise
    int int_mise;

    // Affichage des cartes du joueur et de son argent
    printf("Vous avez %d€.\n",joueur[int_joueur].argent);
    printf("Vos cartes :\n");
    printf("%",)

    // On vérifie la condition de défaite
    if (joueur.argent == 0)
    {
        printf("%s n'a plus d'argent ! Fin de la partie\n",joueur[int_joueur].nom);
        exit(FIN_PARTIE);
    }

    // On demande une mise au joueur en laissant la possibilité de quitter
    printf("Entrez votre mise pour cette manche, 0 pour quitter :\n");
    int_verif = scanf("%d",&int_mise);
    if (int_mise == 0)
    {
        printf("%s souhaites abandonner. Fin de la partie\n",joueur.nom);
        exit(FIN_PARTIE);
    }

    // Celle-ci doit être un nombre entier, positif et doit être inférieure à son argent
    while (int_mise > joueur.argent || int_mise < 0 || int_verif != 1)
    {
        printf("Veuillez entrer une mise valide (inférieur à votre argent restant, supérieur à 0, et étant un nombre entier\n)");
    }
}
*/