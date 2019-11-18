// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier creation.h du jeu SOKOBAN
#ifndef ___CREATION_H
#define ___CREATION_H
#include "constantes.h"
#include <uvsqgraphics.h>
#include "sokoban.h"
#include "historique.h"




int verifier_un_perso(SOKOBAN S);
int modifier_case(SOKOBAN S,int x,int y);
int verifier_murs_fermer(SOKOBAN S, int x,int y);
int verifier_caisse(SOKOBAN S);
SOKOBAN coordonner_personnage(SOKOBAN S);
SOKOBAN changer_apparance_case(SOKOBAN S, int x, int y);
SOKOBAN activer_mode_joueur(SOKOBAN S);
SOKOBAN modifier_map_trois_position_creation(SOKOBAN S,char position,char position_suivante,char position_precedente,int x,int y);
SOKOBAN touche_directionnel_creation(SOKOBAN S, int x,int y);
SOKOBAN jouer_creation(SOKOBAN S);
SOKOBAN deplacement_fleche_creation(SOKOBAN S,int fleche);
SOKOBAN clic_touche_creation(SOKOBAN S,char touche);
SOKOBAN clic_souris_creation(SOKOBAN S,POINT clic);
SOKOBAN action_creation(SOKOBAN S);


#endif
