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
#include <stdbool.h>

#include "jeu.h"

// Définitions
#define ERREUR -1
#define FIN_PARTIE 0

// Couleurs
#define ROUGE "\x1B[1;31m"
#define BLANC "\e[0;37m"

void initialisation(struct sCarte paquet[52], int int_cartesPioche)
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


    // On remet à 0 le nombre de cartes piochées
    int_cartesPioche = 0;
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

int nbJoueur()
{
    // Déclaration des variables
    // Vérification
    int int_verif;
    // Nombre de joueurs
    int int_nbJoueur;

    // Nombre de joueur
    printf("Bienvenue ! Combien êtes-vous (4 max) ?\n");
    int_verif = scanf("%d",&int_nbJoueur);
    while (int_nbJoueur <= 0 || int_verif != 1 || int_nbJoueur > 4)
    {
        getchar();
        printf("Entrez un nombre valide.\n");
        int_verif = scanf("%d",&int_nbJoueur);
    }

    return int_nbJoueur;
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

    // On prend en compte le croupier qui sera considéré comme un joueur suplémentaire
    groupe = malloc(int_joueurs + 1 * sizeof (struct sJoueur));
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
    

    printf("Enfin, il va me falloir vos noms :\n"); 
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
        groupe[i].pioche = 0;
    }

    // On s'occupe aussi du croupier
    groupe[int_joueurs].nom = malloc(10 * sizeof(char));
        if (groupe[i].nom == NULL)
        {
            fprintf(stderr, "Erreur d'allocation\n");
            exit(ERREUR);
        }
    strcpy(groupe[int_joueurs].nom, "Croupier");
    groupe[int_joueurs].pioche = 0;

    printf("Bien, la partie va pouvoir commencer !\n");
    return groupe;
    
}

int pioche(struct sJoueur* groupe, struct sCarte paquet[52], int int_joueur, int int_cartePioche)
{

    // On ajoute une carte au struct du joueur, en regardant le nombre de carte qu'il à déjà
    // Une fois fait, on augmente cartePioche pour pouvoir piocher la carte suivante
    groupe[int_joueur].carte[groupe[int_joueur].pioche].eValeurs = paquet[int_cartePioche].eValeurs;
    groupe[int_joueur].carte[groupe[int_joueur].pioche].eCouleur = paquet[int_cartePioche].eCouleur;
    groupe[int_joueur].pioche++;
    int_cartePioche++;
    return int_cartePioche;
}

