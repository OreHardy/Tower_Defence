#define SORTIE1 "partieseq.cls"
#define SORTIE2 "partiebin.clb"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "towerdefend.h"
#include "listePlayer.h"
#include "sauvegardes.h"

// ================================================
void saveASCII(TListePlayer *l1, TListePlayer *l2){

    TListePlayer tmp1 = *l1;
    TListePlayer tmp2 = *l2;

    //On recupere le nombre d'unite dans chaque liste
    int nbTour = getNbreUnite(&tmp1);
    int nbHorde = getNbreUnite(&tmp2);

    FILE *f_out = NULL;

    f_out=fopen(SORTIE1, "w");

    //On ecrit les deux nombres d'unite au debut du fichier
    fprintf(f_out, "%d\n", nbTour);
    fprintf(f_out, "%d\n", nbHorde);

    //On parcourt la liste du roi et on ecrit les unites dans le fichier
    //champ par champ
    for (int i = 0; i<nbTour; i++){
        Tunite *uniteCurRoi = getPtrData(&tmp1);
        fprintf(f_out, "%d ", uniteCurRoi->cibleAttaquable);
        fprintf(f_out, "%d ", uniteCurRoi->degats);
        fprintf(f_out, "%d ", uniteCurRoi->maposition);
        fprintf(f_out, "%d ", uniteCurRoi->nom);
        fprintf(f_out, "%d ", uniteCurRoi->peutAttaquer);
        fprintf(f_out, "%d ", uniteCurRoi->pointsDeVie);
        fprintf(f_out, "%d ", uniteCurRoi->portee);
        fprintf(f_out, "%d ", uniteCurRoi->posX);
        fprintf(f_out, "%d ", uniteCurRoi->posY);
        fprintf(f_out, "%f ", uniteCurRoi->vitesseAttaque);
        fprintf(f_out, "%f \n", uniteCurRoi->vitessedeplacement);
        tmp1=getptrNextCell(&tmp1);
    }

    //On parcourt la liste de la horde et on ecrit les unites dans le fichier
    //champ par champ
    for (int j = 0; j<nbHorde; j++){
        Tunite *uniteCurHorde = getPtrData(&tmp2);
        fprintf(f_out, "%d ", uniteCurHorde->cibleAttaquable);
        fprintf(f_out, "%d ", uniteCurHorde->degats);
        fprintf(f_out, "%d ", uniteCurHorde->maposition);
        fprintf(f_out, "%d ", uniteCurHorde->nom);
        fprintf(f_out, "%d ", uniteCurHorde->peutAttaquer);
        fprintf(f_out, "%d ", uniteCurHorde->pointsDeVie);
        fprintf(f_out, "%d ", uniteCurHorde->portee);
        fprintf(f_out, "%d ", uniteCurHorde->posX);
        fprintf(f_out, "%d ", uniteCurHorde->posY);
        fprintf(f_out, "%f ", uniteCurHorde->vitesseAttaque);
        fprintf(f_out, "%f \n", uniteCurHorde->vitessedeplacement);
        tmp2=getptrNextCell(&tmp2);
    }

    fclose(f_out);
    printf("Le fichier partieseq.cls a ete cree, essayez de le lire avec un notepad++,gedit, etc.\n");
}

