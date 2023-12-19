#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#include <stdbool.h>
#include "SDL.h"

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 34
#define X 0
#define Y 1

// ================================================
// Definition des types
// ================================================
typedef enum{tourSol, tourAir, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;

// ================================================
typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de gérer le fait que chaque unité attaque une
                            //seule fois par tour ;
                            //0 = a déjà attaqué, 1 = peut attaquer ce tour-ci
                            // à remettre à 1 au début de chaque tour

    //struct Tunite *cible;   //NULL si pas de cible. mettre à jour ce pointeur permet l'aninamtion (simpliste certe) du tir
    //non utilisé au final -> utiliser directement dessineAttaque
} Tunite;


// ================================================
typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unité
} *TListePlayer;

// ================================================
typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)


// ================================================
// Fonctions de base du projet
// ================================================
TplateauJeu AlloueTab2D(int largeur, int hauteur);
void afficheCoordonneesParcours(int **t, int nbcoord);
int **initChemin();         //retourne le chemin emprunter par la horde, sous forme d'un tableau[NBCOORDPARCOURS][2]
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

// ================================================
// Creation des unites
// ================================================
Tunite *creeTourSol(int posx, int posy);
Tunite *creeTourAir(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeUniteAleatoire(int posx, int posy);

// ================================================
// Fonctions de positionnement
// ================================================
void positionneTour(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2, int **chemin);
void positionneUniteHorde(TListePlayer *l2);
void positionnePlayerOnPlateau(TListePlayer *l, TplateauJeu jeu);
void generationUniteAleatoire(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2, int **chemin, int tauxHorde, int tauxRoi);

// ================================================
// Fonctions de comparaison
// ================================================
bool fcompPosY(Tunite *unite1, Tunite *unite2);
bool fcompPV(Tunite *unite1, Tunite *unite2);

// ================================================
// Fonctions d'avancement des unites
// ================================================
int findOuSurChemin(Tunite *uniteDemandee, int**chemin);
bool isOnChemin(int x, int y, int **chemin);
bool isInSamePosition(TListePlayer *l, int x1, int y1);
void avanceUnite(TListePlayer *l2, int**chemin);

// ================================================
// Fonctions de combat
// ================================================
void quiEstAPortee(TListePlayer *l2, TListePlayer *lcible, Tunite *ptrUnite);
void combatHorde(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2);
void combatTour(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2);

// ================================================
// Fonctions de verification de mort/jeu
// ================================================
void supprimerUnite(TListePlayer *l2);
bool isRoiVivant(TListePlayer *l1);
bool isTourDeJeuInfA250(int nbTourDeJeu);

// ================================================
// Affichages
// ================================================
void afficheUnite(Tunite *uniteAffichee);
void affichageRoiMort(bool isRoiVivant);

#endif // TOWERDEFEND_H_INCLUDED
