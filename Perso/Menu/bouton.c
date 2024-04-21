#include "bouton.h"
#include "texte.h"
void initbouton(bouton *b[], char *nom[], int posx[], int posy[], int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        b[i] = malloc(sizeof(bouton));
        if (b[i] == NULL)
        {
            fprintf(stderr, "Echec d'allocation mémoire pour le bouton %d.\n", i);
            exit(1);
        }
        b[i]->image[0] = IMG_Load(nom[2 * i]);
        b[i]->image[1] = IMG_Load(nom[2 * i + 1]);

        if (b[i]->image[0] == NULL || b[i]->image[1] == NULL)
        {
            fprintf(stderr, "Echec de chargement de l'image pour le bouton %d.\n", i);
            exit(1);
        }
        b[i]->posimg.x = posx[i];
        b[i]->posimg.y = posy[i];
        b[i]->posimg.w = b[i]->image[0]->w;
        b[i]->posimg.h = b[i]->image[0]->h;
        b[i]->actif = 0;
        b[i]->son = Mix_LoadWAV("sfx.wav");
        if (b[i]->son == NULL)
        {
            fprintf(stderr, "Echec de chargement du son : %s.\n", Mix_GetError());
            exit(1);
        }
    }
}

void afficherbouton(bouton *b[], SDL_Surface *ecran, int nb)
{
    int i = 0;
    for (i = 0; i < nb; i++)
    {
        SDL_BlitSurface(b[i]->image[b[i]->actif], NULL, ecran, &b[i]->posimg);
    }
}

void boutonmotion(bouton *b[], SDL_Event *event, int nb)
{
    int x, y, j;
    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        x = event->motion.x;
        y = event->motion.y;
        for (j = 0; j < nb; j++)
        {
            if ((x >= b[j]->posimg.x) && (x <= b[j]->posimg.x + b[j]->posimg.w) &&
                (y >= b[j]->posimg.y) && (y <= b[j]->posimg.y + b[j]->posimg.h))
            {
                if (b[j]->actif == 0)
                {
                    b[j]->actif = 1;
                    Mix_PlayChannel(-1, b[j]->son, 0);
                }
            }
            else
            {
                b[j]->actif = 0;
            }
        }
        break;
    default:
        break;
    }
}
void boutondownmain(bouton *bo[], SDL_Event *event, background *b, int *quitter)
{
    int x, y, j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 4; j++)
            {
                if ((x >= bo[j]->posimg.x) && (x <= bo[j]->posimg.x + bo[j]->posimg.w) &&
                    (y >= bo[j]->posimg.y) && (y <= bo[j]->posimg.y + bo[j]->posimg.h) &&
                    (b->niveau == 0))
                {
                    if (j == 0)
                    {
                        b->niveau = 1;
                    }
                    else if (j == 1)
                    {
                        b->niveau = 2;
                    }
                    else if (j == 2)
                    {
                        b->niveau = 3;
                    }
                    else if (j == 3)
                    {
                        b->niveau = 4;
                    }
                }
            }
        }
        break;
    }
}

