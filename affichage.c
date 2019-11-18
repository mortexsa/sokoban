// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier affichage.c du jeu SOKOBAN
#include "affichage.h"
#include "creation.h"
/*
* Initialise la fenétre graphique
*/
void initialiser_affichage()
{
	init_graphics(LONG_FENETRE, HAUT_FENETRE);
	affiche_auto_off();
}

/*
* Affiche le numero du niveau
* @param S la structure qui enregistre les donner du niveau
*/
void numero_niveau(SOKOBAN S)
{
	POINT p;
	p.x = LONG_FENETRE / 12;
	p.y = HAUT_FENETRE - TAILLE_POLICE;
	aff_int(S.niveau, TAILLE_POLICE, p, COUL_POLICE);
	p.x = 0;
	aff_pol("Niveau:", TAILLE_POLICE, p, COUL_POLICE);
}

/*
* Affiche le nombre de coup jouer par le joueur
* @param S la structure qui enregistre les donner du niveau
*/
void coups_jouer(SOKOBAN S)
{
	POINT p;
	p.x = LONG_FENETRE / 3 + 5;
	p.y = HAUT_FENETRE - TAILLE_POLICE;
	aff_int(S.coupsjouer, TAILLE_POLICE, p, COUL_POLICE);
	p.x = LONG_FENETRE / 5;
	aff_pol("Coups Jouer:", TAILLE_POLICE, p, COUL_POLICE);
}

/*
* Affiche le nom du fichier ou se trouve les niveaux
* @param texte Le nom du fichier
*/
void nom_fichier(char *texte)
{
	POINT p;
	p.x = LONG_FENETRE / 2;
	p.y = HAUT_FENETRE - TAILLE_POLICE;
	aff_pol("Fichier:", TAILLE_POLICE, p, COUL_POLICE);
	p.x = p.x + 80;
	aff_pol(texte, TAILLE_POLICE, p, COUL_POLICE);
}

/*
* Affiche un message 
* @param text Le message qu'on veut afficher
* @param x C'est pour l'emplacement du message sur l'axe des abscisses 
*/
void afficher_message(char *text, int x)
{
	POINT p;
	p.x = TAILLE_CASE * x;
	p.y = HAUT_FENETRE - TAILLE_POLICE;
	aff_pol(text, TAILLE_POLICE, p, COUL_POLICE);
}

/*
* Affiche un boutton
* @param numero Emplacement sur l'axe des abscisse du boutton
* @param texte Le texte qui se trouve dans le boutton
*/
void afficher_un_bouton(int numero, char *texte)
{
	POINT bg, hd, centre;
	bg.x = numero * LONG_BOUTON;
	bg.y = 0;
	hd.x = bg.x + LONG_BOUTON;
	hd.y = bg.y + HAUT_BOUTON;
	centre.x = (bg.x + hd.x) / 2;
	centre.y = (bg.y + hd.y) / 2;
	draw_fill_rectangle(bg, hd, COUL_FOND);
	draw_rectangle(bg, hd, COUL_MUR);
	aff_pol_centre(texte, TAILLE_POLICE, centre, COUL_POLICE);
}

/*
* Affiche tout les bouttons
*/
void afficher_les_boutons()
{
	afficher_un_bouton(0, "UNDO");
	afficher_un_bouton(1, "REDO");
	afficher_un_bouton(2, "INIT");
	afficher_un_bouton(3, "PRECEDENT");
	afficher_un_bouton(4, "SUIVANT");
	afficher_un_bouton(5, "QUIT");
}

/*
* Affiche un carré non remplie blanc
*/
void afficher_carre_vide(int x, int y)
{
	POINT p, p1;
	p.x = x * TAILLE_CASE;
	p.y = HAUT_FENETRE - y * TAILLE_CASE;
	p1.x = p.x + TAILLE_CASE;
	p1.y = p.y - TAILLE_CASE;
	draw_rectangle(p, p1, COUL_MUR);
}

/*
* Affiche un carré remplie
*/
void afficher_carre(int x, int y, COULEUR c)
{
	POINT p, p1;
	p.x = x * TAILLE_CASE;
	p.y = HAUT_FENETRE - y * TAILLE_CASE;
	p1.x = p.x + TAILLE_CASE;
	p1.y = p.y - TAILLE_CASE;
	draw_fill_rectangle(p, p1, c);
	draw_rectangle(p, p1, VIDE);
}

/*
* Affiche un objectif 
*/
void afficher_ruc(int x, int y, COULEUR c)
{
	POINT p, p1;
	p.x = x * TAILLE_CASE;
	p.y = HAUT_FENETRE - y * TAILLE_CASE;
	p1.x = p.x + TAILLE_CASE;
	p1.y = p.y - TAILLE_CASE;
	draw_rectangle(p, p1, c);
	draw_line(p, p1, c);
	p.x = p1.x;
	p1.x = x * TAILLE_CASE;
	draw_line(p, p1, c);
}

