#include <stdio.h>

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