void boutondownop(bouton *bo[], SDL_Event *event, SDL_Surface **ecran, background *b, int *volume, int *volumetemp, int *musicvoltemp, int *test1, int *test2)
{
    int x, y, j;

    switch (event->type)
    {
    case SDL_MOUSEMOTION:
        x = event->motion.x;
        y = event->motion.y;
        if (((x >= bo[5]->posimg.x) && (x <= bo[5]->posimg.x + bo[5]->posimg.w) &&
             (y >= bo[5]->posimg.y) && (y <= bo[5]->posimg.y + bo[5]->posimg.h)) ||
            ((*test1) == 1))
        {
            if (bo[5]->actif == 0)
            {
                bo[5]->actif = 1;
                Mix_PlayChannel(-1, bo[5]->son, 0);
            }
        }
        else
        {
            bo[5]->actif = 0;
        }

        if (((x >= bo[6]->posimg.x) && (x <= bo[6]->posimg.x + bo[6]->posimg.w) &&
             (y >= bo[6]->posimg.y) && (y <= bo[6]->posimg.y + bo[6]->posimg.h)) ||
            ((*test2) == 1))
        {
            if (bo[6]->actif == 0)
            {
                bo[6]->actif = 1;
                Mix_PlayChannel(-1, bo[6]->son, 0);
            }
        }
        else
        {
            bo[6]->actif = 0;
        }

        break;
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 7; j++)
            {
                if ((x >= bo[j]->posimg.x) && (x <= bo[j]->posimg.x + bo[j]->posimg.w) &&
                    (y >= bo[j]->posimg.y) && (y <= bo[j]->posimg.y + bo[j]->posimg.h))
                {
                    switch (j)
                    {
                    case 0:
                        b->niveau = 0;
                        break;
                    case 1:
                        if ((*volume) > 1)
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                            (*volume)--;
                        }
                        else if ((*volume) == 1)
                        {
                            Mix_VolumeMusic(0);
                            (*volumetemp) = 1;
                            (*volume)--;
                            bo[6]->actif = 1;
                            (*test2) = 1;
                        }
                        else if ((*test1) == 1)
                        {
                            system("amixer -D pulse sset Master 90%+ > /dev/null");
                            (*volume) = (*volumetemp) - 1;
                            bo[5]->actif = 0;
                            (*test1) = 0;
                        }
                        else if (((*test2) == 1))
                        {
                            Mix_VolumeMusic(*musicvoltemp - (int)(0.1 * MIX_MAX_VOLUME));
                            (*volume) = (*volumetemp) - 1;
                            bo[6]->actif = 0;
                            (*test2) = 0;
                        }
                        Mix_PlayChannel(-1, bo[0]->son, 0);
                        break;
                    case 2:
                        if ((*volume) < 10)
                        {
                            Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                            (*volume)++;
                        }
                        if ((*test1) == 1)
                        {
                            system("amixer -D pulse sset Master 110%+ > /dev/null");
                            (*volume) = (*volumetemp) + 1;
                            bo[5]->actif = 0;
                            (*test1) = 0;
                        }
                        if (((*test2) == 1) && ((*volumetemp) == 1))
                        {
                            Mix_VolumeMusic((0.1 * MIX_MAX_VOLUME));
                            (*musicvoltemp) = (0.1 * MIX_MAX_VOLUME);
                            (*volume) = (*volumetemp);
                            bo[6]->actif = 0;
                            (*test2) = 0;
                        }
                        if (((*test2) == 1) && ((*volumetemp) != 1))
                        {
                            Mix_VolumeMusic(*musicvoltemp + (int)(0.1 * MIX_MAX_VOLUME));
                            (*volume) = (*volumetemp) + 1;
                            bo[6]->actif = 0;
                            (*test2) = 0;
                        }

                        Mix_PlayChannel(-1, bo[0]->son, 0);
                        break;
                    case 3:
                        if ((*ecran) == SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                        {
                            (*ecran) = SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        break;
                    case 4:
                        if ((*ecran) == SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                        {
                            (*ecran) = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        }
                        break;
                    case 5:
                        if ((*volume) != 0)
                        {
                            system("amixer -D pulse sset Master 100%- > /dev/null");
                            (*volumetemp) = (*volume);
                            (*volume) = 0;
                            bo[5]->actif = 1;
                            (*test1) = 1;
                        }
                        else
                        {
                            system("amixer -D pulse sset Master 100%+ > /dev/null");
                            (*volume) = (*volumetemp);
                            Mix_PlayChannel(-1, bo[0]->son, 0);
                            bo[5]->actif = 0;
                            (*test1) = 0;
                        }
                        break;
                    case 6:
                        if (Mix_VolumeMusic(-1) != 0)
                        {
                            (*musicvoltemp) = Mix_VolumeMusic(-1);
                            Mix_VolumeMusic(0);
                            (*volumetemp) = (*volume);
                            (*volume) = 0;
                            bo[6]->actif = 1;
                            (*test2) = 1;
                        }
                        else
                        {
                            Mix_VolumeMusic(*musicvoltemp);
                            (*volume) = (*volumetemp);
                            Mix_PlayChannel(-1, bo[0]->son, 0);
                            bo[6]->actif = 0;
                            (*test2) = 0;
                        }
                        break;
                    }
                }
            }
        }
        break;
    }
}
void keydownop(bouton *bo[], SDL_Event *event, SDL_Surface **ecran, background *b, int *volume, int *volumetemp, int *musicvoltemp, int *test1, int *test2)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_m:
            system("amixer -D pulse sset Master 100%- > /dev/null");
            (*volumetemp) = (*volume);
            (*volume) = 0;
            Mix_PlayChannel(-1, bo[0]->son, 0);
            break;
        case SDLK_u:
            system("amixer -D pulse sset Master 100%+ > /dev/null");
            (*volume) = (*volumetemp);
            Mix_PlayChannel(-1, bo[0]->son, 0);
            break;
        case SDLK_UP:
            if ((*volume) < 10)
            {
                Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                (*volume)++;
            }
            if ((*test1) == 1)
            {
                system("amixer -D pulse sset Master 110%+ > /dev/null");
                (*volume) = (*volumetemp) + 1;
                bo[5]->actif = 0;
                (*test1) = 0;
            }
            if (((*test2) == 1) && ((*volumetemp) == 1))
            {
                Mix_VolumeMusic((0.1 * MIX_MAX_VOLUME));
                (*musicvoltemp) = (0.1 * MIX_MAX_VOLUME);
                (*volume) = (*volumetemp) + 1;
                bo[6]->actif = 0;
                (*test2) = 0;
            }
            if (((*test2) == 1) && ((*volumetemp) != 1))
            {
                Mix_VolumeMusic(*musicvoltemp + (int)(0.1 * MIX_MAX_VOLUME));
                (*volume) = (*volumetemp) + 1;
                bo[6]->actif = 0;
                (*test2) = 0;
            }
            Mix_PlayChannel(-1, bo[0]->son, 0);
            break;
        case SDLK_DOWN:
            if ((*volume) > 1)
            {
                Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                (*volume)--;
            }
            else if ((*volume) == 1)
            {
                Mix_VolumeMusic(0);
                (*volumetemp) = 1;
                (*volume)--;
                bo[6]->actif = 1;
                (*test2) = 1;
            }
            else if ((*test1) == 1)
            {
                system("amixer -D pulse sset Master 90%+ > /dev/null");
                (*volume) = (*volumetemp) - 1;
                bo[5]->actif = 0;
                (*test1) = 0;
            }
            else if (((*test2) == 1))
            {
                Mix_VolumeMusic(*musicvoltemp - (int)(0.1 * MIX_MAX_VOLUME));
                (*volume) = (*volumetemp) - 1;
                bo[6]->actif = 0;
                (*test2) = 0;
            }
            Mix_PlayChannel(-1, bo[0]->son, 0);
            break;
        case SDLK_f:
            if ((*ecran) == SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
            {
                (*ecran) = SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            break;
        case SDLK_w:
            if ((*ecran) == SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
            {
                (*ecran) = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
            }
            break;
        case SDLK_ESCAPE:
            b->niveau = 0;
            break;
        }
        break;
    }
}