/*
* Affiche un personnage
*/
void afficher_personnage(int x, int y, COULEUR c)
{
	POINT p;
	p.x = x * TAILLE_CASE + (TAILLE_CASE / 2);
	p.y = HAUT_FENETRE - y * TAILLE_CASE - (TAILLE_CASE / 2);
	draw_fill_circle(p, TAILLE_CASE / 2, c);
}

/*
* Affiche toute les cases du niveau
*/
void afficher_case(SOKOBAN S, int x, int y)
{
	if (S.la_case[x][y].val == MUR) {
		afficher_carre(x, y, COUL_MUR);
	}
	if (S.la_case[x][y].val == CAISSE) {
		afficher_carre(x, y, COUL_CAISSE);
	}
	if (S.la_case[x][y].val == RUC) {
		afficher_ruc(x, y, COUL_RUC);
	}
	if (S.la_case[x][y].val == PERSONNAGE) {
		afficher_personnage(x, y, COUL_PERSONNAGE);
	}
	if (S.la_case[x][y].val == CAISSE_RUC) {
		afficher_carre(x, y, COUL_CAISSE_RUC);
	}
	if (S.la_case[x][y].val == PERSONNAGE_RUC) {
		afficher_ruc(x, y, COUL_RUC);
		afficher_personnage(x, y, COUL_PERSONNAGE_RUC);
	}
}

/*
* Affiche le niveau complet
*/
void afficher_niveau(SOKOBAN S)
{
	int x, y;
	fill_screen(COUL_VIDE);
	for (y = VIDE; y < NYCASE; y++) {
		for (x = VIDE; x < NXCASE; x++) {
			afficher_case(S, x, y);
		}
	}
	afficher_les_boutons();
	numero_niveau(S);
	coups_jouer(S);
	nom_fichier(nomFichier);
	affiche_all();
}

/*-----------affichage-mode-creation---------------*/

/*
* Affiche une case pour le mode création
*/
void afficher_case_creation(SOKOBAN S, int x, int y)
{
	if (S.la_case[x][y].val == MUR) {
		afficher_carre(x, y, COUL_MUR);
	}
	if (S.la_case[x][y].val == CAISSE) {
		afficher_carre(x, y, COUL_CAISSE);
	}
	if (S.la_case[x][y].val == RUC) {
		afficher_ruc(x, y, COUL_RUC);
	}
	if (S.la_case[x][y].val == PERSONNAGE) {
		afficher_personnage(x, y, COUL_PERSONNAGE);
	}
	if (S.la_case[x][y].val == CAISSE_RUC) {
		afficher_carre(x, y, COUL_CAISSE_RUC);
	}
	if (S.la_case[x][y].val == PERSONNAGE_RUC) {
		afficher_ruc(x, y, COUL_RUC);
		afficher_personnage(x, y, COUL_PERSONNAGE_RUC);
	} else {
		afficher_carre_vide(x, y);
	}
}

/*
* Affiche les bouttons pour le mode création
*/
void boutons_creation()
{
	afficher_un_bouton(0, "INIT");
	afficher_un_bouton(1, "JOUER");
	afficher_un_bouton(2, "UNDO");
	afficher_un_bouton(3, "REDO");
	afficher_un_bouton(4, "SAVE");
	afficher_un_bouton(5, "QUIT");
}

/*
* Affiche le mode création
*/
void afficher_creation(SOKOBAN S)
{
	int x, y;
	fill_screen(COUL_VIDE);
	for (y = 2; y < NYCASE - 1; y++) {
		for (x = VIDE; x < NXCASE - 1; x++) {
			afficher_case_creation(S, x, y);
		}
	}
	boutons_creation();
	if (verifier_un_perso(S) == 0 && S.modifiable == 0) {
		afficher_message("AUCUN PERSO", 0);
	}
	if (verifier_un_perso(S) > 1 && S.modifiable == 0) {
		afficher_message("UN SEUL PERSO AUTORISER", 0);
	}
	if (verifier_caisse(S) == 0 && S.modifiable == 0) {
		afficher_message("AUCUNE CAISSE", 12);
	}
	if (S.modifiable == 0
	    && verifier_murs_fermer(S, S.personnage.x, S.personnage.y) == 0) {
		afficher_message("FERMER MUR ET LANCER JOUER", 20);
	}
	if (S.modifiable == 1) {
		afficher_message("A VOUS DE JOUER PUIS SOUVEGARDER", 8);
	}
	affiche_all();
}
