#include "texte.h"

void initText(text *A, char ch[], int x, int y, int color[], int taille,int font)
{
    if (ch == NULL)
    {
        fprintf(stderr, "Invalid input string in initText\n");
        exit(1);
    }
    strcpy(A->texte, ch);
    A->position.x = x;
    A->position.y = y;
    A->textColor.r = color[0];
    A->textColor.g = color[1];
    A->textColor.b = color[2];
    if(font==0)
    {
        A->font = TTF_OpenFont("Before-Modern.ttf", taille);
    }
    else
    {
        A->font = TTF_OpenFont("neon.ttf", taille);
    }
    
    if (A->font == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir la police de caractères : %s\n", TTF_GetError());
        exit(1);
    }
}

void afficherText(text *A, SDL_Surface *ecran)
{
    A->surfaceTexte = TTF_RenderText_Solid(A->font, A->texte, A->textColor);
    if (A->surfaceTexte == NULL)
    {
        fprintf(stderr, "Impossible de rendre le texte : %s\n", TTF_GetError());
        exit(1);
    }
    SDL_BlitSurface(A->surfaceTexte, NULL, ecran, &A->position);
}

void cleanText(text *A)
{
    SDL_FreeSurface(A->surfaceTexte);
}
