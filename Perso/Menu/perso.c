#include "perso.h"

void initPerso(Personne *p[], int numperso, int nbc, int nbl)
{
    int i;
    int colorscore[] = {251, 170, 25};
    int posscorex[] = {50};
    int posscorey[] = {10};

    for (i = 0; i < numperso; i++)
    {
        p[i] = malloc(sizeof(Personne));
        if (p[i] == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour le personnage %d.\n", i);
            exit(1);
        }
        p[i]->perso = malloc(sizeof(sprite));
        if (p[i]->perso == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour la sprite sheet.\n");
            exit(1);
        }

        // Initialize fields
        p[i]->perso->sprite = NULL;
        p[i]->perso->direction = -1;
        p[i]->nbvie = 3;
        p[i]->score = 0;
        p[i]->newscore = 0;
        p[i]->up = 0;
        p[i]->vitesse = 5;
        p[i]->acceleration = 0;

        p[i]->scoreimg = malloc(sizeof(text));
        if (p[i]->scoreimg == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour scoreimg du personnage %d.\n", i);
            exit(1);
        }

        // Load sprite
        p[i]->perso->sprite = IMG_Load("spritesheet.png");
        if (p[i]->perso->sprite == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image : %s.\n", IMG_GetError());
            exit(1);
        }

        // Calculate dimensions
        p[i]->perso->poSprite.w = p[i]->perso->sprite->w / nbc;
        p[i]->perso->poSprite.h = p[i]->perso->sprite->h / nbl;
        p[i]->perso->poScreen.w = p[i]->perso->sprite->w / nbc;
        p[i]->perso->poScreen.h = p[i]->perso->sprite->h / nbl;

        // Set position and initialize text
        p[i]->perso->poSprite.x = 0;
        p[i]->perso->poSprite.y = 0;
        p[i]->perso->poScreen.x = 50;
        p[i]->perso->poScreen.y = 450;
        initText(p[i]->scoreimg, "0", posscorex[0], posscorey[0], colorscore, 64, 1);
    }
}

void afficherPerso(Personne *p[], SDL_Surface *screen, int *multiplayer)
{
    if (p[0] != NULL && p[0]->perso != NULL && p[0]->perso->sprite != NULL)
    {
        SDL_BlitSurface(p[0]->perso->sprite, &p[0]->perso->poSprite, screen, &p[0]->perso->poScreen);
        afficherText(p[0]->scoreimg, screen);
    }
}

void animerPerso(Personne *p[])
{

    int largeurSprite = p[0]->perso->sprite->w;
    if (p[0]->perso->direction != -1)
    {
        if (p[0]->perso->poSprite.x + 2 * p[0]->perso->poSprite.w >= largeurSprite)
        {
            p[0]->perso->poSprite.x = 0;
        }
        else
        {
            p[0]->perso->poSprite.x += p[0]->perso->poSprite.w;
        }
        p[0]->perso->poSprite.y = p[0]->perso->direction * p[0]->perso->poSprite.h;
    }
}

void movePerso(Personne *p[], Uint32 dt, SDL_Surface *screen)
{
    double pasAvancement;

    switch (p[0]->perso->direction)
    {
    case 0:
        p[0]->vitesse = 5;
        p[0]->acceleration += 0.0003;
        animerPerso(p);
        break;
    case 1:
        p[0]->vitesse = -5;
        p[0]->acceleration -= 0.0003;
        animerPerso(p);
        break;
    }
    if (p[0]->acceleration != 0.0)
    {
        pasAvancement = p[0]->vitesse * (dt / 1000) + 0.5 * p[0]->acceleration * pow((dt / 2), 2);
        p[0]->perso->poScreen.x += (int)pasAvancement;
    }

    // Clamp character position to screen boundaries
    if (p[0]->perso->poScreen.x < 0)
        p[0]->perso->poScreen.x = 0;
    else if (p[0]->perso->poScreen.x > (screen->w - p[0]->perso->poSprite.w))
        p[0]->perso->poScreen.x = screen->w - p[0]->perso->poSprite.w;
}

void saut(Personne *p[], int seuil, Uint32 dt)
{
    double maxJumpHeight = 450.0 - seuil;
    double startJumpHeight = 40.0;
    double jumpSpeed = 0.45; 
    if (p[0]->up == 1 && p[0]->perso->poScreen.y >= (450 - seuil))
    {

        double jumpHeight = startJumpHeight * (1 + fabs(p[0]->acceleration) * 2500); 
        double deltaY = jumpSpeed * (dt);
        if(jumpHeight>maxJumpHeight)
        {
            jumpHeight>maxJumpHeight;
        }
        p[0]->perso->poScreen.y -= (int)deltaY;

        if (p[0]->perso->poScreen.y < (450 - jumpHeight))
            p[0]->perso->poScreen.y = (450 - jumpHeight);

        p[0]->perso->poScreen.x += 0.5 * p[0]->acceleration * pow((dt), 2);

        animerPerso(p);
    }
    else
    {
        double deltaY = jumpSpeed * (dt);
        p[0]->perso->poScreen.y += (int)deltaY;

        if (p[0]->perso->poScreen.y > 450)
            p[0]->perso->poScreen.y = 450;

        animerPerso(p);
    }
}

void freePerso(Personne *p[], int numperso)
{
    int i;
    for (i = 0; i < numperso; i++)
    {
        if (p[i] != NULL)
        {
            if (p[i]->perso != NULL)
            {
                if (p[i]->perso->sprite != NULL)
                {
                    SDL_FreeSurface(p[i]->perso->sprite);
                    p[i]->perso->sprite = NULL;
                }
                free(p[i]->perso);
                p[i]->perso = NULL;
            }
            if (p[i]->scoreimg != NULL)
            {
                cleanText(p[i]->scoreimg);
                free(p[i]->scoreimg);
                p[i]->scoreimg = NULL;
            }
            free(p[i]);
            p[i] = NULL;
        }
    }
}
