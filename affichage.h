// Nom : Slimani 
// Prénom : Arezki
// n° étudiant : 21502933

//Fichier affichage.h du jeu SOKOBAN
#include "sokoban.h"
#include <uvsqgraphics.h>
#include "constantes.h"
#include "lire_ecrire.h"

void initialiser_affichage();
void numero_niveau(SOKOBAN S);
void coups_jouer(SOKOBAN S);
void nom_fichier(char *texte);
void afficher_message(char *text,int x);
void afficher_un_bouton(int numero, char *texte);
void afficher_les_boutons();
void afficher_carre_vide(int x, int y);
void afficher_carre(int x,int y,COULEUR c);
void afficher_ruc(int x,int y,COULEUR c);
void afficher_personnage(int x,int y,COULEUR c);
void afficher_case(SOKOBAN S,int x,int y);
void afficher_niveau(SOKOBAN S);
void afficher_case_creation(SOKOBAN S,int x,int y);
void boutons_creation();
void afficher_creation(SOKOBAN S);

