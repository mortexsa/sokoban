// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier action.h du jeu SOKOBAN
#ifndef ___ACTION_H
#define ___ACTION_H
#include "lire_ecrire.h"


/*-------------------------------------------------*/

SOKOBAN niveau_precedent(SOKOBAN S);
SOKOBAN niveau_suivant(SOKOBAN S);
SOKOBAN init_partie(SOKOBAN S);
SOKOBAN undo(SOKOBAN S);
SOKOBAN redo(SOKOBAN S);
SOKOBAN niveau_terminer(SOKOBAN S);
//fonction qui sert a deplacer le personnage
SOKOBAN modifier_map_deux_position(SOKOBAN S,char position,char position_suivante,int x,int y);
SOKOBAN modifier_map_trois_position(SOKOBAN S,char position,char position_suivante,char position_suivante_2,int x,int y);
SOKOBAN touche_directionnel(SOKOBAN S, int x,int y);
SOKOBAN deplacement_fleche(SOKOBAN S,int fleche);
SOKOBAN appuis_touche(SOKOBAN S,char touche);
SOKOBAN clic_souris(SOKOBAN S,POINT clic);
SOKOBAN bouger_personnage(SOKOBAN S);

#endif
