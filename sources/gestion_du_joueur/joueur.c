#include "joueur.h"


/*-------------------------------------------------------------------------------------------------------------*/
int deplacer_joueur(SDL_Event evenement, int** map, int nb_lignes, int nb_colonnes, SDL_Point* position_joueur){

    // si le pointeur evenement est invalide :
    if((map == NULL) || (position_joueur == NULL)){
        printf("Erreur : au moins un des argument de cette fonction est NULL :\n");
        return ERREUR_EVENEMENT;
    }
    else if(evenement.type == SDL_KEYDOWN) {
        // sinon si tout est correct:
        switch (evenement.key.keysym.sym)
        {
        case SDLK_LEFT:
            printf("le joueur est allee vers l'avant\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            // verification de la matrice pour eviter des erreurs de segmentation :
            if(position_joueur->x > INDICE_MIN){
                // si le joueur peut se déplacer vers le haut ou vers l'avant :
                if(map[position_joueur->y][position_joueur->x - PAS_DU_JOUEUR_MAP] != OBSTACLE){
                    position_joueur->x--;
                    
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
                    position_joueur->x++;
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;

        case SDLK_UP:
            printf("le joueur est allee vers la gauche\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if(position_joueur->y >= PAS_DU_JOUEUR_MAP){
                // si le joueur se dirige vers la gauche: 
                if(map[position_joueur->y - PAS_DU_JOUEUR_MAP][position_joueur->x] != OBSTACLE) {
                    position_joueur->y--;
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;
        case SDLK_DOWN:
            printf("le joueur est allee vers la droite\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if((position_joueur->y + PAS_DU_JOUEUR_MAP) < nb_lignes){
                // si le joueur se dirige vers la droite :
                if(map[position_joueur->y + 1][position_joueur->x] != OBSTACLE){
                    position_joueur->y++;
                    return JOUEUR_A_BOUGE;
                }
            }
            
            break;
        
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
        //SDL_RenderPresent(rendu);
        return AFFICHAGE_JOUEUR_REUSSI;
    }
}