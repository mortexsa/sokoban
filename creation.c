// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier creation.c du jeu SOKOBAN
#include "creation.h"
#include "sokoban.h"
#include "action.h"
#include "lire_ecrire.h"
#include "historique.h"

/*
* Vérifier qu'il a qu'un seul personnage sur la map
*/
int verifier_un_perso(SOKOBAN S)
{
	int compteur = 0;
	int x, y;
	for (y = VIDE; y < NYCASE; y++) {
		for (x = VIDE; x < NXCASE; x++) {
			if (S.la_case[x][y].val == PERSONNAGE) {
				compteur++;
			}
		}
	}
	return compteur;
}

/*
* Modifier la valeur de la case
*/
int modifier_case(SOKOBAN S, int x, int y)
{
	if (S.modifiable == VIDE) {
		return (S.la_case[x][y].nbrclic + 1) % 4;
	}
	return S.la_case[x][y].nbrclic;
}

/*
* Vérifier si les murs du niveau sont bien fermer
*/
int verifier_murs_fermer(SOKOBAN S, int x, int y)
{
	if (S.la_case[x][y].val == MUR) {
		return 1;
	}
	if ((x == 0) || (x == NXCASE - 1)) {
		return 0;
	}
	if ((y == 2) || (y == NYCASE - 1)) {
		return 0;
	}
	S.la_case[x][y].val = MUR;
	return ((verifier_murs_fermer(S, x - 1, y))
		&& (verifier_murs_fermer(S, x + 1, y))
		&& (verifier_murs_fermer(S, x, y - 1))
		&& (verifier_murs_fermer(S, x, y + 1)));
}

/*
* Vérifier qu'il y'a au moins une caisse sur la map
*/
int verifier_caisse(SOKOBAN S)
{
	int x;
	int y;
	for (y = 2; y < NYCASE - 1; y++) {
		for (x = VIDE; x < NXCASE - 1; x++) {
			if (S.la_case[x][y].val == CAISSE_RUC) {
				return 1;
			}
		}
	}
	return 0;
}

/*
* Affiche un carré non remplie blanc
*/
SOKOBAN coordonner_personnage(SOKOBAN S)
{
	int x;
	int y;
	for (y = 2; y < NYCASE - 1; y++) {
		for (x = VIDE; x < NXCASE - 1; x++) {
			if (S.la_case[x][y].val == PERSONNAGE) {
				S.personnage.x = x;
				S.personnage.y = y;
				return S;
			}
			if (S.la_case[x][y].val == PERSONNAGE_RUC) {
				S.personnage.x = x;
				S.personnage.y = y;
				return S;
			}
		}
	}
	return S;
}
/*
* Change le contenu de la case qui changera son apparance
*/
SOKOBAN changer_apparance_case(SOKOBAN S, int x, int y)
{
	S.la_case[x][y].nbrclic = modifier_case(S, x, y);
	if (S.la_case[x][y].nbrclic == 0) {
		S.la_case[x][y].val = ESPACE;
		return S;
	}
	if (S.la_case[x][y].nbrclic == 1) {
		S.la_case[x][y].val = MUR;
		return S;
	}
	if (S.la_case[x][y].nbrclic == 2) {
		S.la_case[x][y].val = CAISSE_RUC;
		return S;
	}
	if (S.la_case[x][y].nbrclic == 3) {
		S.la_case[x][y].val = PERSONNAGE;
		return S;
	}
	return S;
}

/*
* Passer en mode joueur pour faire jouer l'utilisateur a l'envers(on ne peut plus changer la map)
*/
SOKOBAN activer_mode_joueur(SOKOBAN S)
{
	S.modifiable = 1;
	return S;
}

/*
* Modifier La map en fesont des changement sur trois coordonner de la map
* @param S La structure qui enregistre les donner du niveau
* @param position La position actuel du personnage
* @param position_suivante La position ou on veut bouger le personnage
* @param position_suivante_2 La position ou on veut bouger la caisse
* @param x La coordonner des abscisse du personnage
* @param y La coordonner des ordonner du personnage
* @return Les nouvelles coordonner du personnage en changeant la map
*/
SOKOBAN modifier_map_trois_position_creation(SOKOBAN S, char position, char position_suivante, char position_precedente, int x, int y)
{
	S.la_case[S.personnage.x][S.personnage.y].val = position;
	S.la_case[S.personnage.x + x][S.personnage.y + y].val = position_suivante;
	S.la_case[S.personnage.x - x][S.personnage.y - y].val = position_precedente;
	S.personnage.x += x;
	S.personnage.y += y;
	P = inserer_pile(P, S);
	while (!est_pile_vide(P2)) {
		P2 = retirer_pile(P2);
	}
	return S;
}

