// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier lire_ecrire.c du jeu SOKOBAN
#include "lire_ecrire.h"

//Lis le niveau dans un fichier
SOKOBAN lire_niveau()
{
	SOKOBAN S;
	int x, y;
	char k;
	FILE *fic = fopen(nomFichier, "r");
	if (fic == NULL) {
		exit(EXIT_FAILURE);
	}
	while (S.niveau != lvl) {
		S = initialiser_sokoban();
		fscanf(fic, "%d", &S.niveau);
		for (y = 0; y < NYCASE; y++) {
			for (x = 0; x < NXCASE; x++) {
				fscanf(fic, "%c", &k);
				S.la_case[x][y].val = k;
				if (S.la_case[x][y].val == PERSONNAGE) {//enregistre les coordonner du personnage
					S.personnage.x = x;
					S.personnage.y = y;
				}
				if (S.la_case[x][y].val == PERSONNAGE_RUC) {//enregistre les coordonner du personnage
					S.personnage.x = x;
					S.personnage.y = y;
				}
				if (k == RETOUR_LIGNE) {
					x = NXCASE;
				}
				if (k == POINT_VIRGULE) {
					y = NYCASE;
					x = NXCASE;
				}
			}
		}
	}
	fclose(fic);
	return S;
}

//ecrie le niveau dans un fichier
void ecrire_niveau(SOKOBAN S)
{
	int x, y;
	FILE *fic = fopen(nomFichier, "w");
	if (fic == NULL) {
		exit(EXIT_FAILURE);
	}
	for (y = 0; y < NYCASE; y++) {
		for (x = 0; x < NXCASE; x++) {
			fputc(S.la_case[x][y].val, fic);
		}
	}
	fclose(fic);
}
