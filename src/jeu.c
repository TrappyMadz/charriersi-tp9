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
#include <unistd.h>

#include "jeu.h"
#include "utile.h"

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

void enregistrement(int int_joueurs, struct sJoueur groupe[5])
{
    // Déclaration des variables
    // Argent choisis
    int int_argent;
    // Compteur de boucle
    int i;


    // Initialisation de chaque joueur
    printf("Bien ! Nous allons procéder à votre enregistrement.\n");
    int_argent = ask("Premièrement, avec quel montant d'argent voulez-vous commencer ?\n",1 , 999999);

    printf("Enfin, il va me falloir vos noms :\n"); 
    for (i = 0 ; i < int_joueurs ; i++)
    {
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
    strcpy(groupe[int_joueurs].nom, "Croupier");
    groupe[int_joueurs].pioche = 0;

    printf("Bien, la partie va pouvoir commencer !\n");
}

int pioche(struct sJoueur groupe[5], struct sCarte paquet[52], int int_joueur, int int_cartePioche)
{

    // On ajoute une carte au struct du joueur, en regardant le nombre de carte qu'il à déjà
    // Une fois fait, on augmente cartePioche pour pouvoir piocher la carte suivante
    groupe[int_joueur].carte[groupe[int_joueur].pioche].eValeurs = paquet[int_cartePioche].eValeurs;
    groupe[int_joueur].carte[groupe[int_joueur].pioche].eCouleur = paquet[int_cartePioche].eCouleur;
    groupe[int_joueur].pioche++;
    int_cartePioche++;
    return int_cartePioche;
}

void affichCarte(struct sJoueur joueur[5], int int_joueur)
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
            strcpy(char_couleur, "\u2660\0");
            break;

        case Trèfle :
            strcpy(char_couleur, "\u2663\0");
            break;

        case Carreau :
            strcpy(char_couleur, ROUGE "\u2666" BLANC "\0");
            bool_R = true;
            break;

        case Coeur :
            strcpy(char_couleur, ROUGE "\u2665" BLANC "\0");
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
                strcpy(char_valeur, "2\0");
                strcpy(char_valeur2, "\u1615\0");
                break;

            case Trois :
                strcpy(char_valeur, "3\0");
                strcpy(char_valeur2, "\u0190\0");
                break;

            case Quatre :
                strcpy(char_valeur, "4\0");
                strcpy(char_valeur2, "h\0");
                break;

            case Cinq :
                strcpy(char_valeur, "5\0");
                strcpy(char_valeur2, "\u091F\0");
                break;

            case Six :
                strcpy(char_valeur, "6\0");
                strcpy(char_valeur2, "9\0");
                break;

            case Sept :
                strcpy(char_valeur, "7\0");
                strcpy(char_valeur2, "L\0");
                break;

            case Huit :
                strcpy(char_valeur, "8\0");
                strcpy(char_valeur2, "8\0");
                break;

            case Neuf :
                strcpy(char_valeur, "9\0");
                strcpy(char_valeur, "6\0");
                break;

            case Dix :

                strcpy(char_valeur, "10\0");
                strcpy(char_valeur2, "0\u0196\0");
                bool_D = true;
                break;

            case Valet :
                strcpy(char_valeur, "J\0");
                strcpy(char_valeur2, "\u017F\0");
                break;

            case Dame :
                strcpy(char_valeur, "Q\0");
                strcpy(char_valeur2, "\u1FF8\0");
                break;

            case Roi :
                strcpy(char_valeur, "K\0");
                strcpy(char_valeur2, "\uA4D8\0");
                break;

            case As :
                strcpy(char_valeur, "A\0");
                strcpy(char_valeur2, "\u2C6F\0");
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
                strcpy(char_valeur, ROUGE "2" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u1615" BLANC "\0");
                break;

            case Trois :
                strcpy(char_valeur, ROUGE "3" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u0190" BLANC "\0");
                break;

            case Quatre :
                strcpy(char_valeur, ROUGE "4" BLANC "\0");
                strcpy(char_valeur2, ROUGE "h" BLANC "\0");
                break;

            case Cinq :
                strcpy(char_valeur, ROUGE "5" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u091F" BLANC "\0");
                break;

            case Six :
                strcpy(char_valeur, ROUGE "6" BLANC "\0");
                strcpy(char_valeur2, ROUGE "9" BLANC "\0");
                break;

            case Sept :
                strcpy(char_valeur, ROUGE "7" BLANC "\0");
                strcpy(char_valeur2, ROUGE "L" BLANC "\0");
                break;

            case Huit :
                strcpy(char_valeur, ROUGE "8" BLANC "\0");
                strcpy(char_valeur2, ROUGE "8" BLANC "\0");
                break;

            case Neuf :
                strcpy(char_valeur, ROUGE "9" BLANC "\0");
                strcpy(char_valeur, ROUGE "6" BLANC "\0");
                break;

            case Dix :
                strcpy(char_valeur, ROUGE "10" BLANC "\0");
                strcpy(char_valeur2, ROUGE "0\u0196" BLANC "\0");
                bool_D = true;
                break;

            case Valet :
                strcpy(char_valeur, ROUGE "J" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u017F" BLANC "\0");
                break;

            case Dame :
                strcpy(char_valeur, ROUGE "Q" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u1FF8" BLANC "\0");
                break;

            case Roi :
                strcpy(char_valeur, ROUGE "K" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\uA4D8" BLANC "\0");
                break;

            case As :
                strcpy(char_valeur, ROUGE "A" BLANC "\0");
                strcpy(char_valeur2, ROUGE "\u2C6F" BLANC "\0");
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
        usleep(500000);
        
    }
}

int distrib(struct sJoueur groupe[5], int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche)
{
    // Déclaration des variables

    // On suit les règles du black jack :
    // Le croupier distribue une carte par joueur face visible et une à lui-même
    for (int i = 0 ; i <= int_nbJoueur ; i++)
    {
        int_cartePioche = pioche(groupe, paquet, i, int_cartePioche);
    }
    
    // On affiche uniquement les cartes du Croupier pour éviter la redondance
    affichCarte(groupe, int_nbJoueur);

    // Le croupier distribue ensuite une deuxième carte uniquements aux joueurs. Il tire sa seconde carte une fois qu'ils ont joué.
    for (int i = 0 ; i < int_nbJoueur ; i++)
    {
        int_cartePioche = pioche(groupe, paquet, i, int_cartePioche);
        affichCarte(groupe, i);
    }

    return (int_cartePioche);
}

int points(struct sJoueur groupe[5], int int_joueur)
{
    // Déclaration des variables
    // Points totaux
    int int_pts = 0;
    // Si on pioche un As, passe à vrai (permet de gerer la règle de l'As)
    bool bool_as = false;

    // On parcours les cartes du joueur, et on ajoute les points que valent les cartes à son score
    for (int i = 0 ; i < groupe[int_joueur].pioche ; i++)
    {
        switch (groupe[int_joueur].carte[i].eValeurs)
        {
        case Deux :
            int_pts += 2;
            break;

        case Trois :
            int_pts += 3;
            break;

        case Quatre :
            int_pts += 4;
            break;

        case Cinq :
            int_pts += 5;
            break;

        case Six :
            int_pts += 6;
            break;

        case Sept :
            int_pts += 7;
            break;

        case Huit :
            int_pts += 8;
            break;

        case Neuf :
            int_pts += 9;
            break;

        case Dix :
        case Valet :
        case Dame :
        case Roi :
            int_pts += 10;
            break;

        case As :
            bool_as = true;
            int_pts += 11;
        
        default:
            break;
        }
    }

    // Blackjack !
    if (groupe[int_joueur].pioche <= 2 && int_pts == 21)
    {
        printf("Black Jack !\n");
        int_pts = 22;
    }

    // Règle de l'As
    if (bool_as == true && int_pts >= 21)
    {
        int_pts -= 10;
        bool_as = false;
    }

    // Défaite
    if (bool_as == false && int_pts >= 21)
    {
        int_pts = 0;
    }

    return int_pts;
}

void finPartie(struct sJoueur groupe[5], int int_nbJoueur)
{
    // Déclaration des variables
    // Maximum
    int int_max;
    // Position du max
    int int_pos;

    // On trouve le maximum d'argent
    int_max = groupe[0].argent;
    int_pos = 0;
    for (int i = 1 ; i < int_nbJoueur ; i++)
    {
        if (int_max < groupe[i].argent)
        {
            int_max = groupe[i].argent;
            int_pos = i;
        }
    }

    printf("Partie terminée ! Voici l'argent avec lequel vous repartez :\n");
    // On affiche les scores de tous les joueurs
    for (int i = 0 ; i < int_nbJoueur ; i++)
    {
        printf("%s : %d€\n",groupe[i].nom,groupe[i].argent);
    }

    // On indique quel joueur est vainqueur
    printf("%s reppart avec le plus d'argent (%d€)\n",groupe[int_pos].nom,int_max);


}


void mise(struct sJoueur groupe[5],int int_joueur, int int_nbJoueur)
{
    // Déclaration des variables
    int int_mise;

    // On demande une mise au joueur, et on vérifie qu'elle soit valide, et on lui retire l'argent correspondant
    printf("Vous avez %d€.\n", groupe[int_joueur].argent);
    int_mise = ask("Combien voulez-vous miser ?\n", 0, groupe[int_joueur].argent);
    groupe[int_joueur].argent -= int_mise;
    groupe[int_joueur].mise = int_mise;

    // Quitter ?
    if (int_mise == 0)
    {
        printf("Abandon de %s ! Partie terminée",groupe[int_joueur].nom);
        groupe[int_joueur].argent = 0;
        finPartie(groupe, int_nbJoueur);
    }
}