// ================================================
void loadASCII(TListePlayer *l1, TListePlayer *l2){

    initListePlayer(l1);
    initListePlayer(l2);

    FILE *f_in = NULL;
    int nbTour;
    int nbHorde;

    f_in=fopen(SORTIE1, "r");

    //On lit les les nombres d'unite des deux listes
    fscanf(f_in,"%d",&nbTour);
    printf("nb de tour : %d\n", nbTour);
    fscanf(f_in,"\n");
    fscanf(f_in,"%d",&nbHorde);

    for (int i = 0; i<nbTour; i++){
        Tunite *uniteAAjouter = creeArcher(0,0); //On cree une unite "tampon" dont on va modifier les champs grace au fichier
        int myCibleAttaquable, myDegats, myPosition, myNom, myPeutAttaquer, myPV, myPortee, myPosX, myPosY;
        float myVitesseAttaque, myVitesseDeplacement;
        fscanf(f_in,"%d %d %d %d %d %d %d %d %d %f %f",&myCibleAttaquable, &myDegats, &myPosition, &myNom, &myPeutAttaquer, &myPV, &myPortee, &myPosX, &myPosY, &myVitesseAttaque, &myVitesseDeplacement);
        uniteAAjouter->cibleAttaquable=myCibleAttaquable;
        uniteAAjouter->degats=myDegats;
        uniteAAjouter->maposition=myPosition;
        uniteAAjouter->nom=myNom;
        uniteAAjouter->peutAttaquer=myPeutAttaquer;
        uniteAAjouter->pointsDeVie=myPV;
        uniteAAjouter->portee=myPortee;
        uniteAAjouter->posX=myPosX;
        uniteAAjouter->posY=myPosY;
        uniteAAjouter->vitesseAttaque=myVitesseAttaque;
        uniteAAjouter->vitessedeplacement=myVitesseDeplacement;

        //printf("unite recup = \n");
        //afficheUnite(uniteAAjouter);

        if (i==0) ajoutTeteListePlayer(l1, uniteAAjouter); //Si c'est le roi (première unité) on ajoute en tête
        else ajoutEn2ListePlayer(l1, uniteAAjouter); //On ajoute en deux pour le reste
    }


    for (int j = 0; j<nbHorde; j++){
        Tunite *uniteAAjouter = creeArcher(0,0);
        int myCibleAttaquable, myDegats, myPosition, myNom, myPeutAttaquer, myPV, myPortee, myPosX, myPosY;
        float myVitesseAttaque, myVitesseDeplacement;
        fscanf(f_in,"%d %d %d %d %d %d %d %d %d %f %f",&myCibleAttaquable, &myDegats, &myPosition, &myNom, &myPeutAttaquer, &myPV, &myPortee, &myPosX, &myPosY, &myVitesseAttaque, &myVitesseDeplacement);
        uniteAAjouter->cibleAttaquable=myCibleAttaquable;
        uniteAAjouter->degats=myDegats;
        uniteAAjouter->maposition=myPosition;
        uniteAAjouter->nom=myNom;
        uniteAAjouter->peutAttaquer=myPeutAttaquer;
        uniteAAjouter->pointsDeVie=myPV;
        uniteAAjouter->portee=myPortee;
        uniteAAjouter->posX=myPosX;
        uniteAAjouter->posY=myPosY;
        uniteAAjouter->vitesseAttaque=myVitesseAttaque;
        uniteAAjouter->vitessedeplacement=myVitesseDeplacement;

        //printf("unite recup = \n");
        //afficheUnite(uniteAAjouter);

        ajoutTeteListePlayer(l2, uniteAAjouter);
    }

    afficheListePlayer(l1);
    afficheListePlayer(l2);

    fclose(f_in);
    printf("Le fichier partieseq.cls a ete lu\n");
}

// ================================================
void saveBinary(TListePlayer *l1, TListePlayer *l2){

    TListePlayer tmp1 = *l1;
    TListePlayer tmp2 = *l2;

    FILE *f_out = fopen(SORTIE2, "wb");

    //on écrit le nombre d'unité qui vont être présentes dans la list
    int nbTour = getNbreUnite(&tmp1);
    int nbHorde = getNbreUnite(&tmp2);

    fwrite(&nbTour, sizeof(int),1,f_out);
    fwrite(&nbHorde, sizeof(int),1,f_out);

    for (int i = 0; i<nbTour; i++){
        Tunite *uniteCurRoi = getPtrData(&tmp1);
        //afficheUnite(uniteCurRoi);
        fwrite(uniteCurRoi, sizeof(Tunite),1,f_out); //On écrit directement la structure des unités dans le fichier binaire
        tmp1=getptrNextCell(&tmp1);
    }

    for (int j = 0; j<nbHorde; j++){
        Tunite *uniteCurHorde = getPtrData(&tmp2);
        //afficheUnite(uniteCurHorde);
        fwrite(uniteCurHorde, sizeof(Tunite),1,f_out); //On écrit directement la structure des unités dans le fichier binaire
        tmp2=getptrNextCell(&tmp2);
    }

    fclose(f_out);
    printf("Le fichier partiebin.clb a ete cree\n");
}

// ================================================
void loadBinary(TListePlayer *l1, TListePlayer *l2){

    initListePlayer(l1);
    initListePlayer(l2);

    FILE *f_in = fopen(SORTIE2, "rb");

    int nbTour ;
    int nbHorde ;

    fread(&nbTour, sizeof(int),1,f_in);
    fread(&nbHorde, sizeof(int),1,f_in);

    //printf("\n le nombre du roi est %d et de horde est %d\n", nbTour, nbHorde);

    for (int i = 0; i<nbTour; i++){
        Tunite *uniteCurRoi=(Tunite *)malloc(sizeof(Tunite));
        fread(uniteCurRoi, sizeof(Tunite),1,f_in);
        //printf("\nUnite roi recup du fichier bin : \n");
        //afficheUnite(uniteCurRoi);
        if (i==0) ajoutTeteListePlayer(l1, uniteCurRoi); // le roi est toujours en tête
        else ajoutEn2ListePlayer(l1, uniteCurRoi);       // ajout en position 2 pour être efficace
    }

    for (int j = 0; j<nbHorde; j++){
        Tunite *uniteCurHorde=(Tunite *)malloc(sizeof(Tunite));
        fread(uniteCurHorde, sizeof(Tunite),1,f_in);
        //printf("\nUnite horde recup du fichier bin : \n");
        //afficheUnite(uniteCurHorde);
        ajoutTeteListePlayer(l2, uniteCurHorde);
    }

    afficheListePlayer(l1);
    afficheListePlayer(l2);

    fclose(f_in);
    printf("Le fichier partiebin .clb a ete lu\n");
}
