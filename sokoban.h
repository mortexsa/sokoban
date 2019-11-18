// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//le fichier sokoban.h du jeu SOKOBAN
#ifndef ___SOKOBAN_H
#define ___SOKOBAN_H
#include "constantes.h"
#include <uvsqgraphics.h>
typedef struct une_case {
	char val;
	int nbrclic;
}une_case;

typedef struct perso {
	int x;
	int y;
}PERSO;

struct sokoban {
	int niveau;
	int coupsjouer;
	int modifiable;
	PERSO personnage;
	une_case la_case [NXCASE][NYCASE];
};
typedef struct sokoban SOKOBAN;
SOKOBAN initialiser_sokoban();
SOKOBAN initialiser_sokoban_creation();
void lancer_jeu(SOKOBAN S);
void creer_niveau(SOKOBAN S);
int lvl;
#endif
