// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier historique.c du jeu SOKOBAN
#include "historique.h"

//crée une nouvelle pile 
Pile nouvelle_pile()
{
	return NULL;
}

//tester si la pile est vide 
int est_pile_vide(Pile P)
{
	if (P == NULL) {
		return 1;
	} else {
		return 0;
	}
}

//inserer un element sur la pile
Pile inserer_pile(Pile P, SOKOBAN S)
{
	PileElement *element;
	element = (Pile) malloc(sizeof(PileElement));
	if (element == NULL) {
		puts("Probleme allocation de memoire.\n");
		exit(EXIT_FAILURE);
	}
	element->valeur = S;
	element->suivant = P;
	return element;
}

//retirer l'element qui se trouve sur le sommet de la pile
Pile retirer_pile(Pile P)
{
	PileElement *element;
	if (est_pile_vide(P)) {
		puts("La pile est vide.\n");
		return NULL;
	}
	element = P->suivant;
	free(P);
	return element;
}

//returne la valeur de la tete de liste 
SOKOBAN valeur_sommet_pile(Pile P)
{
	return P->valeur;
}

//longueur de la pile 
int longueur_pile(Pile P)
{
	int longueur = 0;
	while (P != NULL) {
		++longueur;
		P = P->suivant;
	}
	return longueur;
}

//vider les deux piles utiliser pour l'historique
void vider_les_piles()
{
	while (!est_pile_vide(P)) {
		P = retirer_pile(P);
	}
	while (!est_pile_vide(P2)) {
		P2 = retirer_pile(P2);
	}
}
