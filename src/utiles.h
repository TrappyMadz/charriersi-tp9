/*!
\file utiles.h
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Fichier h associé aux fonctions utiles
*/

#ifndef __UTILES_H_
#define __UTILES_H_

/*!
\fn void afftab(int* tint_tab, int int_taille)
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Affichage d'un tableau d'entiers
\param tint_tab Un tableau d'entiers
\param int_taille La taille du tableau
*/
void afftab(int* tint_tab, int int_taille);

/*!
\fn void afftab(int* tint_tab, int int_taille)
\author Charrier Simon
\version 1
\date 17 novembre 2023
\brief Demande à l'utilisateur d'un tableau d'entier et stockage de ce derniers (NE PAS OUBLIER DE FREE APRES UTILISATION)
\return Un tableau d'entier entré par l'utilisateur
\param int_taille La taille du futur tableau
*/
int* eTab(int int_taille);

#endif