void boutonkeycontrol(bouton *b[], SDL_Event *event, int nb, int *inbo)
{
    int i;
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            (*inbo)++;
            if ((*inbo) == nb)
            {
                (*inbo) = 0;
            }
            for (i = 0; i < nb; i++)
            {
                b[i]->actif = 0;
            }
            b[(*inbo)]->actif = 1;
            break;
        case SDLK_LEFT:
            (*inbo)--;
            if ((*inbo) == -1)
            {
                (*inbo) = nb - 1;
            }
            if ((*inbo) == -2)
            {
                (*inbo) = 0;
            }
            for (i = 0; i < nb; i++)
            {
                b[i]->actif = 0;
            }
            b[(*inbo)]->actif = 1;
            break;
        }
    }
}

void entermain(bouton *bo[], background *b, SDL_Event *event, int *inbo, int *quitter)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_RETURN:
            switch ((*inbo))
            {
            case 0:
                b->niveau = 1;
                break;
            case 1:
                b->niveau = 2;

                break;
            case 2:
                b->niveau = 3;

                break;
            case 3:
                b->niveau = 4;
                break;
            }
            break;
        }
    }
}

void enterquit(bouton *bo[], background *b, SDL_Event *event, int *inbo, int *quitter, int nivtemp)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_RETURN:
            switch ((*inbo))
            {
            case 0:
                b->niveau = nivtemp;
                break;
            case 1:
                (*quitter) = 0;
                break;
            }
            break;
        }
    }
}

