#include "background.h"

void initback(background *b)
{
    int i;
    char *nom[] = {"main.png", "play.png", "options.png", "credits.png", "quit.png"};

    for (i = 0; i < 5; i++)
    {
        b->image[i] = IMG_Load(nom[i]);
        if (b->image[i] == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
        b->posimg[i].x = 0;
        b->posimg[i].y = 0;
        b->posimg[i].w = b->image[0]->w;
        b->posimg[i].h = b->image[0]->h;
    }
    b->niveau = 0;
    b->posimg[4].x = 170;
    b->posimg[4].y = 140;   

}

void afficherback(background *b, SDL_Surface *ecran)
{
    SDL_BlitSurface(b->image[b->niveau], NULL, ecran, &b->posimg[b->niveau]);
}

void initanim(image *anim[], char ch[], int posx[], int posy[], int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        char animimagename[20];
        sprintf(animimagename, "%s%d.png", ch, i);
        anim[i] = malloc(sizeof(image));
        if (anim[i] == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour le bouton %d.\n", i);
            exit(1);
        }
        anim[i]->image = IMG_Load(animimagename);
        if (anim[i]->image == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }
        else
        {
            anim[i]->posimg.x = posx[0];
            anim[i]->posimg.y = posy[0];
            anim[i]->posimg.w = anim[i]->image->w;
            anim[i]->posimg.h = anim[i]->image->h;
        }
    }
}

void affichermusicbar(image *musicbar[], SDL_Surface *ecran, int nb, int volume)
{

    SDL_BlitSurface(musicbar[volume]->image, NULL, ecran, &musicbar[volume]->posimg);
}

void cleanback(background *b)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        SDL_FreeSurface(b->image[i]);
    }
    free(b);
}
void cleananim(image *anim[], int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        SDL_FreeSurface(anim[i]->image);
    }
}