/*
* Modifier La map en fonction de la direction ou on veut bouger le personnage
* @param S La structure qui enregistre les donner du niveau
* @param x La coordonner des abscisse du personnage
* @param y La coordonner des ordonner du personnage
* @return Les nouvelles coordonner du personnage en changeant la map
*/
SOKOBAN touche_directionnel_creation(SOKOBAN S, int x, int y)
{
	if (S.la_case[S.personnage.x + x][S.personnage.y + y].val != MUR) {
		if (S.la_case[S.personnage.x][S.personnage.y].val == PERSONNAGE) {
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == ESPACE) {
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE) {
					S = modifier_map_trois_position_creation(S, CAISSE, PERSONNAGE, ESPACE, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE_RUC) {
					S = modifier_map_trois_position_creation(S, CAISSE, PERSONNAGE, RUC, x, y);
					return S;
				} else {
					S = modifier_map_deux_position(S, ESPACE, PERSONNAGE, x, y);
					return S;
				}
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == RUC) {
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE) {
					S = modifier_map_trois_position_creation(S, CAISSE, PERSONNAGE_RUC, ESPACE, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE_RUC) {
					S = modifier_map_trois_position_creation(S, CAISSE, PERSONNAGE_RUC, RUC, x, y);
					return S;
				} else {
					S = modifier_map_deux_position(S, ESPACE, PERSONNAGE_RUC, x, y);
					return S;
				}
			}
		}
		if (S.la_case[S.personnage.x][S.personnage.y].val == PERSONNAGE_RUC) {
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == ESPACE) {
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE) {	//si case precedente est une caisse
					S = modifier_map_trois_position_creation(S, CAISSE_RUC, PERSONNAGE, ESPACE, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE_RUC) {	//si case precedente est une caisse sur objectif
					S = modifier_map_trois_position_creation(S, CAISSE_RUC, PERSONNAGE, RUC, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == RUC) {	//si case precedente est un objectif
					S = modifier_map_trois_position_creation(S, RUC, PERSONNAGE, RUC, x, y);
					return S;
				} else {
					S = modifier_map_deux_position(S, RUC, PERSONNAGE, x, y);
					return S;
				}
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == RUC) {
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE) {	//si case precedente est une caisse
					S = modifier_map_trois_position_creation(S, CAISSE_RUC, PERSONNAGE_RUC, ESPACE, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == CAISSE_RUC) {	//si case precedente est une caisse sur objectif
					S = modifier_map_trois_position_creation(S, CAISSE_RUC, PERSONNAGE_RUC, RUC, x, y);
					return S;
				}
				if (S.la_case[S.personnage.x - x][S.personnage.y - y].val == RUC) {	//si case precedente est un objectif
					S = modifier_map_trois_position_creation(S, RUC, PERSONNAGE_RUC, RUC, x, y);
					return S;
				} else {
					S = modifier_map_deux_position(S, RUC, PERSONNAGE_RUC, x, y);
					return S;
				}
			}
		}
	}
	return S;
}

/*
* Gere le mode joueur pour faire jouer a l'envers l'utilisateur
*/
SOKOBAN jouer_creation(SOKOBAN S)
{
	S.personnage.x = 0;
	S.personnage.y = 0;
	if (verifier_un_perso(S) == 1) {
		if (verifier_caisse(S)) {
			S = coordonner_personnage(S);
			if (verifier_murs_fermer
			    (S, S.personnage.x, S.personnage.y)) {
				S = activer_mode_joueur(S);
				P = inserer_pile(P, S);
			}
		}
	}
	return S;
}

