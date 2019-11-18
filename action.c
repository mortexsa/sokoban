// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier action.c du jeu SOKOBAN
#include "action.h"
#include "sokoban.h"
#include "historique.h"

/*
* Passe au niveau précédant
*/
SOKOBAN niveau_precedent(SOKOBAN S)
{
	if (lvl > 1) {
		vider_les_piles();//vide l'historique
		lvl--;
		S = lire_niveau();
		P = inserer_pile(P, S);
		return S;
	}
	return S;
}

/*
* Passe au niveau suivant
*/
SOKOBAN niveau_suivant(SOKOBAN S)
{
	if (lvl < 50) {
		vider_les_piles();
		lvl++;
		S = lire_niveau();
		P = inserer_pile(P, S);
		return S;
	}
	return S;
}

/*
* reinitialise le niveau sans suprimer l'historique
*/
SOKOBAN init_partie(SOKOBAN S)
{
	while (longueur_pile(P) > 1) {//tant que la pile principal contient plus d'un élement
		P2 = inserer_pile(P2, valeur_sommet_pile(P));
		P = retirer_pile(P);
	}
	S = valeur_sommet_pile(P);
	return S;
}

/*
* Recule dans l'historique de jeu
*/
SOKOBAN undo(SOKOBAN S)
{
	if (longueur_pile(P) > 1) {
		P2 = inserer_pile(P2, valeur_sommet_pile(P));
		P = retirer_pile(P);
		S = valeur_sommet_pile(P);
		return S;
	}
	return S;
}

/*
* Avance dans l'historique de jeu
*/
SOKOBAN redo(SOKOBAN S)
{
	if (!est_pile_vide(P2)) {
		P = inserer_pile(P, valeur_sommet_pile(P2));
		P2 = retirer_pile(P2);
		S = valeur_sommet_pile(P);
		return S;
	}
	return S;
}

/*
* Passe au niveau suivant(si possible) si le niveau est compléter(aucune caisse non rangé)
*/
SOKOBAN niveau_terminer(SOKOBAN S)
{
	int compteur_caisse = 0;
	int compteur_virgule = 0;
	int x, y;
	for (y = VIDE; y < NYCASE; y++) {
		for (x = VIDE; x < NXCASE; x++) {
			if (S.la_case[x][y].val == CAISSE) {
				compteur_caisse++;
			}
			if (S.la_case[x][y].val == POINT_VIRGULE) {
				compteur_virgule++;
			}
		}
	}
	if (compteur_caisse == 0 && compteur_virgule == 1) {//si il y'a un niveau suivant
		S = niveau_suivant(S);
		return S;
	}
	if (compteur_caisse == 0 && compteur_virgule == 0) {//si il n'ya pas de niveau suivant
		vider_les_piles(); // on libére la mémoire
		exit(0);
	}
	return S;
}

