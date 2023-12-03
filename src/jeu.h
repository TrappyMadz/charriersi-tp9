/*!
\file utiles.h
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Fichier h associé aux fonctions utiles
*/

#ifndef __JEU_H_
#define __JEU_H_

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

void initialisation(struct sCarte paquet[52], int int_cartesPioche);
int pioche(struct sJoueur groupe[5], struct sCarte paquet[52], int int_joueur, int int_cartePioche);
void enregistrement(int int_joueurs, struct sJoueur groupe[5]);
void affichCarte(struct sJoueur joueur[5], int int_joueur);
int distrib(struct sJoueur groupe[5], int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche);
int points(struct sJoueur groupe[5], int int_joueur);
void finPartie(struct sJoueur groupe[5], int int_nbJoueur);
void mise(struct sJoueur groupe[5],int int_joueur, int int_nbJoueur);
#endif