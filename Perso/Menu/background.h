#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include "texte.h"

typedef struct
{
    SDL_Surface *image[5];
    SDL_Rect posimg[5];
    int niveau;
} background;

typedef struct
{
    SDL_Surface *image;
    SDL_Rect posimg;
} image;

void initback(background *b);
void afficherback(background *b, SDL_Surface *ecran);
void initanim(image *anim[], char ch[], int posx[], int posy[], int nb);
void affichermusicbar(image *anim[], SDL_Surface *ecran, int nb, int volume);
void cleanback(background *b);
void cleananim(image *anim[], int nb);

#endif // BACKGROUND_H
