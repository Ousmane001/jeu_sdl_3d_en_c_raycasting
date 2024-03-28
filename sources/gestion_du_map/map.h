#ifndef MAP_H

    #define MAP_H


    #include "../../includes_de_SDL/entetes_sdl.h"

    #define DECALAGE 795
    #define FICHIER_MAP "sources/gestion_du_map/fichier_map.csv"
    #define TAILLE_MAX_TAMPON 1024
    #define ERREUR_OUVERTURE -1
    #define ERREUR_LECTURE -2
    #define MATRICE_CREEE 0
    #define ERREUR_MAP -4
    #define OUVERTURE_SUCCES 0
    #define PREMIER_CARACTERE 0
    #define CARACTERE_SEPARATEUR ','
    #define MATRICE_CHARGEE_AVEC_SUCCES 0
    #define MAP_CORRECT 0
    #define OBSTACLE 1
    #define TAILLE_MUR 15
    #define MUR_DESSINE_AVEC_SUCCES 0
    #define ERREUR_DESSIN_MUR -7
    #define MAP_AFFICHEE_AVEC_SUCCES 0
    #define ERREUR_AFFICHAGE_MAP -9
    #define MAP_DETRUITE_AVEC_SUCCES 0
    #define ESPACE_VIDE 0
    #define HAUTEUR_ESPACE_AFFICHAGE 900 
    #define LARGEUR_MUR 25
    #define DISTANCE_MINIMAL 7.5
    #define DEBUT_AFFICHAGE_3DX 25 
    #define DEBUT_AFFICHAGE_3DY 30
    #define FIN_RENDU_3D 680
    #define COEFF_DIRECTEUR 10




    int scanner_une_map(char* fichier, int* nombre_de_ligne, int* nombre_de_colonne);
    int allouer_une_map_correcte(int*** map, int nombre_de_ligne, int nombre_de_colonne);
    int charger_une_map(char* fichier, int** map);
    int dessiner_un_mur_2D(SDL_Renderer* rendu, SDL_Rect* mur);
    int afficher_une_map(SDL_Renderer* rendu, int** map, int nombre_de_ligne, int nombre_de_colonne, int debut_x, int debut_y);
    int detruire_une_map(int*** map, int nombre_de_ligne);
    int afficher_une_map_3D(SDL_Renderer* rendu,int nb_ligne, int* distances, int nb_rayon, int portee_vision);
    
#endif