/*
* Modifier La map en fesont des changement sur deux coordonner de la map
* @param S La structure qui enregistre les donner du niveau
* @param position La position actuel du personnage
* @param position_suivante La position ou on veut bouger le personnage
* @param x La coordonner des abscisse du personnage
* @param y La coordonner des ordonner du personnage
* @return Les nouvelles coordonner du personnage en changeant la map
*/
SOKOBAN modifier_map_deux_position(SOKOBAN S,char position,char position_suivante,int x,int y){
	S.la_case[S.personnage.x][S.personnage.y].val = position;//position actuel du perso
	S.la_case[S.personnage.x + x][S.personnage.y + y].val = position_suivante;//position ou on veut le bouger
	S.personnage.x += x;
	S.personnage.y += y;
	S.coupsjouer++;
	P = inserer_pile(P, S);
	while (!est_pile_vide(P2)) {//on vide la deuxieme pile 
		P2 = retirer_pile(P2);
	}
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
SOKOBAN modifier_map_trois_position(SOKOBAN S,char position,char position_suivante,char position_suivante_2,int x,int y){
	S.la_case[S.personnage.x][S.personnage.y].val = position; 
	S.la_case[S.personnage.x + x][S.personnage.y + y].val = position_suivante;
	S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val = position_suivante_2;
	S.personnage.x += x;
	S.personnage.y += y;
	S.coupsjouer++;
	P = inserer_pile(P, S);
	while (!est_pile_vide(P2)) {
		P2 = retirer_pile(P2);
	}
	return S;
}

/*
* Modifier La map en fonction de la direction ou on veut bouger le personnage
*/
SOKOBAN touche_directionnel(SOKOBAN S, int x, int y)
{
	if (S.la_case[S.personnage.x + x][S.personnage.y + y].val != MUR) {
		if (S.la_case[S.personnage.x][S.personnage.y].val == PERSONNAGE) {
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == ESPACE) {
				S = modifier_map_deux_position(S,ESPACE,PERSONNAGE,x,y);
				return S;
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y +y].val == RUC) {
				S = modifier_map_deux_position(S,ESPACE,PERSONNAGE_RUC,x,y);
				return S;
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == CAISSE) {
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == ESPACE) {
					S = modifier_map_trois_position(S,ESPACE,PERSONNAGE,CAISSE,x,y);
					return S;
				}
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == RUC) {
					S = modifier_map_trois_position(S,ESPACE,PERSONNAGE,CAISSE_RUC,x,y);
					return S;
				}
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == CAISSE_RUC) {
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == ESPACE) {
					S = modifier_map_trois_position(S,ESPACE,PERSONNAGE_RUC,CAISSE,x,y);
					return S;
				}
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == RUC) {
					S = modifier_map_trois_position(S,ESPACE,PERSONNAGE_RUC,CAISSE_RUC,x,y);
					return S;
				}
			}
		}
		if (S.la_case[S.personnage.x][S.personnage.y].val == PERSONNAGE_RUC) {
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == ESPACE) {
				S = modifier_map_deux_position(S,RUC,PERSONNAGE,x,y);
				return S;
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == RUC) {
				S = modifier_map_deux_position(S,RUC,PERSONNAGE_RUC,x,y);
				return S;
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == CAISSE) {
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == ESPACE) {
					S = modifier_map_trois_position(S,RUC,PERSONNAGE,CAISSE,x,y);
					return S;
				}
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == RUC) {
					S = modifier_map_trois_position(S,RUC,PERSONNAGE,CAISSE_RUC,x,y);
					return S;
				}
			}
			if (S.la_case[S.personnage.x + x][S.personnage.y + y].val == CAISSE_RUC) {
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == ESPACE) {
					S = modifier_map_trois_position(S,RUC,PERSONNAGE_RUC,CAISSE,x,y);
					return S;
				}
				if (S.la_case[S.personnage.x + (x * 2)][S.personnage.y + (y * 2)].val == RUC) {
					S = modifier_map_trois_position(S,RUC,PERSONNAGE_RUC,CAISSE_RUC,x,y);
					return S;
				}
			}
		}
	}
	return S;
}

/*
* Déplace le personnage avec les fleches du clavier
*/
SOKOBAN deplacement_fleche(SOKOBAN S, int fleche)
{
	int x = 0;
	int y = 0;
	if (fleche == FLECHE_GAUCHE) {
		x = (-1);
		y = 0;
		S = touche_directionnel(S, x, y);
		return S;
	}
	if (fleche == FLECHE_DROITE) {
		x = 1;
		y = 0;
		S = touche_directionnel(S, x, y);
		return S;
	}
	if (fleche == FLECHE_BAS) {
		x = 0;
		y = 1;
		S = touche_directionnel(S, x, y);
		return S;
	}
	if (fleche == FLECHE_HAUTE) {
		x = 0;
		y = (-1);
		S = touche_directionnel(S, x, y);
		return S;
	}
	return S;
}

