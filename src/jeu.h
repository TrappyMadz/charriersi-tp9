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
    char* nom;
    int argent;
    int mise;
    struct sCarte carte[10];
    int pioche;
    int score;
};

void initialisation(struct sCarte paquet[52], int int_cartesPioche);
int pioche(struct sJoueur* groupe, struct sCarte paquet[52], int int_joueur, int int_cartePioche);
struct sJoueur* enregistrement(int int_joueurs);
void affichCarte(struct sJoueur* joueur, int int_joueur);
int distrib(struct sJoueur* groupe, int int_nbJoueur, struct sCarte paquet[52], int int_cartePioche);
int nbJoueur();
#endif