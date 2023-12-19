#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include "listePlayer.h"

//typedef Tunite* ** TplateauJeu;

// ================================================
TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}

// ================================================
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

// ================================================
void afficheUnite(Tunite *uniteAffichee){                                           //fonction d'affichage d'une unité dans la console

        int nomUnite=uniteAffichee->nom;
        int peutAttaquerUnite=uniteAffichee->peutAttaquer;
        int vieUnite=uniteAffichee->pointsDeVie;
        int posxUnite=uniteAffichee->posX;
        int posyUnite=uniteAffichee->posY;


         switch(nomUnite){
            case 0 :
                printf("Tour sol | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | ", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
             case 1 :
                printf("Tour air | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
            case 2 :
                printf("Tour Roi | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
            case 3 :
                printf("Archer | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
            case 4 :
                printf("Chevalier| ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
            case 5 :
                printf("Dragon | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;
            case 6 :
                printf("Gargouille | ");
                printf("Peut attaquer = %d | ", peutAttaquerUnite);
                printf("Vie unite = %d | \n", vieUnite);
                printf("Pos X = %d | ", posxUnite);
                printf("Pos Y = %d | \n", posyUnite);
                break;

        }
}

/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, à partir d'un point x y donné

int **chemin  : tab de coordonnées x y du chemin
int *ichemin  : indice de la case du chemin d'où on part
int *xdepart, int *ydepart : valeur en x y de départ pouri la premiere case
int distance  : distance sur laquelle on va écrire des coordonnées dans le tab chemin
int *distanceMaxRestante : securité pour ne pas sortir de la plage d'indice de chemin
*/
// ================================================
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}

// ================================================
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

// ================================================
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

// ================================================
int **initChemin(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //19 on part du bas
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}

// ================================================
void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnées\n");
}

// ================================================
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

// ================================================
Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 180;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement =3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// ================================================
Tunite *creeUniteAleatoire(int posx, int posy){
    int choix = 3 + rand() / (RAND_MAX / (6 - 3 + 1) + 1);
    switch(choix){
            case 3 :
                return creeArcher(posx,posy);
                break;
            case 4 :
                return creeChevalier(posx,posy);
                break;
            case 5 :
                return creeDragon(posx,posy);
                break;
            case 6 :
                return creeGargouille(posx,posy);
                break;
        }
        printf("\n unite cree : %d", choix);
        return creeArcher(posx, posy);
}

// ================================================
void positionnePlayerOnPlateau(TListePlayer *l, TplateauJeu jeu){           //fonction de positionnement des listes player sur le plateau
    TListePlayer tmp = *l;
    while(!isListePlayerVide(&tmp)){                                                        //tant que la liste player contient des elements
        int posix = tmp->pdata->posX;                                        //on stocke la position en x de l'unité
        int posiy = tmp->pdata->posY;                                        //on stocke la position en y de l'unité
        jeu[posix][posiy]=tmp->pdata;                                        //on mets ensuite dans la case x y associé de plateau la valeur pdata de l'unité
        tmp = tmp->suiv;                                                      //on passe a l'unité suivante de la liste
    }
}

// ================================================
bool isOnChemin(int x, int y, int **chemin){
    bool result = false;
    for (int i = 0; i<NBCOORDPARCOURS; i++){
        //printf("%d / ",i);
        if (x==chemin[i][0]&&y==chemin[i][1]){
            //printf("chemin[%d] : x = %d y = %d \n", i, chemin[i][0],chemin[i][1]);
            result=true;
            //printf("\nEst sur le chemin !\n");
            return result;
        }
    }
    //printf("\nPas sur le chemin !\n");
    return result;
}

// ================================================
bool isInSamePosition(TListePlayer *l, int x1, int y1){
    TListePlayer tmp=*l;
    bool result = false;

    //printf("\nL'unite a verif a pour coor x = %d et y = %d\n", x1,y1);

    while(result==false && !(isListePlayerVide(&tmp))){
        //printf("is liste vide ? %d", isListePlayerVide(&tmp));
        //printf("\nL'unite de la liste a pour coor x = %d et y = %d\n",getPtrData(&tmp)->posX ,getPtrData(&tmp)->posY);

        if(x1==(getPtrData(&tmp)->posX) && y1==(getPtrData(&tmp)->posY)) {
            result=true;
        }
        else{
            tmp=getptrNextCell(&tmp);
        }
    }
    return result;
}

// ================================================
void positionneTour(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2, int **chemin){
    if (!isListePlayerVide(l2)){

        TListePlayer temp = *l2;
        tri_selection(&temp, fcompPosY); //on trie les unités de la horde selon leur position sur l'axe y,
        bool choixIsAir;                //c-a-d celles qui sont les plus proches du roi
        int distanceApparition;

        int x = 1 + rand() / (RAND_MAX / (10 - 1 + 1) + 1);
        int y = 1 + rand() / (RAND_MAX / (18 - 1 + 1) + 1);

        //printf("\nUnite choisie pour affectation tour : \n");
        Tunite *uniteChoisie = getPtrData(&temp);
        //afficheUnite(uniteChoisie);

        Tcible position = uniteChoisie->maposition;
        //printf("\nma position est %d\n", position);

        if (position==2){
            distanceApparition=3;
            choixIsAir = true;
        }
        else  {
            distanceApparition=4; //on a volontairement réduit la distance d'apparition par rapport à la portée
            choixIsAir = false;   //pour éviter des apparitions trop défavorables à la horde
        }

        int xUniteHorde = uniteChoisie->posX, yUniteHorde =uniteChoisie->posY;

        while (((isInSamePosition(l1,x, y) || isOnChemin(x,y,chemin)) || (((x-xUniteHorde)*(x-xUniteHorde)+(y-yUniteHorde)*(y-yUniteHorde))>distanceApparition*distanceApparition))){
        //on vérifie que les coordonnées choisies ne sont pas déjà occupées, ne sont pas sur le chemin
        //et sont bien comprises dans le cercle de rayon la portée de la tour et de centre l'unité selectionnée
            //printf("\nPas dans la bonne zone !\n");
            x = 1 + rand() / (RAND_MAX / (10 - 1 + 1) + 1);
            y = 1 + rand() / (RAND_MAX / (18 - 1 + 1) + 1);
        }

        dessineCase(surface, x, y, 0xFFFFFF); //affichage de la case selectionnée
        //printf("\nx choisi : %d y choisi : %d\n", x,y);
        dessineSpawn(surface, uniteChoisie,distanceApparition,0x0000FF); //affichage du cercle d'apparition

        if (choixIsAir) {
            ajoutEn2ListePlayer(l1 , creeTourAir(x,y));
        }
        else{
            ajoutEn2ListePlayer(l1 , creeTourSol(x,y));
        }
    }

}

// ================================================
bool fcompPosY(Tunite *unite1, Tunite *unite2){
    int posY1 = unite1->posY;
    int posY2 = unite2->posY;

    return posY1>posY2;
}

// ================================================
bool fcompPV(Tunite *unite1, Tunite *unite2){
    int vie1 = unite1->pointsDeVie;
    int vie2 = unite2->pointsDeVie;

    return vie1>vie2;
}

// ================================================
void positionneUniteHorde(TListePlayer *l2){
    ajoutTeteListePlayer(l2, creeUniteAleatoire(5,18)); //on fait apparaitre au debut du chemin
}

// ================================================
void generationUniteAleatoire(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2, int **chemin, int tauxHorde, int tauxRoi){
    int resultTirageHorde = 0 + rand() / (RAND_MAX / (100 - 0 + 1) + 1);
    int resultTirageRoi = 0 + rand() / (RAND_MAX / (100 - 0 + 1) + 1);
    //printf("\ngeneration unite : taux horde = %d, score obtenu = %d", tauxHorde, resultTirageHorde);
    //printf("\ngeneration unite : taux roi = %d, score obtenu = %d", tauxRoi, resultTirageRoi);


    if (resultTirageHorde<=tauxHorde){
        //printf("\nGeneration unite HORDE REUSSIE !\n");
        positionneUniteHorde(l2);
    }

    if (resultTirageRoi<tauxRoi){
        //printf("\nGeneration unite TOUR REUSSIE !\n");
        positionneTour(surface, l1,l2,chemin);
    }

}

// ================================================
int findOuSurChemin(Tunite *uniteDemandee, int**chemin){
    int x = uniteDemandee->posX;
    int y = uniteDemandee->posY;

    for (int i=0; i<NBCOORDPARCOURS; i++){
        if (x==chemin[i][0]&&y==chemin[i][1]){
            return i;
        }
    }
    printf("\nPlace de l'unite dans le chemin non trouvee !");
    return 0;

}

// ================================================
void avanceUnite(TListePlayer *l2, int**chemin){
    TListePlayer tmp = *l2;
    TListePlayer tmp2 = *l2;

    while(!(isListePlayerVide(&tmp))){
        Tunite* uniteCur = getPtrData(&tmp);
        bool aEteDeplace = false;

        //printf("\noldPos : %d,%d\n", uniteCur->posX, uniteCur->posY);
        int deplacement = uniteCur->vitessedeplacement;

        //printf("vitesse de deplacement : %d", deplacement);
        int i = findOuSurChemin(uniteCur, chemin);
        //printf("\nJe suis a la case %d\n",i);

        while(!aEteDeplace){
            aEteDeplace = false;
            //printf("Pos actuelle : %d,%d\n",(chemin[i+deplacement][0]),(chemin[i+deplacement][1]));
            //printf("\nJe veux aller a la case %d\n",i+deplacement);
            if (i+deplacement>33 || isInSamePosition(&tmp2, (chemin[i+deplacement][0]), (chemin[i+deplacement][1]))){
            //on vérifie si la case ou l'on veux arriver n'est pas déjà occupée ou en dehors du chemin
            //si ca l'est on decremente l'avancement de 1, si aucune case n'est libre alors on ne bouge pas
                if (deplacement==0){
                    aEteDeplace=true;
                }
                else {
                    deplacement--;
                }
            }
            else {
                aEteDeplace=true;
            }

        }

        uniteCur->posX=(chemin[i+deplacement][0]);
        uniteCur->posY=(chemin[i+deplacement][1]);
        //printf("\nvalind = %d, newPos : %d,%d\n", i, uniteCur->posX, uniteCur->posY);
        tmp=getptrNextCell(&tmp);
        }
}

// ================================================
void quiEstAPortee(TListePlayer *l2, TListePlayer *lcible, Tunite *ptrUnite){
    TListePlayer temp=*l2;

    int porteeUnite = ptrUnite->portee;

    int x=ptrUnite->posX;
    int y=ptrUnite->posY;

    Tcible positionCiblable = ptrUnite->cibleAttaquable;

    while(!isListePlayerVide(&temp)){
        Tunite *uniteCur = getPtrData(&temp);
        //afficheUnite(uniteChoisie);

        Tcible positionCible = uniteCur->maposition;
        int xUnite = uniteCur->posX, yUnite = uniteCur->posY;

        if((positionCiblable==positionCible || positionCiblable==1) && (((xUnite-x)*(xUnite-x)+(yUnite-y)*(yUnite-y))<porteeUnite*porteeUnite)){
            ajoutTeteListePlayer(lcible, uniteCur);
        }

        temp=getptrNextCell(&temp);
    }
}

// ================================================
void combatHorde(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2){
    TListePlayer lHorde = *l2;
    //afficheListePlayer(l1);
    Tunite *roi = getPtrData(l1);
    //afficheUnite(roi);

    int xRoi = 4;
    int yRoi = 1;

    while(!isListePlayerVide(&lHorde)){

        Tunite *uniteCur = getPtrData(&lHorde);
        //afficheUnite(uniteCur);
        int porteeUnite = uniteCur->portee;
        //printf("\nporte unite = %d\n", porteeUnite);

        int x = uniteCur->posX, y = uniteCur->posY;

        if((((xRoi-x)*(xRoi-x)+(yRoi-y)*(yRoi-y))<=porteeUnite*porteeUnite)){
            dessineAttaque(surface, uniteCur, roi, 0x008000);
            roi->pointsDeVie = roi->pointsDeVie - uniteCur->degats;
        }
    lHorde=getptrNextCell(&lHorde);
    }

}

// ================================================
void combatTour(SDL_Surface *surface, TListePlayer *l1, TListePlayer *l2){
    if (!isListePlayerVide(l2)){
        TListePlayer lRoi = *l1;
        TListePlayer lHorde = *l2;
        TListePlayer lCible;

        while(!isListePlayerVide(&lRoi)){
            initListePlayer(&lCible);
            Tunite *uniteAttaquante = getPtrData(&lRoi);
            quiEstAPortee(&lHorde, &lCible, uniteAttaquante);

            if (!isListePlayerVide(&lCible)){
                tri_selection(&lCible, fcompPV); //on choisit l'unité qui a le moins de vie
                Tunite *uniteChoisie = getPtrData(&lCible);
                //printf("\nUnite Choisie pour etre attaquer : \n");
                //afficheUnite(uniteChoisie);
                dessineAttaque(surface, uniteAttaquante, uniteChoisie, 0xFF0000);
                int pointsAttaque = uniteAttaquante->degats;

                uniteChoisie->pointsDeVie = uniteChoisie->pointsDeVie - pointsAttaque;
                //printf("PV après attaque : %d" , uniteChoisie->pointsDeVie);
            }

            lRoi = getptrNextCell(&lRoi);
        }
    }
}

// ================================================
void supprimerUnite(TListePlayer *l2){
    TListePlayer lHorde = *l2;
    while(!isListePlayerVide(&lHorde)){
        Tunite *curUniteHorde = getPtrData(&lHorde);
        if (curUniteHorde->pointsDeVie<=0){
            //printf("PV INF A 0");

            supprUniteListePlayer(l2,curUniteHorde);
            //afficheListePlayer(l2);
        }
        lHorde=getptrNextCell(&lHorde);
    }
}

// ================================================
bool isRoiVivant(TListePlayer *l1){
    return getPtrData(l1)->pointsDeVie>0; //le roi est toujours en première position
}

// ================================================
void affichageRoiMort(bool isRoiVivant){
    if (!isRoiVivant){
        printf("\n\n\n[!]---------------- LE ROI EST MORT ! LA HORDE GAGNE ! ----------------[!]\n");
        printf("\n<========================== FIN DU JEU (Merci d'avoir joue !) ==========================>\n");
        message("Fin de TowerDfend","Le roi est mort ! Fin du jeu ! Merci d'avoir joue :)");
    }
}

// ================================================
bool isTourDeJeuInfA250(int nbTourDeJeu){ //on s'arrête après 250 tour de jeu car après essais il n'y a plus de case disponibles
                                          //pour le positionnement des tours et cela entraine des erreurs
    return nbTourDeJeu<=250;
}
