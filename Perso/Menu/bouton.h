#ifndef BOUTON_H
#define BOUTON_H

#include "background.h"

typedef struct
{
    SDL_Surface *image[2];
    SDL_Rect posimg;
    int actif;
    Mix_Chunk *son;
} bouton;

void initbouton(bouton *b[], char *nom[], int posx[], int posy[], int nb);
void afficherbouton(bouton *b[], SDL_Surface *ecran, int nb);
void boutonmotion(bouton *b[], SDL_Event *event, int nb);
void boutondownmain(bouton *bo[], SDL_Event *event, background *b, int *quitter);
void boutondownop(bouton *bo[], SDL_Event *event, SDL_Surface **ecran, background *b, int *volume, int *volumetemp, int *musicvoltemp, int *test1, int *test2);
void keydownop(bouton *bo[], SDL_Event *event, SDL_Surface **ecran, background *b, int *volume, int *volumetemp,int *musicvoltemp,int *test1, int *test2);
void boutonkeycontrol(bouton *b[], SDL_Event *event, int nb, int *inbo);
void entermain(bouton *bo[],background *b, SDL_Event *event, int *inbom,int *quitter);
void entreop(bouton *bo[], background *b, SDL_Event *event, SDL_Surface **ecran, int *volume, int *volumetemp, int *musicvoltemp, int *test1, int *test2,int *inboo);
void enterquit(bouton *bo[],background *b, SDL_Event *event, int *inbom,int *quitter,int nivtemp);
void boutondowncred(bouton *bo[], SDL_Event *event, background *b);
void boutondownquit(bouton *bo[], SDL_Event *event, background *b, int *quitter,int nivtemp);
void cleanbouton(bouton *b[], int nb);

#endif // BOUTON_H
