/*!
\file utile.c
\author Charrier Simon
\version 1
\date 3 décembre 2023
\brief Fonctions utiles
*/

#include <stdio.h>

// Demande un nombre entier entre min et max, après avoir posé une question
int ask(char text[],int min,int max)
{
    int a,test;
    do{
        printf ("%s",text);
        test = scanf("%d",&a);
        int d = 0;
        while((d = getchar() != '\n') && d != EOF){}   
    }while((test==0) || (a <= (min-1)) || (a >= (max+1)));
    return a;
}