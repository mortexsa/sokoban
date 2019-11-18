// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier historique.h du jeu sokoban
#ifndef ___HISTORIQUE_H
#define ___HISTORIQUE_H
#include "sokoban.h"

typedef struct PileElement{
	SOKOBAN valeur;
	struct PileElement *suivant;
} PileElement, *Pile;
//crée une nouvelle pile
Pile nouvelle_pile();
//tester si la pile est vide 
int est_pile_vide(Pile P);
//inserer un element sur la pile
Pile inserer_pile(Pile P,SOKOBAN S);
//retirer l'element qui se trouve sur le sommet de la pile
Pile retirer_pile(Pile P);
//returne la valeur de la tete de liste 
SOKOBAN valeur_sommet_pile(Pile P);
//longueur de la pile 
int longueur_pile(Pile P);

void vider_les_piles();

Pile P;
Pile P2;

#endif