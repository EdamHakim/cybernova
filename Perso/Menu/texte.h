#ifndef Texte_H
#define Texte_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

typedef struct
{
    SDL_Surface *surfaceTexte;
    SDL_Rect position;
    TTF_Font *font;
    SDL_Color textColor;
    char texte[50];
} text;

void initText(text *A, char ch[], int x, int y, int color[], int taille,int font);
void afficherText(text *A, SDL_Surface *ecran);
void cleanText(text *A);
#endif
