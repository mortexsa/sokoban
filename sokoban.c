// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier sokoban.c du jeu SOKOBAN
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sokoban.h"
#include "lire_ecrire.h"
#include <uvsqgraphics.h>
#include "affichage.h"
#include "creation.h"
#include "action.h"
#include "historique.h"

//initialiser la structure SOKOBAN
SOKOBAN initialiser_sokoban()
{
	SOKOBAN S;
	S.niveau = VIDE;
	S.coupsjouer = VIDE;
	S.personnage.x = VIDE;
	S.personnage.y = VIDE;
	S.modifiable = VIDE;
	int x, y;
	for (y = VIDE; y < NYCASE; y++) {
		for (x = VIDE; x < NXCASE; x++) {
			S.la_case[x][y].val = VIDE;
			S.la_case[x][y].nbrclic = VIDE;
		}
	}
	return S;
}

//inialiser la structure SOKOBAN pour le mode création
SOKOBAN initialiser_sokoban_creation()
{
	SOKOBAN S;
	S.niveau = VIDE;
	S.coupsjouer = VIDE;
	S.personnage.x = VIDE;
	S.personnage.y = VIDE;
	S.modifiable = VIDE;
	int x, y;
	for (y = VIDE; y < NYCASE; y++) {
		for (x = VIDE; x < NXCASE; x++) {
			S.la_case[x][y].val = ESPACE;
			S.la_case[x][y].nbrclic = VIDE;
		}
	}
	S.la_case[0][0].val = POINT_VIRGULE;	//le point du depart du niveau
	S.la_case[2][0].val = '1';	// numéro du niveau (je choisi 1)
	for (y = VIDE; y < NYCASE; y++) {
		S.la_case[NXCASE - 1][y].val = RETOUR_LIGNE;	//les retour a la ligne a la fin de chaque ligne
	}
	return S;
}

//lancer le mode jouer 
void lancer_jeu(SOKOBAN S)
{
	S = lire_niveau();
	P = inserer_pile(P, S);
	while (1) {
		afficher_niveau(S);
		S = bouger_personnage(S);
	}
}

//lancer le mode creation
void creer_niveau(SOKOBAN S)
{
	S = initialiser_sokoban_creation();
	while (1) {
		afficher_creation(S);
		S = action_creation(S);
	}
}

int main(int argc, char *argv[])
{
	initialiser_affichage();
	SOKOBAN S;
	S = initialiser_sokoban();
	P = nouvelle_pile();
	P2 = nouvelle_pile();
	lvl = 1;
	if (argc > 4) {//si on a plus de 4 argument
		printf("\nNombre d'arguments anormalement élevé\n");
		exit(0);
	} else if (argc > 1) {// si on a plus de 1 argument
		if (argc == 2) {//si on a deux argument
			nomFichier = argv[1];
			lancer_jeu(S);
		} else if (strcmp(argv[1], "-c") == 0) {
			nomFichier = argv[2];
			creer_niveau(S);
		} else if (strcmp(argv[1], "-n") == 0) {
			if (atoi(argv[2]) == 0 || atoi(argv[2]) > 50) {//entrée d'un niveau inexistant
				printf("Niveau inéxistant.\n");
				exit(0);
			}
			lvl = atoi(argv[2]);//affectation du numero du lvl dans la variable 'lvl'
			nomFichier = argv[3];
			lancer_jeu(S);
		} else {//commande incorrect
			printf("\nLa commande '%s' est incorrect, veuillez selection une des suivante : ", argv[1]);
			printf("\n -n pour débuter un niveau précis ");
			printf("\n -c pour lancer la création d'un niveau\n");
			exit(0);
		}
	}
	exit(0);
}
