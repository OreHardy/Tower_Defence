#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>

// ================================================
//  Fonction d'initialisation
// ================================================
void initListePlayer(TListePlayer *l);
bool isListePlayerVide(TListePlayer *l);

void cleanListePlayer(TListePlayer *l);

// ================================================
//  Fonctions d'ajout
// ================================================
void ajoutTeteListePlayer(TListePlayer *l, Tunite *mydata);
void ajoutEn2ListePlayer(TListePlayer *l, Tunite *mydata);

// ================================================
//  Fonctions de suppression
// ================================================
void supprTeteListePlayer(TListePlayer *l);
void supprUniteListePlayer(TListePlayer *l, Tunite *ptrUnite);

// ================================================
//  Affichage
// ================================================
void afficheListePlayer(TListePlayer *l);

// ================================================
//  Fonction sur les cellules du TListePlayer
// ================================================
TListePlayer getptrFirstCell(TListePlayer *l);
TListePlayer getptrNextCell(TListePlayer *l);
TListePlayer getptrLastCell(TListePlayer *l);
Tunite* getPtrData(TListePlayer *l);
void swapPtrData(TListePlayer *source, TListePlayer *destination);

// ================================================
//  Fonctions de comptage
// ================================================
int getNbreUnite(TListePlayer *l);
int getSizeBytes(TListePlayer *l);

// ================================================
//  Fonctions de tri
// ================================================
void tri_selection(TListePlayer *l, bool (fcomp)(Tunite *, Tunite *));


#endif // LISTEDOUBLE_H_INCLUDED

