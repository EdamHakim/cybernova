prog: main.o background.o bouton.o texte.o perso.o
	gcc main.o background.o bouton.o texte.o perso.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lm

main.o: main.c
	gcc -c main.c -o main.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

background.o: background.c
	gcc -c background.c -o background.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

bouton.o: bouton.c
	gcc -c bouton.c -o bouton.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

texte.o: texte.c
	gcc -c texte.c -o texte.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

perso.o: perso.c
	gcc -c perso.c -o perso.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
