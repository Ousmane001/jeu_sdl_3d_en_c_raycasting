#include "joueur.h"


/*-------------------------------------------------------------------------------------------------------------*/
int deplacer_joueur(SDL_Event evenement, int** map, int nb_lignes, int nb_colonnes, SDL_Point* position_joueur, SDL_Point* ancienne_position, int* debut_vision){
    
    // si le pointeur evenement est invalide :
    if((map == NULL) || (position_joueur == NULL)){
        printf("Erreur : au moins un des argument de cette fonction est NULL :\n");
        return ERREUR_EVENEMENT;
    }
    else if(evenement.type == SDL_KEYDOWN){
        // sinon si tout est correct:
        switch (evenement.key.keysym.sym)
        {
        case SDLK_LEFT:
            printf("le joueur est allee vers l'avant\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            // verification de la matrice pour eviter des erreurs de segmentation :
            if(position_joueur->x > INDICE_MIN){
                // si le joueur peut se déplacer vers le haut ou vers l'avant :
                if(map[position_joueur->y][position_joueur->x - PAS_DU_JOUEUR_MAP] != OBSTACLE){
                    if(sauvegarder_ancienne_position(position_joueur,ancienne_position) != POSITION_SAUVEGARDEE_AVEC_SUCCES){
                        printf("Erreur de sauvegarde: le joueur ne se deplacera pas !\n");
                        return JOUEUR_NE_BOUGE_PAS;
                    }
                    else{
                        position_joueur->x--;
                    }
                    return JOUEUR_A_BOUGE;
                }
                
            }
            
            break;
        case SDLK_RIGHT:
            printf("le joueur est allee vers l'arriere\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            
            // verification de la matrice pour eviter des erreurs de segmentation :
            if((position_joueur->x + PAS_DU_JOUEUR_MAP) < nb_colonnes){
                // si le joueur veut reculer :
                if(map[position_joueur->y][position_joueur->x + PAS_DU_JOUEUR_MAP] != OBSTACLE){
                    if(sauvegarder_ancienne_position(position_joueur,ancienne_position) != POSITION_SAUVEGARDEE_AVEC_SUCCES){
                        printf("Erreur de sauvegarde: le joueur ne se deplacera pas !\n");
                        return JOUEUR_NE_BOUGE_PAS;
                    }
                    else{
                        position_joueur->x++;
                    }
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;

        case SDLK_UP:
            printf("le joueur est allee vers la gauche\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if(position_joueur->y >= PAS_DU_JOUEUR_MAP){
                // si le joueur se dirige vers la gauche: 
                if(map[position_joueur->y - PAS_DU_JOUEUR_MAP][position_joueur->x] != OBSTACLE) {
                    if(sauvegarder_ancienne_position(position_joueur,ancienne_position) != POSITION_SAUVEGARDEE_AVEC_SUCCES){
                        printf("Erreur de sauvegarde: le joueur ne se deplacera pas !\n");
                        return JOUEUR_NE_BOUGE_PAS;
                    }
                    else{
                        position_joueur->y--;
                    }
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;
        case SDLK_DOWN:
            printf("le joueur est allee vers la droite\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if((position_joueur->y + PAS_DU_JOUEUR_MAP) < nb_lignes){
                // si le joueur se dirige vers la droite :
                if(map[position_joueur->y + 1][position_joueur->x] != OBSTACLE){
                    if(sauvegarder_ancienne_position(position_joueur,ancienne_position) != POSITION_SAUVEGARDEE_AVEC_SUCCES){
                        printf("Erreur de sauvegarde: le joueur ne se deplacera pas !\n");
                        return JOUEUR_NE_BOUGE_PAS;
                    }
                    else{
                        position_joueur->y++;
                    }
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;
        
        case SDLK_q : 
            printf("le joueur tourne la tete vers la gauche .\n");
            *debut_vision += INCREMENTATION_VISION;

            if(*debut_vision > 2*PI_DEGRE){
                *debut_vision -= 2*PI_DEGRE;
            }
            return JOUEUR_A_BOUGE;
        case SDLK_d :
            printf("le joueur tourne la tete vers la droite .\n");
            *debut_vision -= INCREMENTATION_VISION;

            if(*debut_vision < ANGLE_NULL){
                *debut_vision += 2*PI_DEGRE;
            }
            return JOUEUR_A_BOUGE;
        default:
            printf("le default est active\n");
            return JOUEUR_NE_BOUGE_PAS;
            break;
        }
        // si aucune des situations ne correspond alors il ne bouge pas :
        return JOUEUR_NE_BOUGE_PAS;
    }

}
/*-------------------------------------------------------------------------------------------------------------*/
int afficher_joueur(SDL_Renderer* rendu, SDL_Point* position_joueur){

    SDL_Rect joueur;

    // si le pointeur renderer est invalide ou la position_joueur :
    if((rendu == NULL) || (position_joueur == NULL)){
        printf("Erreur : le pointeur du rendu ou de la position joueur est null\n");
        return ERREUR_RENDERER_POSITION;
    }
    else{
        joueur.h = TAILLE_JOUEUR;
        joueur.w = TAILLE_JOUEUR;
        joueur.x = PAS_DU_JOUEUR_PIXEL* position_joueur->x;
        joueur.y = PAS_DU_JOUEUR_PIXEL* position_joueur->y;

        COULEUR_ROUGE(rendu);
        SDL_RenderFillRect(rendu,&joueur);
        SDL_RenderPresent(rendu);
        return AFFICHAGE_JOUEUR_REUSSI;
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

int effacer_ancienne_position_joueur(SDL_Renderer* rendu, SDL_Point* ancienne_position_joueur){
    SDL_Rect joueur;

    // si le pointeur renderer est invalide ou la position_joueur :
    if((rendu == NULL) || (ancienne_position_joueur == NULL)){
        printf("Erreur : le pointeur du rendu ou de la position joueur est null\n");
        return ERREUR_RENDERER_POSITION;
    }
    else{
        joueur.h = TAILLE_JOUEUR;
        joueur.w = TAILLE_JOUEUR;
        joueur.x = PAS_DU_JOUEUR_PIXEL* ancienne_position_joueur->x;
        joueur.y = PAS_DU_JOUEUR_PIXEL* ancienne_position_joueur->y;

        COULEUR_NOIRE(rendu);
        SDL_RenderFillRect(rendu,&joueur);
        //SDL_RenderPresent(rendu);
        return SUPPRIPRESSION_ANCIENNE_POSITION_JOUEUR_REUSSI;
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

int sauvegarder_ancienne_position(SDL_Point* position_joueur, SDL_Point* ancienne_position_joueur){

    if((position_joueur == NULL) || (ancienne_position_joueur == NULL)){
        printf("Echec de sauvegarde de l'ancienne position du joueur \n");
        return ECHEC_DE_SAUVEGARDE;
    }
    else{
        ancienne_position_joueur->x = position_joueur->x;
        ancienne_position_joueur->y = position_joueur->y;
        return POSITION_SAUVEGARDEE_AVEC_SUCCES;
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

int tracer_effacer_un_rayon(SDL_Renderer* rendu, SDL_Point* origine, SDL_Point* extremite, int mode){
    if((rendu == NULL) || (origine == NULL) || (extremite == NULL)){
        printf("Erreur : les pointeurs arguments sont pas valides dans la fonction tracer_effacer_un_rayon \n");
        return ECHEC_DESSIN;
    }
    else{
        if(mode == DESSIN_RAYON){
            COULEUR_VERTE(rendu);
        }
        else if(mode == EFFACEMENT_RAYON){
            COULEUR_NOIRE(rendu);
        }
        else{
            printf("Erreur : veuillez specifier le mode soit pour tracer, soit pour effacer un rayon : \n");
            return ECHEC_DESSIN;
        }
        
        SDL_RenderDrawLine(rendu,origine->x * TAILLE_JOUEUR +TAILLE_JOUEUR/2,origine->y * TAILLE_JOUEUR+TAILLE_JOUEUR/2,extremite->x,extremite->y);
        SDL_RenderPresent(rendu);
        return DESSIN_REUSSI;
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

int dessiner_ou_supprimer_vision_joueur(SDL_Renderer* rendu, SDL_Point* origine, int debut_vision, int mode){
    SDL_Point extremite_rayon;
    int angle;

    if((rendu == NULL) || (origine == NULL)){
        printf("Erreur : les pointeurs arguments sont pas valides dans la fonction dessiner_vision_joueur \n");
        return ECHEC_DESSIN;
    }
    else{
            for(angle = debut_vision; angle < (debut_vision + ANGLE_SPECTRE_VISION); angle += INCREMENTATION_ANGLE){
                extremite_rayon.x = origine->x + TAILLE_JOUEUR/2 + 100*(float)cosl(conversion_radian_angle(angle));
                extremite_rayon.y = origine->y + TAILLE_JOUEUR/2 + 100*(float)sinl(conversion_radian_angle(angle));

                tracer_effacer_un_rayon(rendu,origine,&extremite_rayon,mode);
            }
        return DESSIN_REUSSI;
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

double conversion_radian_angle(int angle_degre){
    double angle_randian = angle_degre * M_PI/PI_DEGRE;
    return angle_randian;
}

/*-------------------------------------------------------------------------------------------------------------*/