void entreop(bouton *bo[], background *b, SDL_Event *event, SDL_Surface **ecran, int *volume, int *volumetemp, int *musicvoltemp, int *test1, int *test2, int *inboo)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_RETURN:
            switch ((*inboo))
            {
            case 0:
                b->niveau = 0;
                break;
            case 1:
                if ((*volume) > 1)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) - (int)(0.1 * MIX_MAX_VOLUME));
                    (*volume)--;
                }
                else if ((*volume) == 1)
                {
                    Mix_VolumeMusic(0);
                    (*volume)--;
                }
                Mix_PlayChannel(-1, bo[0]->son, 0);
                break;
            case 2:
                if ((*volume) < 10)
                {
                    Mix_VolumeMusic(Mix_VolumeMusic(-1) + (int)(0.1 * MIX_MAX_VOLUME));
                    (*volume)++;
                }
                Mix_PlayChannel(-1, bo[0]->son, 0);
                break;
            case 3:
                if ((*ecran) == SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                {
                    (*ecran) = SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                }
                break;
            case 4:
                if ((*ecran) == SDL_SetVideoMode(1208, 896, 32, SDL_HWSURFACE | SDL_DOUBLEBUF))
                {
                    (*ecran) = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                }
                break;
            case 5:
                if ((*volume) != 0)
                {
                    system("amixer -D pulse sset Master 100%- > /dev/null");
                    (*volumetemp) = (*volume);
                    (*volume) = 0;
                    bo[5]->actif = 1;
                    (*test1) = 1;
                }
                else
                {
                    system("amixer -D pulse sset Master 100%+ > /dev/null");
                    (*volume) = (*volumetemp);
                    Mix_PlayChannel(-1, bo[0]->son, 0);
                    bo[5]->actif = 0;
                    (*test1) = 0;
                }
                break;
            case 6:
                if (Mix_VolumeMusic(-1) != 0)
                {
                    (*musicvoltemp) = Mix_VolumeMusic(-1);
                    Mix_VolumeMusic(0);
                    (*volumetemp) = (*volume);
                    (*volume) = 0;
                    bo[6]->actif = 1;
                    (*test2) = 1;
                }
                else
                {
                    Mix_VolumeMusic(*musicvoltemp);
                    (*volume) = (*volumetemp);
                    Mix_PlayChannel(-1, bo[0]->son, 0);
                    bo[6]->actif = 0;
                    (*test2) = 0;
                }
                break;
            }
            break;
        }
    }
}

void boutondowncred(bouton *bo[], SDL_Event *event, background *b)
{
    int x, y, j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 1; j++)
            {
                if ((x >= bo[j]->posimg.x) && (x <= bo[j]->posimg.x + bo[j]->posimg.w) &&
                    (y >= bo[j]->posimg.y) && (y <= bo[j]->posimg.y + bo[j]->posimg.h))
                {
                    if (j == 0)
                    {
                        b->niveau = 0;
                    }
                }
            }
        }
        break;
    }
}

void boutondownquit(bouton *bo[], SDL_Event *event, background *b, int *quitter, int nivtemp)
{

    int x, y, j;
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        x = event->button.x;
        y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            for (j = 0; j < 2; j++)
            {
                if ((x >= bo[j]->posimg.x) && (x <= bo[j]->posimg.x + bo[j]->posimg.w) &&
                    (y >= bo[j]->posimg.y) && (y <= bo[j]->posimg.y + bo[j]->posimg.h))
                {
                    if (j == 0)
                    {
                        b->niveau = nivtemp;
                    }
                    else if (j == 1)
                    {
                        (*quitter) = 0;
                    }
                }
            }
        }
        break;
    }
}

void cleanbouton(bouton *b[], int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        SDL_FreeSurface(b[i]->image[0]);
        SDL_FreeSurface(b[i]->image[1]);
        Mix_FreeChunk(b[i]->son);
        free(b[i]);
    }
}
