// constantes.h du projet SOKOBAN
// slimani-arezki@hotmail.com
// decembre 2016


#ifndef ___CONSTANTES_H
#define ___CONSTANTES_H

// La taille du sokoban
#define NXCASE 32
#define NYCASE 22 
#define TAILLE_MAX 256

// La taile et couleur de l'écriture 
#define TAILLE_POLICE 20
#define COUL_POLICE vert
#define COUL_FOND marron
// La valeur pour une case 
#define VIDE 0

// Constantes liées à l'affichage 
#define TAILLE_CASE 30
#define LONG_BOUTON ((NXCASE*TAILLE_CASE)/6)
#define HAUT_BOUTON (TAILLE_POLICE*2)
#define LONG_FENETRE (NXCASE*TAILLE_CASE)
#define HAUT_FENETRE (NYCASE*TAILLE_CASE + HAUT_BOUTON) 

// constantes liées a la lecture du ficher
#define MUR '#'
#define CAISSE '$'
#define RUC '.' //objectif
#define PERSONNAGE '@'
#define CAISSE_RUC '*' //caisse sur objectif
#define PERSONNAGE_RUC '+' //personnage sur objectif
#define ESPACE ' '
//différentes touches
#define INIT 73
#define JOUER 74
#define PRECEDENT 80
#define QUITTER 81
#define REDO 82
#define SUIVANT 83
#define SAVE 83
#define UNDO 85
// Autre constantes
#define POINT_VIRGULE ';'
#define RETOUR_LIGNE '\n'

// les différentes couleurs
#define COUL_VIDE black
#define COUL_MUR blanc
#define COUL_CAISSE jaune
#define COUL_RUC rouge
#define COUL_PERSONNAGE magenta
#define COUL_CAISSE_RUC bleu
#define COUL_PERSONNAGE_RUC vert

#endif