/*
* Déplace le personnage avec les fleches du clavier
*/
SOKOBAN deplacement_fleche_creation(SOKOBAN S, int fleche)
{
	int x = 0;
	int y = 0;
	if (fleche == FLECHE_GAUCHE) {
		x = (-1);
		y = 0;
		S = touche_directionnel_creation(S, x, y);
		return S;
	}
	if (fleche == FLECHE_DROITE) {
		x = 1;
		y = 0;
		S = touche_directionnel_creation(S, x, y);
		return S;
	}
	if (fleche == FLECHE_BAS) {
		x = 0;
		y = 1;
		S = touche_directionnel_creation(S, x, y);
		return S;
	}
	if (fleche == FLECHE_HAUTE) {
		x = 0;
		y = (-1);
		S = touche_directionnel_creation(S, x, y);
		return S;
	}
	return S;
}

/*
* Gere les differentes fonctionnalitées qu'on peut éxécuté avec les touches du clavier
*/
SOKOBAN clic_touche_creation(SOKOBAN S, char touche)
{
	if (touche == INIT) {
		S = initialiser_sokoban_creation();
		vider_les_piles();
		return S;
	}			//INIT
	if (touche == JOUER) {
		S = jouer_creation(S);
		return S;
	}			//JOUER
	if (touche == UNDO) {
		if (S.modifiable == 1) {
			S = undo(S);
			return S;
		}
		return S;
	}			//UNDO
	if (touche == REDO) {
		if (S.modifiable == 1) {
			S = redo(S);
			return S;
		}
		return S;
	}			//REDO
	if (touche == SAVE) {
		ecrire_niveau(S);
		vider_les_piles();
		P = inserer_pile(P, S);
		return S;
	}			//SAVE
	if (touche == QUITTER) {
		vider_les_piles();
		exit(0);
	}			//QUIT
	return S;
}

/*
* Gere les differentes fonctionnalitées qu'on peut éxécuté avec les clics de la souris
*/
SOKOBAN clic_souris_creation(SOKOBAN S, POINT clic)
{
	int x = 0;
	int y = 0;
	if (clic.y < HAUT_BOUTON) {
		if (clic.x > LONG_BOUTON * 0 && clic.x < LONG_BOUTON * 1) {
			S = initialiser_sokoban_creation();
			vider_les_piles();
			return S;
		}		//INIT
		if (clic.x > LONG_BOUTON * 1 && clic.x < LONG_BOUTON * 2) {
			S = jouer_creation(S);
			return S;
		}		//JOUER
		if (clic.x > LONG_BOUTON * 2 && clic.x < LONG_BOUTON * 3) {
			if (S.modifiable == 1) {
				S = undo(S);
				return S;
			}
			return S;
		}		//UNDO
		if (clic.x > LONG_BOUTON * 3 && clic.x < LONG_BOUTON * 4) {
			if (S.modifiable == 1) {
				S = redo(S);
				return S;
			}
			return S;
		}		//REDO
		if (clic.x > LONG_BOUTON * 4 && clic.x < LONG_BOUTON * 5) {
			ecrire_niveau(S);
			vider_les_piles();
			P = inserer_pile(P, S);
			return S;
		}		//SAVE
		if (clic.x > LONG_BOUTON * 5 && clic.x < LONG_BOUTON * 6) {
			vider_les_piles();
			exit(0);
		}		//QUIT
	}
	if (clic.y > HAUT_BOUTON + TAILLE_CASE && clic.y < HAUT_FENETRE - 2 * TAILLE_CASE && clic.x < LONG_FENETRE - TAILLE_CASE) {
		x = clic.x / TAILLE_CASE;
		y = (HAUT_FENETRE - clic.y) / TAILLE_CASE;
		S = changer_apparance_case(S, x, y);
		return S;
	}
	return S;
}

/*
* Gere tout les clics et touches éxécuté
*/
SOKOBAN action_creation(SOKOBAN S)
{
	char touche = { 0 };
	int fleche;
	POINT clic;
	clic.x = 0;
	clic.y = 0;
	int action = 0;
	action = wait_key_arrow_clic(&touche, &fleche, &clic);
	if (action == 1) {
		S = deplacement_fleche_creation(S, fleche);
		attendre(120);
		return S;
	}
	if (action == 2) {
		S = clic_touche_creation(S, touche);
		return S;
	}
	if (action == 3) {
		S = clic_souris_creation(S, clic);
		return S;
	}
	return S;
}