void affichCarte(struct sJoueur* joueur, int int_joueur)
{
    // Déclaration des variables
    // Compteur de boucle
    int i;
    // Valeur et couleur de la carte scannée (tailles max obtenues après des essais)
    char char_valeur[18];
    char char_couleur[19];
    // Valeurs à l'envers, pour l'affichage de la carte
    char char_valeur2[18];
    // Couleur de la carte (vrai si rouge)
    bool bool_R;
    // Si la valeurs est 10, cette variable = true (pour l'affichage)
    bool bool_D;
    

    printf("Cartes de %s :\n", joueur[int_joueur].nom);

    // On affiche toutes les cartes du joueur int_joueur
    for (i = 0 ; i < joueur[int_joueur].pioche ; i++)
    {
        // On remet à false les booléens
        bool_R = false;
        bool_D = false;

        // On utilise un switch pour les couleurs 
        // (elles seront colorées, mais pique et trèfles seront blanc au lieu de noir car le fond du terminal est noir chez la plupart des utilisateurs)
        switch (joueur[int_joueur].carte[i].eCouleur)
        {
        case Pique :
            strcpy(char_couleur, "\u2660");
            break;

        case Trèfle :
            strcpy(char_couleur, "\u2663");
            break;

        case Carreau :
            strcpy(char_couleur, ROUGE "\u2666" BLANC);
            bool_R = true;
            break;

        case Coeur :
            strcpy(char_couleur, ROUGE "\u2665" BLANC);
            bool_R = true;
            break;
        
        default:
            break;
        }

        if (bool_R == false)
        {
            // Un autre switch pour les valeurs si on a pique ou trèfle
            switch (joueur[int_joueur].carte[i].eValeurs)
            {
            case Deux :
                strcpy(char_valeur, "2");
                strcpy(char_valeur2, "\u1615");
                break;

            case Trois :
                strcpy(char_valeur, "3");
                strcpy(char_valeur2, "\u0190");
                break;

            case Quatre :
                strcpy(char_valeur, "4");
                strcpy(char_valeur2, "h");
                break;

            case Cinq :
                strcpy(char_valeur, "5");
                strcpy(char_valeur2, "\u091F");
                break;

            case Six :
                strcpy(char_valeur, "6");
                strcpy(char_valeur2, "9");
                break;

            case Sept :
                strcpy(char_valeur, "7");
                strcpy(char_valeur2, "L");
                break;

            case Huit :
                strcpy(char_valeur, "8");
                strcpy(char_valeur2, "8");
                break;

            case Neuf :
                strcpy(char_valeur, "9");
                strcpy(char_valeur, "6");
                break;

            case Dix :

                strcpy(char_valeur, "10");
                strcpy(char_valeur2, "0\u0196");
                bool_D = true;
                break;

            case Valet :
                strcpy(char_valeur, "J");
                strcpy(char_valeur2, "\u017F");
                break;

            case Dame :
                strcpy(char_valeur, "Q");
                strcpy(char_valeur2, "\u1FF8");
                break;

            case Roi :
                strcpy(char_valeur, "K");
                strcpy(char_valeur2, "\uA4D8");
                break;

            case As :
                strcpy(char_valeur, "A");
                strcpy(char_valeur2, "\u2C6F");
                break;
        
            default:
                break;
            }
        }
        else
        {
            // Un autre switch pour les valeurs si on a coeur ou carreau
            switch (joueur[int_joueur].carte[i].eValeurs)
            {
            case Deux :
                strcpy(char_valeur, ROUGE "2" BLANC);
                strcpy(char_valeur2, ROUGE "\u1615" BLANC);
                break;

            case Trois :
                strcpy(char_valeur, ROUGE "3" BLANC);
                strcpy(char_valeur2, ROUGE "\u0190" BLANC);
                break;

            case Quatre :
                strcpy(char_valeur, ROUGE "4" BLANC);
                strcpy(char_valeur2, ROUGE "h" BLANC);
                break;

            case Cinq :
                strcpy(char_valeur, ROUGE "5" BLANC);
                strcpy(char_valeur2, ROUGE "\u091F" BLANC);
                break;

            case Six :
                strcpy(char_valeur, ROUGE "6" BLANC);
                strcpy(char_valeur2, ROUGE "9" BLANC);
                break;

            case Sept :
                strcpy(char_valeur, ROUGE "7" BLANC);
                strcpy(char_valeur2, ROUGE "L" BLANC);
                break;

            case Huit :
                strcpy(char_valeur, ROUGE "8" BLANC);
                strcpy(char_valeur2, ROUGE "8" BLANC);
                break;

            case Neuf :
                strcpy(char_valeur, ROUGE "9" BLANC);
                strcpy(char_valeur, ROUGE "6" BLANC);
                break;

            case Dix :
                strcpy(char_valeur, ROUGE "10" BLANC);
                strcpy(char_valeur2, ROUGE "0\u0196" BLANC);
                bool_D = true;
                break;

            case Valet :
                strcpy(char_valeur, ROUGE "J" BLANC);
                strcpy(char_valeur2, ROUGE "\u017F" BLANC);
                break;

            case Dame :
                strcpy(char_valeur, ROUGE "Q" BLANC);
                strcpy(char_valeur2, ROUGE "\u1FF8" BLANC);
                break;

            case Roi :
                strcpy(char_valeur, ROUGE "K" BLANC);
                strcpy(char_valeur2, ROUGE "\uA4D8" BLANC);
                break;

            case As :
                strcpy(char_valeur, ROUGE "A" BLANC);
                strcpy(char_valeur2, ROUGE "\u2C6F" BLANC);
                break;
        
            default:
                break;
            }            
        }

        // Pour toutes les cartes, sauf 10 car son affichage posera problème (10 fait 2 charactère)
        if (bool_D == false)
        {
            printf(" ______\n");
            printf("|%s     |\n",char_valeur);
            printf("|      |\n");
            printf("|  %s   |\n",char_couleur);
            printf("|      |\n");
            printf("|     %s|\n",char_valeur2);
            printf(" \u203E\u203E\u203E\u203E\u203E\u203E\n");
        }

        // Pour 10, on retire un espace
        else
        {
            printf(" ______ \n");
            printf("|%s    |\n",char_valeur);
            printf("|      |\n");
            printf("|  %s   |\n",char_couleur);
            printf("|      |\n");
            printf("|    %s|\n",char_valeur2);
            printf(" \u203E\u203E\u203E\u203E\u203E\u203E\n");
        }
        
    }
}

int distrib(struct sJoueur* groupe, int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche)
{
    // Déclaration des variables
    // Compteur de boucle
    int i;


    // On suit les règles du black jack :
    // Le croupier distribue une carte par joueur face visible et une à lui-même
    for (i = 0 ; i <= int_nbJoueur ; i++)
    {
        int_cartePioche = pioche(groupe, paquet, i, int_cartePioche);
        affichCarte(groupe, i);
    }

    // Le croupier distribue ensuite une deuxième carte uniquements aux joueurs. Il tire sa seconde carte une fois qu'il à joué.
    return int_cartePioche;
}


/*
struct sJoueur tourJoueur(struct sJoueur joueur,int int_joueurtour)
{
    // Déclaration des variables
    // Vérification
    int int_verif;
    // Mise
    int int_mise;

    // Début du tour
    system("clear");
    printf("C'est au tour de %s de jouer !\n",joueur[int_joueurtour].nom)

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