/*!
\file utile.h
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Fonctions utiles
*/

#ifndef __UTILE_H_
#define __UTILE_H_

/*!
\fn int ask(char text[],int min,int max);
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Demande un entier entre min et max à l'utilisateur en lui affichant la question
\param text[] la question à afficher
\param min le minimum
\param max le maximum
\return a l'entier entre min et max entré par l'utilisateur.
*/
int ask(char text[],int min,int max);

#endif