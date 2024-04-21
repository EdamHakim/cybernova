// perso.h

#ifndef PERSO_H
#define PERSO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "texte.h"

typedef struct
{
    SDL_Surface *sprite;
    SDL_Rect poSprite;
    SDL_Rect poScreen;
    int direction;
} sprite;


typedef struct
{
    sprite *perso;
    text *scoreimg;
    int nbvie,score,newscore;
    int up;
    double vitesse,acceleration;
} Personne;

void initPerso(Personne *p[], int numperso, int nbc,int nbl);
void afficherPerso(Personne *p[], SDL_Surface *screen, int *multiplayer);
void animerPerso(Personne *p[]);
void movePerso(Personne *p[], Uint32 dt,SDL_Surface *screen);
void saut(Personne *p[], int seuil, Uint32 dt);
void freePerso(Personne *p[], int numperso);

#endif /* PERSO_H */
