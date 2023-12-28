#ifndef JOUEUR_H

    #define JOUEUR_H
    #include "../../includes_de_SDL/entetes_sdl.h"
    #include "../gestion_du_map/map.h"
    #include <stdio.h>
    #include <stdlib.h>
    
    #define PAS_DU_JOUEUR_PIXEL 15
    #define PAS_DU_JOUEUR_MAP 1
    #define ERREUR_EVENEMENT -1
    #define JOUEUR_A_BOUGE 1
    #define JOUEUR_NE_BOUGE_PAS 0
    #define ERREUR_RENDERER_POSITION -2
    #define TAILLE_JOUEUR 15
    #define AFFICHAGE_JOUEUR_REUSSI 1
    #define INDICE_MIN 0
    /**************************STRUCTURE DU JOUEUR*********************/
    typedef struct{

        SDL_Point* position_joueur;
        int angle_vision;
    }joueur;

    /**************************FONCTIONS DU JOUEUR*********************/

    int deplacer_joueur(SDL_Event evenement, int** map, int nb_lignes, int nb_colonnes, SDL_Point* position_joueur);
    int afficher_joueur(SDL_Renderer* rendu, SDL_Point* position_joueur);

#endif




