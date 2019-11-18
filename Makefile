#// Nom : Slimani 
#// Prénom : Arezki
#// n° étudiant : 21502933
#// gestion de la compilation des differents fichier du jeu SOKOBAN 

CFLAGS=-c -g -Wall

all: clean compil
	
test: clean compil
	./sokoban -n 8 sasquatch1.xsb
	
compil: sokoban.o affichage.o action.o lire_ecrire.o creation.o historique.o
	gcc -o sokoban sokoban.o affichage.o action.o lire_ecrire.o creation.o historique.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

sokoban.o: sokoban.c sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` sokoban.c

affichage.o: affichage.c affichage.h sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` affichage.c

action.o: action.c action.h sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` action.c

lire_ecrire.o: lire_ecrire.c lire_ecrire.h sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` lire_ecrire.c

creation.o: creation.c creation.h sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` creation.c

historique.o: historique.c historique.h sokoban.h constantes.h
	gcc $(CFLAGS) `sdl-config --cflags` historique.c

clean:
	rm -f sokoban	
	rm -f sokoban.o
	rm -f affichage.o
	rm -f action.o
	rm -f lire_ecrire.o
	rm -f creation.o
	rm -f historique.o
	