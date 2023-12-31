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
    #define SUPPRIPRESSION_ANCIENNE_POSITION_JOUEUR_REUSSI 1
    #define ECHEC_DE_SAUVEGARDE -1
    #define POSITION_SAUVEGARDEE_AVEC_SUCCES 1
    #define INDICE_MIN 0
    #define ECHEC_DESSIN -3
    #define DESSIN_REUSSI 0
    #define ANGLE_SPECTRE_VISION 50
    #define INCREMENTATION_VISION 2
    #define INCREMENTATION_ANGLE 2
    #define ANGLE_NULL 0
    #define PI_DEGRE 180
    #define DESSIN_RAYON 1
    #define EFFACEMENT_RAYON 0

    /**************************STRUCTURE DU JOUEUR*********************/

    typedef struct{

        SDL_Point* position_joueur;
        int angle_vision;
    }joueur;

    /**************************FONCTIONS DU JOUEUR*********************/

    int deplacer_joueur(SDL_Event evenement, int** map, int nb_lignes, int nb_colonnes, SDL_Point* position_joueur, SDL_Point* ancienne_position, int* debut_vision);
    int afficher_joueur(SDL_Renderer* rendu, SDL_Point* position_joueur);
    int effacer_ancienne_position_joueur(SDL_Renderer* rendu, SDL_Point* ancienne_position_joueur);
    int sauvegarder_ancienne_position(SDL_Point* position_joueur, SDL_Point* ancienne_position_joueur);
    int tracer_effacer_un_rayon(SDL_Renderer* rendu, SDL_Point* origine, SDL_Point* extremite, int mode);
    int dessiner_ou_supprimer_vision_joueur(SDL_Renderer* rendu, SDL_Point* origine, int debut_vision, int mode);
    double conversion_radian_angle(int angle_degre);
#endif




