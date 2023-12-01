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
    struct sCarte carte;
    int score;
};

void initialisation(struct sCarte paquet[52]);
struct sJoueur* enregistrement(int int_joueurs);

#endif