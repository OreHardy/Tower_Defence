//NOM prénom étudiant 1 : HARDY Oregan
//NOM prénom étudiant 2 : CAILLE PAUL

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"
#include "listePlayer.h"
#include "sauvegardes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define HORDESPAWNRATE 100
#define ROISPAWNRATE 10 //10 étant le taux le plus équilibré que nous avons trouvés

/*--------------------- Main ---------------------*/
int main(int argc, char* argv[])
{
    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        //"Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        "TOWER DEFENCE de Oregan et Paul",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    //SDL_Renderer * renderer = SDL_CreateRenderer(pWindow, -1, 0);  //non utilisé, pour mémoire

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");  //indice 1 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 2
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 3
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 4
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 5
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 6
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 7  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 8 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 9 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 10 idem

    // ASTUCE : on stocke le sprite d'une unité à l'indice de son nom dans le type enum TuniteDuJeu, dans le tableau TabSprite
    // SAUF pour l'Eau, l''herbe et le pont qui apparaitront en l absence d'unité (NULL dans le plateau) et en foction de certains indices x,y définissant le chemin central
    SDL_Surface* TabSprite[11]={pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();  //tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau à 2 cases (indice 0 pour X, indice 1 pour Y)

    if ( pSpriteTourSol )  //si le permier sprite a bien été chargé, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);
        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //message("Lancement de TowerDfend","Debut du jeu !");
        //message("Commandes","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");

        //Defintions des variables

        Tunite *a=creeUniteAleatoire(5,18); //on crée toujours une unité au début pour la horde
        Tunite *r=creeTourRoi(4,1);

        TListePlayer listeRoi;
        TListePlayer listeHorde;

        initListePlayer(&listeRoi);
        initListePlayer(&listeHorde);

        ajoutTeteListePlayer(&listeRoi,r);
        ajoutTeteListePlayer(&listeHorde,a);

        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        positionnePlayerOnPlateau(&listeRoi,jeu);
        positionnePlayerOnPlateau(&listeHorde,jeu);

        printf("\nListes apres initialisation ==> \n\n");

        printf("Liste du roi : \n");
        afficheListePlayer(&listeRoi);

        printf("Liste de la horde : \n");
        afficheListePlayer(&listeHorde);

        printf("\n<========================== DEBUT DU JEU | REGLAGES : SRH = %d , SRR = %d ==========================>\n", HORDESPAWNRATE, ROISPAWNRATE);

        // boucle principale du jeu
        int cont = 1;
        int tour = 0;
        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events

                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);

                /***********************************************************************/
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                combatHorde(pWinSurf,&listeRoi,&listeHorde);
                combatTour(pWinSurf,&listeRoi,&listeHorde);

                supprimerUnite(&listeHorde);

                avanceUnite(&listeHorde, tabParcours);
                generationUniteAleatoire(pWinSurf,&listeRoi,&listeHorde, tabParcours, HORDESPAWNRATE, ROISPAWNRATE);

                printf("---------- TOUR %d | PV DU ROI = %d ----------\n", tour, getPtrData(&listeRoi)->pointsDeVie);
                initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
                positionnePlayerOnPlateau(&listeRoi,jeu);
                positionnePlayerOnPlateau(&listeHorde,jeu);

                tour++;
                cont=isRoiVivant(&listeRoi)&&isTourDeJeuInfA250(tour);
                affichageRoiMort(isRoiVivant(&listeRoi));

                // FIN DE VOS APPELS
                /***********************************************************************/

                maj_fenetre(pWindow);

                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES

                if ( pKeyStates[SDL_SCANCODE_V] ){

                        loadASCII(&listeRoi, &listeHorde);
                        message("Sauvegarde ASCII","Sauvegarde ASCII ouverte !");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){

                        saveASCII(&listeRoi,&listeHorde);
                        message("Sauvegarde ASCII","Sauvegarde ASCII créee !");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){

                        loadBinary(&listeRoi, &listeHorde);
                        message("Sauvegarde binaire","Sauvegarde binaire ouverte !");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){

                        saveBinary(&listeRoi, &listeHorde);
                        message("Sauvegarde binaire","Sauvegarde binaire créee !");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

                SDL_Delay(500);  //valeur du délai à modifier éventuellement


        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTourSol); // Libération de la ressource occupée par le sprite
        SDL_FreeSurface(pSpriteTourAir);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