/*
* Gere les differentes fonctionnalitées qu'on peut éxécuté avec les touches du clavier
*/
SOKOBAN appuis_touche(SOKOBAN S, char touche)
{
	if (touche == UNDO) {
		S = undo(S);
		return S;
	}
	if (touche == REDO) {
		S = redo(S);
		return S;
	}
	if (touche == INIT) {
		S = init_partie(S);
		return S;
	}
	if (touche == PRECEDENT) {
		S = niveau_precedent(S);
		return S;
	}
	if (touche == SUIVANT) {
		S = niveau_suivant(S);
		return S;
	}
	if (touche == QUITTER) {
		vider_les_piles();
		exit(0);
	}
	return S;
}

/*
* Gere les differentes fonctionnalitées qu'on peut éxécuté avec les clics de la souris
*/
SOKOBAN clic_souris(SOKOBAN S, POINT clic)
{
	int x = 0;
	int y = 0;
	if (clic.y < HAUT_BOUTON) {
		if (clic.x > LONG_BOUTON * 0 && clic.x < LONG_BOUTON * 1) {
			S = undo(S);
			return S;
		}		//UNDO
		if (clic.x > LONG_BOUTON * 1 && clic.x < LONG_BOUTON * 2) {
			S = redo(S);
			return S;
		}		//REDO
		if (clic.x > LONG_BOUTON * 2 && clic.x < LONG_BOUTON * 3) {
			S = init_partie(S);
			return S;
		}		//INIT
		if (clic.x > LONG_BOUTON * 3 && clic.x < LONG_BOUTON * 4) {
			S = niveau_precedent(S);
			return S;
		}		//PRECEDENT
		if (clic.x > LONG_BOUTON * 4 && clic.x < LONG_BOUTON * 5) {
			S = niveau_suivant(S);
			return S;
		}		//SUIVANT
		if (clic.x > LONG_BOUTON * 5 && clic.x < LONG_BOUTON * 6) {
			vider_les_piles();
			exit(0);
		}		//QUITTER
	} else {
		 /*G*/ if ((clic.x / TAILLE_CASE == S.personnage.x - 1)
			   && (HAUT_FENETRE - clic.y) / TAILLE_CASE == S.personnage.y) {
			x = (-1);
			y = 0;
			S = touche_directionnel(S, x, y);
			return S;
		}
		/*D*/ if ((clic.x / TAILLE_CASE == S.personnage.x + 1) && (HAUT_FENETRE - clic.y) / TAILLE_CASE == S.personnage.y) {
			x = 1;
			y = 0;
			S = touche_directionnel(S, x, y);
			return S;
		}
		/*B*/ if ((clic.x / TAILLE_CASE == S.personnage.x) && (HAUT_FENETRE - clic.y) / TAILLE_CASE == S.personnage.y + 1) {
			x = 0;
			y = 1;
			S = touche_directionnel(S, x, y);
			return S;
		}
		/*H*/ if ((clic.x / TAILLE_CASE == S.personnage.x) && (HAUT_FENETRE - clic.y) / TAILLE_CASE == S.personnage.y - 1) {
			x = 0;
			y = (-1);
			S = touche_directionnel(S, x, y);
			return S;
		}
	}
	return S;
}

/*
* Gere tout les clics et touches éxécuté
*/
SOKOBAN bouger_personnage(SOKOBAN S)
{
	char touche = { 0 };
	int fleche;
	POINT clic;
	clic.x = 0;
	clic.y = 0;
	int action = 0;
	action = wait_key_arrow_clic(&touche, &fleche, &clic);
	if (action == 1) {
		S = deplacement_fleche(S, fleche);
		attendre(120);
		S = niveau_terminer(S);
		return S;
	}
	if (action == 2) {
		S = appuis_touche(S, touche);
		return S;
	}
	if (action == 3) {
		S = clic_souris(S, clic);
		S = niveau_terminer(S);
		return S;
	}
	return S;
}
