#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "towerdefend.h"
#include "listePlayer.h"


// ================================================
void initListePlayer(TListePlayer *l)
{
    *l=NULL;
}

// ================================================
bool isListePlayerVide(TListePlayer *l)
{
    return (*l==NULL);
}

// ================================================
void cleanListePlayer(TListePlayer *l){
    while (!isListePlayerVide(l)){
        supprTeteListePlayer(l);
    }
}

// ================================================
void ajoutTeteListePlayer(TListePlayer *l, Tunite *mydata)
{
    TListePlayer cell=(TListePlayer)malloc(sizeof(struct T_cell));
    cell->pdata = mydata;
    cell->suiv=(*l);
    *l=cell;
}

// ================================================
void ajoutEn2ListePlayer(TListePlayer *l, Tunite *mydata)
{
    TListePlayer cell = (TListePlayer)malloc(sizeof(struct T_cell));
    cell->pdata=mydata;
    cell->suiv=(*l)->suiv;
    (*l)->suiv=cell;
}

// ================================================
void supprTeteListePlayer(TListePlayer *l)
{
    if(*l!=NULL){
        TListePlayer tmp = (*l);
        *l=(*l)->suiv;
        free(tmp->pdata);
        free(tmp);
    }
}

// ================================================
void supprUniteListePlayer(TListePlayer *l, Tunite *ptrUnite){
    struct T_cell *tmp=*l;
    struct T_cell *tmp2;

    if(tmp->pdata==ptrUnite) {
        *l=(*l)->suiv;
    } else {
        while(tmp->suiv->pdata != ptrUnite) {
            tmp=tmp->suiv;
        }
        tmp2=tmp->suiv->suiv;
        free(tmp->suiv->pdata);
        free(tmp->suiv);
        tmp->suiv=tmp2;
    }
}

// ================================================
void afficheListePlayer(TListePlayer *l){
    int cmpt = 0;
    struct T_cell *tmp=*l;
    printf("---- Unites du joueur ---- \n");
    if (isListePlayerVide(l)) printf("Il n'y a pas d'unites ! \n");
    while(tmp!=NULL) {
        printf("%d  : ", cmpt);
        afficheUnite(tmp->pdata);
        cmpt++;
        tmp=tmp->suiv;
    }
    printf("\n\n");
}

// ================================================
TListePlayer getptrFirstCell(TListePlayer *l){
    return *l ;
}

// ================================================
TListePlayer getptrNextCell(TListePlayer *l){
    return (*l)->suiv ;
}

// ================================================
TListePlayer getptrLastCell(TListePlayer *l){
    TListePlayer courant = *l;

    if (isListePlayerVide(&courant)) {
        printf("Erreur getptrLastCell liste vide");
    }
    else {
        while(courant->suiv != NULL){
            courant=courant->suiv;
        }
    }
    return courant;
}

// ================================================
Tunite* getPtrData(TListePlayer *l){
    return (*l)->pdata ;
}

// ================================================
void swapPtrData(TListePlayer *source, TListePlayer *destination){
    Tunite* tmp = (*source)->pdata;
    (*source)->pdata = (*destination)->pdata;
    (*destination)->pdata = tmp;
}

// ================================================
int getNbreUnite(TListePlayer *l){
    TListePlayer tmp = *l;
    int compteur = 0 ;
    while(!(isListePlayerVide(&tmp))){
        tmp = tmp->suiv ;
        compteur = compteur+1 ;
    }
    return compteur ;
}

// ================================================
int getSizeBytes(TListePlayer *l){
    int nbr_cell = getNbreUnite(l);
    return sizeof(TListePlayer) * nbr_cell;
}

// ================================================
void tri_selection(TListePlayer *l, bool (*fcomp)(Tunite *, Tunite *)){
    TListePlayer en_cours, plus_petit, j;
    if (!isListePlayerVide(l)){
        for (en_cours = (*l); en_cours!=NULL; en_cours=getptrNextCell(&en_cours))  //on n'utilise plus un pointeur sur la fin, on regarde seulement si c'est NULL
        {
            plus_petit = en_cours;
            for (j = getptrNextCell(&en_cours) ; j != NULL; j=getptrNextCell(&j))
            {
                if (fcomp(getPtrData(&plus_petit),getPtrData(&j)))
                    plus_petit = j;
            }

            if(en_cours != plus_petit) swapPtrData(&en_cours, &plus_petit);
        }
    }
}
/*
// ================================================
void tri_selection_ETAPE3_YD(TListePlayer *l, bool (*fcomp)(Tunite *, Tunite *)){
    TListePlayer en_cours, plus_petit, j, fin;  //pointeurs sur cellule donc T_liste
    if (!isListePlayerVide(l)){
        fin = getptrLastCell(l); //pour ne faire qu'un seul appel de cette fonction en O(n)

        //nous ne faisons ici que des branchements et déplacements de pointeurs
        for (en_cours = (*l); en_cours != fin; en_cours=getptrNextCell(&en_cours)) //avec "en_cours != fin", nous nous arrêtons bien sur l'avant dernière cellule
        {
            plus_petit = en_cours;
            for (j = en_cours ; j != fin; j=getptrNextCell(&j))
            {
                if (fcomp(getPtrData(&plus_petit),getPtrData(&j)))  //MAJ fcomp
                    plus_petit = j;  //branchement de "plus_petit" sur la cellule ayant une valeur pointée par data plus petite que celle pointée par plus_petit
            }
            //comparaison avec la cellule fin non comparée dans le FOR ci-dessus
            if (fcomp(getPtrData(&plus_petit), getPtrData(&fin))) plus_petit = fin;  //MAJ fcomp

            //swap
            swapPtrData(&en_cours, &plus_petit);
        }
    }
}*/

