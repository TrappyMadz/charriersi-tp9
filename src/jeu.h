/*!
\file jeu.h
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Fichier h associé aux fonctions utiles pour le jeu
*/

// Définitions
#ifndef __JEU_H_
#define __JEU_H_

// Inclusion (pour le booléen)
#include <stdbool.h>

enum eCouleur {Pique, Trèfle, Carreau, Coeur};
enum eValeurs { Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi, As};

struct sCarte 
{
    enum eCouleur eCouleur;
    enum eValeurs eValeurs;
};

struct sJoueur
{
    char nom[256];
    int argent;
    int mise;
    struct sCarte carte[10];
    int pioche;
    int score;
};

/*!
\fn int initialisation(struct sJoueur groupe[5], struct sCarte paquet[52], int int_cartesPioche, int int_nbJoueur);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Création, mélange du paquet de cartes et remise à 0 des variables joueur (nb de cartes piochées...)
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\param int_cartesPioche Le nombre de cartes piochée au total pendant le round
\param int_nbJoueur le nombre de joueurs
\return int_cartesPioche le nombre de cartes piochée remis à 0 pour un nouveau round
*/
int initialisation(struct sJoueur groupe[5], struct sCarte paquet[52], int int_cartesPioche, int int_nbJoueur);

/*!
\fn int pioche(struct sJoueur groupe[5], struct sCarte paquet[52], int int_joueur, int int_cartePioche);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet d'ajouter une carte à la main d'un joueur
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\param int_joueur Le joueur dont on veut modifier la main
\param int_cartesPioche Le nombre de cartes piochée au total pendant le round
\return int_cartesPioche le nombre de cartes piochée durant ce round + 1 (car il y a eu une nouvelle pioche)
*/
int pioche(struct sJoueur groupe[5], struct sCarte paquet[52], int int_joueur, int int_cartePioche);

/*!
\fn void enregistrement(int int_joueurs, struct sJoueur groupe[5]);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet de demander le nom des joueurs et l'argent avec lequel le groupe commencera
\param int_joueurs Le nombre de joueurs
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
*/
void enregistrement(int int_joueurs, struct sJoueur groupe[5]);

/*!
\fn void affichCarte(struct sJoueur joueur[5], int int_joueur);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet d'afficher les cartes d'un joueur
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_joueur Le joueur dont on veut afficher les cartes
*/
void affichCarte(struct sJoueur joueur[5], int int_joueur);

/*!
\fn int distrib(struct sJoueur groupe[5], int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet de distibuer les premières cartes à tous les joueurs puis au croupier
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_nbJoueur Le nombre de joueurs
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\param int_cartesPioche Le nombre de cartes piochée au total pendant le round
\return int_cartesPioche Le nombre de cartes piochées au total pendant le round + celles piochées pendant la distribution
*/
int distrib(struct sJoueur groupe[5], int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche);

/*!
\fn int points(struct sJoueur groupe[5], int int_joueur);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet de compter les points d'un participant (joueur ou croupier)
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_joueur Le joueur dont on veut compter les points
\return int_points Le nombre de points du joueur
*/
int points(struct sJoueur groupe[5], int int_joueur);

/*!
\fn void finPartie(struct sJoueur groupe[5], int int_nbJoueur);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet de mettre fin à la partie en affichant les scores
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_nbJoueur Le nombre de joueur
*/
void finPartie(struct sJoueur groupe[5], int int_nbJoueur);

/*!
\fn bool mise(struct sJoueur groupe[5],int int_joueur, int int_nbJoueur, bool bool_partieFinie);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet de faire miser un joueur (ou de le voir perdre, si il veut arrêter ou qu'il n'a plus d'argent)
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_joueur Le joueur dont on veut connaître la mise
\param int_nbJoueur Le nombre de joueurs
\param bool_partieFinie La variable servant à mettre fin au programme. Elle passe à true si un joueur mise 0, et la partie prendra fin à la fin du prochain tour.
\return bool_partieFinie : false si personne ne mise 0 (la partie continue donc), true si la partie doit se terminer 
*/
bool mise(struct sJoueur groupe[5],int int_joueur, int int_nbJoueur, bool bool_partieFinie);

/*!
\fn int tirageJ(struct sJoueur groupe[5],struct sCarte paquet[52], int int_joueur,int int_nbJoueur, int int_nbCartePioche);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Permet au joueur de tirer ou non des cartes supplémentaire lors de la partie
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\param int_joueur Le joueur dont c'est le tour
\param int_nbJoueur Le nombre de joueurs
\param int_nbCartePioche Le nombre de cartes piochée au total pendant le round
\return int_cartesPioche Le nombre de cartes piochées au total pendant le round + celles piochées lors du tirage
*/
int tirageJ(struct sJoueur groupe[5],struct sCarte paquet[52], int int_joueur,int int_nbJoueur, int int_nbCartePioche);

/*!
\fn int tirageC(struct sJoueur groupe[5], struct sCarte paquet[52], int int_nbJoueur, int int_nbCartePioche);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Gère le tour du croupier
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\param int_nbJoueur Le nombre de joueurs
\param int_nbCartePioche Le nombre de cartes piochée au total pendant le round
\return int_cartesPioche Le nombre de cartes piochées au total pendant le round + celles piochées lors du tirage
*/
int tirageC(struct sJoueur groupe[5], struct sCarte paquet[52], int int_nbJoueur, int int_nbCartePioche);

/*!
\fn void compar(struct sJoueur groupe[5], int int_nbJoueur);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Compare le score des joueurs avec celui du croupier et s'occupe des gains
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param int_nbJoueur Le nombre de joueurs
*/
void compar(struct sJoueur groupe[5], int int_nbJoueur);

/*!
\fn int tourJeu(struct sJoueur groupe[5], struct sCarte paquet[52]);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Gère le déroulement de la partie, en se servant de toutes les autre fonctions
\param sJoueur groupe[5] Un tableau de struct représentant les joueurs (max 4 + le croupier)
\param sCarte paquet[52] Le paquet de 52 cartes. Chaque cartes à une valeur et une couleur
\return 0 si tout s'est bien passé
*/
int tourJeu(struct sJoueur groupe[5], struct sCarte paquet[52]);

#endif