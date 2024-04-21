
#include "background.h"
#include "bouton.h"
#include "perso.h"

int main(int argc, char **argv)
{

    Uint32 mainstarTime, mainendTime, opstarTime, opendTime;
    Uint32 persostarTime, persoendTime;
    Uint32 dt = 0, t_prev = 0;
    int quitter = 1, volume = 5, volumetemp = 5, musicvoltemp, i = 0, j = 0, inbom = -1, inboo = -1, inboq = -1, k = 0, nivtemp = 0;
    int test1 = 0, test2 = 0;
    char *nommain[] = {"playoff.png", "playon.png", "optionsoff.png", "optionson.png", "creditsoff.png", "creditson.png", "quitoff.png", "quiton.png"};
    char *nomop[] = {"backoff.png", "backon.png", "-off.png", "-on.png", "+off.png", "+on.png", "fullscreenoff.png", "fullscreenon.png", "windowedoff.png", "windowedon.png", "volumeunmuted.png", "volumemuted.png", "musicunmuted.png", "musicmuted.png"};
    char *nomcred[] = {"backoff.png", "backon.png"};
    char *nomquit[] = {"qplayoff.png", "qplayon.png", "qquitoff.png", "qquiton.png"};
    char chtmain[] = "Cybernova";
    char chtbomo[] = "Selected";
    background *b = malloc(sizeof(background));
    if (b == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for background\n");
        exit(1);
    }
    int numperso = 1;
    Personne *p[1];
    bouton *bomain[4];
    bouton *boop[7];
    bouton *bocred[1];
    bouton *boquit[2];
    image *animmain[18];
    image *musicbar[11];
    image *animop[36];
    text *tmain = malloc(sizeof(text));
    text *tbomotion[4];
    int posmainx[] = {20, 210, 400, 590};
    int posmainy[] = {498, 498, 498, 498};
    int posopx[] = {45, 318, 719, 50, 570, 300, 450};
    int posopy[] = {30, 250, 262, 498, 498, 498, 498};
    int posopmbx[] = {357};
    int posopmby[] = {260};
    int poscredx[] = {25};
    int poscredy[] = {30};
    int posquitx[] = {230, 420};
    int posquity[] = {320, 320};
    int posanimmainx[] = {0};
    int posanimmainy[] = {0};
    int posanimopx[] = {0};
    int posanimopy[] = {0};
    int postextemainx[] = {175};
    int postextemainy[] = {20};
    int postextebomainx[] = {20, 210, 400, 590};
    int postextebomainy[] = {468, 468, 468, 468};
    int colortextemain[] = {251, 170, 25};
    int multiplayer = 0;
    char animmainname[] = "mani";
    char animopname[] = "opani";
    char musicimagename[] = "mb";
    SDL_Surface *ecran;
    SDL_Event event;
    Mix_Music *musique;
    // Initialisation
    TTF_Init();
    if (TTF_Init() != 0)
    {
        printf("Echec d'initialisation de SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        printf("Bonjour le monde, SDL est initialisé avec succès.\n");
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Echec de creation de la fenetre : %s.\n", SDL_GetError());
        exit(1);
    }
    initback(b);

    initanim(animmain, animmainname, posanimmainx, posanimmainy, 18);
    initanim(musicbar, musicimagename, posopmbx, posopmby, 11);
    initanim(animop, animopname, posanimopx, posanimopy, 36);
    initbouton(bomain, nommain, posmainx, posmainy, 4);
    initbouton(boop, nomop, posopx, posopy, 7);
    initbouton(bocred, nomcred, poscredx, poscredy, 1);
    initbouton(boquit, nomquit, posquitx, posquity, 2);
    initText(tmain, chtmain, postextemainx[0], postextemainy[0], colortextemain, 48, 0);
    initPerso(p, 1, 6, 4);

    for (i = 0; i < 4; i++)
    {
        tbomotion[i] = malloc(sizeof(text));
        initText(tbomotion[i], chtbomo, postextebomainx[i], postextebomainy[i], colortextemain, 16, 0);
    }
    musique = Mix_LoadMUS("soncontinue.mp3");
    Mix_PlayMusic(musique, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    while (quitter)
    {
        mainstarTime = SDL_GetTicks();
        opstarTime = SDL_GetTicks();
        persostarTime = SDL_GetTicks();
        Uint32 t_curr = SDL_GetTicks();
        Uint32 dt = t_curr - t_prev;
        t_prev = t_curr;
        afficherback(b, ecran);
        switch (b->niveau)
        {
        case 0:
            SDL_BlitSurface(animmain[i]->image, NULL, ecran, &animmain[i]->posimg);
            afficherText(tmain, ecran);
            afficherbouton(bomain, ecran, 4);
            for (j = 0; j < 4; j++)
            {
                if (bomain[j]->actif == 1)
                {

                    afficherText(tbomotion[j], ecran);
                }
            }
            SDL_Flip(ecran);
            mainendTime = SDL_GetTicks();
            if (mainendTime - mainstarTime < 30)
            {
                SDL_Delay(30 - (mainendTime - mainstarTime));
            }
            i++;
            if (i >= 18)
            {
                i = 0;
            }
            break;
        case 1:
            afficherPerso(p, ecran, &multiplayer);
            persoendTime = SDL_GetTicks();
            if (persoendTime - persostarTime < 150)
            {
                SDL_Delay(150 - (persoendTime - persostarTime));
            }
            movePerso(p, dt, ecran);
            break;
        case 2:
            SDL_BlitSurface(animop[k]->image, NULL, ecran, &animop[k]->posimg);
            opendTime = SDL_GetTicks();
            if (opendTime - opstarTime < 30)
            {
                SDL_Delay(30 - (opendTime - opstarTime));
            }
            k++;
            if (k >= 36)
            {
                k = 0;
            }
            afficherbouton(boop, ecran, 7);
            affichermusicbar(musicbar, ecran, 11, volume);
            SDL_Flip(ecran);
            break;
        case 3:
            afficherbouton(bocred, ecran, 1);
            break;
        case 4:
            afficherbouton(boquit, ecran, 2);
            break;
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                b->niveau = 4;
            }
            switch (b->niveau)
            {
            case 0:
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        b->niveau = 4;
                        break;
                    case SDLK_p:
                        b->niveau = 1;
                        break;
                    case SDLK_o:
                        b->niveau = 2;
                        break;
                    case SDLK_q:
                        b->niveau = 4;
                        break;
                    }
                }
                boutonmotion(bomain, &event, 4);
                boutondownmain(bomain, &event, b, &quitter);
                boutonkeycontrol(bomain, &event, 4, &inbom);
                entermain(bomain, b, &event, &inbom, &quitter);
                nivtemp = 0;

                break;
            case 1:
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        b->niveau = 0;
                        break;
                    case SDLK_UP:
                        p[0]->up = 1;
                        break;
                    case SDLK_RIGHT:
                        p[0]->perso->direction = 0;
                        break;
                    case SDLK_LEFT:
                        p[0]->perso->direction = 1;
                        break;
                    default:
                        p[0]->perso->direction = -1;
                        break;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        p[0]->up = 0;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                        p[0]->vitesse = 0;
                        p[0]->acceleration = 0;
                        p[0]->perso->direction = -1;
                        break;
                    }
                }
                saut(p, 360,dt);
                nivtemp = 1;

                break;
            case 2:
                boutonmotion(boop, &event, 5);
                keydownop(boop, &event, &ecran, b, &volume, &volumetemp, &musicvoltemp, &test1, &test2);
                boutondownop(boop, &event, &ecran, b, &volume, &volumetemp, &musicvoltemp, &test1, &test2);
                boutonkeycontrol(boop, &event, 7, &inboo);
                entreop(boop, b, &event, &ecran, &volume, &volumetemp, &musicvoltemp, &test1, &test2, &inboo);
                nivtemp = 2;

                break;
            case 3:
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        b->niveau = 0;
                        break;
                    }
                }
                boutonmotion(bocred, &event, 1);
                boutondowncred(bocred, &event, b);
                nivtemp = 3;
                break;
            case 4:
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        b->niveau = 0;
                        break;

                    case SDLK_q:
                        quitter = 0;
                        break;
                    }
                }
                boutonmotion(boquit, &event, 2);
                boutondownquit(boquit, &event, b, &quitter, nivtemp);
                boutonkeycontrol(boquit, &event, 2, &inboq);
                enterquit(boquit, b, &event, &inboq, &quitter, nivtemp);

                break;
            }
        }
        SDL_Flip(ecran);
    }
    cleanback(b);
    cleanbouton(bomain, 4);
    cleanbouton(boop, 7);
    cleanbouton(bocred, 1);
    cleananim(animmain, 18);
    cleananim(musicbar, 11);
    cleanText(tmain);
    freePerso(p, numperso);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
