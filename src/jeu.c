/*!
\file jeu.c
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Fonctions utiles pour le déroulement du jeu
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

// Initialisation du paquet de cartes et des variables joueurs
int initialisation(struct sJoueur groupe[5], struct sCarte paquet[52], int int_cartesPioche, int int_nbJoueur)
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

    // Partie joueurs
    // On remet le nombre de cartes piochées par joueurs à 0
    for (i = 0 ; i <= int_nbJoueur ; i++)
    {    
        groupe[i].pioche = 0;   
    }
    return int_cartesPioche;
}

// Enregistrement des joueurs (nom / argent avec lequel ils commencent)
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
        
    }

    // On s'occupe aussi du croupier
    strcpy(groupe[int_joueurs].nom, "Croupier");
    

    printf("Bien, la partie va pouvoir commencer !\n");
}

// Ajoute une carte à la main d'un joueur
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

// Affiche les cartes d'un joueur
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
                strcpy(char_valeur2, "6\0");
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
                strcpy(char_valeur2, ROUGE "6" BLANC "\0");
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

// Distribution initiale (2 cartes par joueur et 1 au croupier, dans le bonne ordre)
int distrib(struct sJoueur groupe[5], int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche)
{
    // On suit les règles du black jack :
    // Le croupier distribue une carte par joueur face visible et une à lui-même
    for (int i = 0 ; i <= int_nbJoueur ; i++)
    {
        int_cartePioche = pioche(groupe, paquet, i, int_cartePioche);
    }

    // Le croupier distribue ensuite une deuxième carte uniquements aux joueurs. Il tire sa seconde carte une fois qu'ils ont joué.
    for (int i = 0 ; i < int_nbJoueur ; i++)
    {
        int_cartePioche = pioche(groupe, paquet, i, int_cartePioche);
    }

    return (int_cartePioche);
}

// Calcul des points d'un participant
int points(struct sJoueur groupe[5], int int_joueur)
{
    // Déclaration des variables
    // Points totaux
    int int_pts = 0;
    // Si on pioche un As, pon incrémente
    int int_as = 0;

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
            int_as += 1;
            int_pts += 11;
        
        default:
            break;
        }
    }

    // Blackjack !
    if (groupe[int_joueur].pioche <= 2 && int_pts == 21)
    {
        int_pts = 22;
        return int_pts;
    }

    // Règle de l'As 
    while (int_pts > 21 && int_as > 0)
    {
        int_pts -= 10;
        int_as -=1;
    }

    // Défaite
    if (int_as == 0 && int_pts >= 21)
    {
        int_pts = 0;
        return int_pts;
    }

    return int_pts;
}

// Met fin à la partie en affichant les scores
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

// Permet à un joueur de miser ou d'abandonner si il mise 0
bool mise(struct sJoueur groupe[5],int int_joueur, int int_nbJoueur, bool bool_partieFinie)
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
        printf("Abandon de %s !",groupe[int_joueur].nom);
        groupe[int_joueur].argent = 0;
        bool_partieFinie = true;
        return bool_partieFinie;
    }
    else
    {
        return bool_partieFinie;
    }
}

// Permet à un joueur de tirer ou non des cartes suplémentaires
int tirageJ(struct sJoueur groupe[5],struct sCarte paquet[52], int int_joueur,int int_nbJoueur, int int_nbCartePioche)
{   
    // Déclaration des variables
    // Réponse à la question "pioche ?"
    int int_rep;

    // On affiche la carte du croupier, son score, puis de même pour le joueur
    sleep(1);
    system("clear");
    affichCarte(groupe, int_nbJoueur);
    groupe[int_nbJoueur].score = points(groupe, int_nbJoueur);
    if (groupe[int_nbJoueur].score == 22 && groupe[int_nbJoueur].pioche == 1)
    {
        printf("Le croupier à fait un Black Jack !\n");
    }
    else if (groupe[int_nbJoueur].score == 0)
    {
        printf("Le croupier est au dessus de 21 !\n");
    }
    else
    {
        printf("Points du croupier : %d\n",groupe[int_nbJoueur].score);
    }
    
    affichCarte(groupe, int_joueur);
    // Si le joueur possède un black jack (21 points sans avoir tirer de cartes), on ne lui propose pas de tirer.
    groupe[int_joueur].score = points(groupe, int_joueur);
    if (groupe[int_joueur].score == 22 && groupe[int_joueur].pioche == 1)
    {
        printf("Black Jack !\n");
        sleep(1);
        return int_nbCartePioche;
    }
    

    else
    {
        printf("Vos points : %d\n",groupe[int_joueur].score);
        while (groupe[int_joueur].score <= 21 && groupe[int_joueur].score != 0)
        {
            // On demande au joueur si il souhaite une nouvelle carte
            int_rep = ask("Voulez-vous une carte suplémentaire (0 : Oui, 1 : Non) ?\n",0,1);

            // Si c'est le cas, on lui en fait piocher une
            if (int_rep == 0)
            {
                int_nbCartePioche = pioche(groupe, paquet, int_joueur, int_nbCartePioche);
                // On actualise le score
                groupe[int_joueur].score = points(groupe, int_joueur);

                // On affiche de nouveau les cartes
                sleep(1);
                system("clear");
                affichCarte(groupe, int_nbJoueur);
                groupe[int_nbJoueur].score = points(groupe, int_nbJoueur);
                if (groupe[int_nbJoueur].score == 0)
                {
                    printf("Le croupier à fait un Black Jack !\n");
                }
                else
                {
                    printf("Points du croupier : %d\n",groupe[int_nbJoueur].score);
                }
    
                affichCarte(groupe, int_joueur);
                printf("Vos points : %d\n",groupe[int_joueur].score);
            
            }
            else
            {
                return int_nbCartePioche;
            }
        }

        printf("Vous atteignez %d points. Dommage, c'est perdu !\n",groupe[int_joueur].score);
        sleep(1);
        return int_nbCartePioche;
    }
}

// Tour du croupier
int tirageC(struct sJoueur groupe[5], struct sCarte paquet[52], int int_nbJoueur, int int_nbCartePioche)
{
    // Le croupier suit les règles normales du black jack. La seule différence est qu'il commence avec une seule carte
    groupe[int_nbJoueur].score = points(groupe,int_nbJoueur);

    // Tant que le croupier à moins de 17 points,
    while(groupe[int_nbJoueur].score < 17 && groupe[int_nbJoueur].score != 0)
    {
        // On actualise les points du croupier
        groupe[int_nbJoueur].score = points(groupe,int_nbJoueur);

        // On clear, on affiche sa main, ses points
        sleep(1);
        system("clear");
        affichCarte(groupe, int_nbJoueur);
        printf("Points du croupier : %d\n",groupe[int_nbJoueur].score);

        int_nbCartePioche = pioche(groupe, paquet, int_nbJoueur, int_nbCartePioche);
    }

    // Une fois qu'il a fini, on affiche de nouveausleep(1); sa main et ses points :
    printf("Le croupier s'arrête.\n");
    sleep(1);

    // Si il a un black jack, on affiche un message spécial
    if (groupe[int_nbJoueur].score == 22 && groupe[int_nbJoueur].pioche == 1)
    {
        printf("Le croupier a fait un Black Jack !\n");
        sleep(1);
        return int_nbCartePioche;
    }
    // Si il fait plus de 21, il perd
    else if (groupe[int_nbJoueur].score > 21)
    {
        printf("Le croupier est au dessus de 21 !\n");
        sleep(1);
        return int_nbCartePioche;
    }
    
    // Sinon, rien de spécial ne se passe.
    return int_nbCartePioche;
}

// Compare les points des joueurs avec ceux du croupier et gère les gains
void compar(struct sJoueur groupe[5], int int_nbJoueur)
{

    // On parcours la totalité des joueurs et on compare leur score à celui du croupier
    for (int i = 0 ; i < int_nbJoueur ; i++)
    {
        // Si il est supérieur, on leur rend leur mise x2
        if (groupe[i].score > groupe[int_nbJoueur].score)
        {
            groupe[i].argent += groupe[i].mise * 2;
            groupe[i].mise = 0;
            printf("%s à plus de points que le croupier (%d) ! Il remporte le double de sa mise.\n",groupe[i].nom, groupe[i].score);
        }

        // Si il y a égalité, on rend au joueur sa mise
        else if (groupe[i].score == groupe[int_nbJoueur].score)
        {
            groupe[i].argent += groupe[i].mise;
            groupe[i].mise = 0;
            printf("%s à autant de points que le croupier (%d) ! Il récupère sa mise.\n",groupe[i].nom, groupe[i].score);
        }        

        // Sinon on ne fait rien
        else if (groupe[i].score < groupe[int_nbJoueur].score)
        {
            groupe[i].mise = 0;
            printf("%s à moins de points que le croupier (%d) ! Il perd sa mise.\n",groupe[i].nom, groupe[i].score);
        }

        // Rappel : si une personne fait un black jack, il a un score de 22 (donc > 21 via un tirage normal)
        // Rappel bis : si une personne va au delà de 21, son score est ramené à 0
        // Ces deux cas sont déjà gérés par la fonction points.
    }
}

// Déroulement de la partie, en utilisant les fonctions précedantes
int tourJeu(struct sJoueur groupe[5], struct sCarte paquet[52])
{
    // Déclaration des variables
    // Nombre de cartes piochées par l'ensemble des joueur (= où on en est dans le paquet)
    int int_nbCartePioche;
    // La partie est-elle finie ?
    bool bool_partieFinie = false;
    // Nombre de joueurs
    int int_nbJoueurs;

    printf("Bienvenu ! prêt à jouer au Black Jack ?\n");
    // On demande le nombre de joueurs
    int_nbJoueurs = ask("Parfait, dans ce cas, combien de joueurs sont présents (Max 4) ?\n",1,4);
        
    // Les joueurs s'enregistres
    enregistrement(int_nbJoueurs, groupe);

    while (bool_partieFinie == false)
    {
        // On commence par initialiser le jeu de carte
        printf("Le croupier mélange le paquet de cartes...\n");
        int_nbCartePioche = initialisation(groupe, paquet, int_nbCartePioche, int_nbJoueurs);

        // Chaque joueur va pouvoir miser
        printf("Chaque joueur va pouvoir miser pour ce tour !\n");
        for (int i = 0 ; i < int_nbJoueurs ; i++)
        {
            printf("Au tour de %s de miser.\n", groupe[i].nom);
            bool_partieFinie = mise(groupe, i, int_nbJoueurs, bool_partieFinie);
            
            // Si la partie est finie, on termine le round pour que les joueurs soient sur un pied d'égaliter
            // Sinon, si joueur 1 mise, puis que joueur 2 abandonne, joueur 3 aura plus de chance d'avoir plus d'argent, puisqu'il n'a pas encore misé.
        }


        // Le croupier distribue les cartes, qui s'affichent
        printf("Le croupier distribue les cartes...\n");
        int_nbCartePioche = distrib(groupe, int_nbJoueurs, paquet, int_nbCartePioche);

        // Tour à tour, chaque joueur va tirer les cartes qu'il veut
        printf("Chaque joueur va pouvoir maintenant pouvoir jouer !\n");
        for (int i = 0 ; i < int_nbJoueurs ; i++)
        {
            int_nbCartePioche = tirageJ(groupe, paquet, i, int_nbJoueurs, int_nbCartePioche);
        }

        // Enfin, le croupier jouera
        printf("Tour du croupier.\n");
        int_nbCartePioche = tirageC(groupe, paquet, int_nbJoueurs, int_nbCartePioche);

        // On compare les score, ceux qui on au dessus du croupier double leur mises, les autres la perde
        printf("Résultats : \n");
        compar(groupe, int_nbJoueurs);
    }

    // La partie prendra fin si l'un des joueur décide de miser 0 lors de la phase de mise (par volonté ou par obligation)
    // Dans ce cas, on affiche les scores via la fonction finPartie
    finPartie(groupe, int_nbJoueurs);
    return 0;
}