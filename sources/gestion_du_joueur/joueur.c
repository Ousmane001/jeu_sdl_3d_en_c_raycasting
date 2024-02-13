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
            //printf("le joueur est allee vers l'avant\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            // verification de la matrice pour eviter des erreurs de segmentation :
            if(position_joueur->x > INDICE_MIN){
                // si le joueur peut se déplacer vers le haut ou vers l'avant :
                if(map[position_joueur->y][position_joueur->x - PAS_DU_JOUEUR_MAP] == ESPACE_VIDE){
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
            //printf("le joueur est allee vers l'arriere\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            
            // verification de la matrice pour eviter des erreurs de segmentation :
            if((position_joueur->x + PAS_DU_JOUEUR_MAP) < nb_colonnes){
                // si le joueur veut reculer :
                if(map[position_joueur->y][position_joueur->x + PAS_DU_JOUEUR_MAP] == ESPACE_VIDE){
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
            //printf("le joueur est allee vers la gauche\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if(position_joueur->y >= PAS_DU_JOUEUR_MAP){
                // si le joueur se dirige vers la gauche: 
                if(map[position_joueur->y - PAS_DU_JOUEUR_MAP][position_joueur->x] == ESPACE_VIDE) {
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
            //printf("le joueur est allee vers la droite\nmatrice[%d][%d] = %d\n",position_joueur->x,position_joueur->y,map[position_joueur->y][position_joueur->x]);
            if((position_joueur->y + PAS_DU_JOUEUR_MAP) < nb_lignes){
                // si le joueur se dirige vers la droite :
                if(map[position_joueur->y + 1][position_joueur->x] == ESPACE_VIDE){
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
            //printf("le joueur tourne la tete vers la gauche .\n");
            *debut_vision += INCREMENTATION_VISION;

            if(*debut_vision >= 2*PI_DEGRE){
                *debut_vision -= 2*PI_DEGRE;
            }
            return JOUEUR_A_BOUGE;
        case SDLK_d :
           // printf("le joueur tourne la tete vers la droite .\n");
           printf("avant --> %d    ",*debut_vision);
            *debut_vision -= INCREMENTATION_VISION;
            printf("entre  --> %d    ",*debut_vision);
            if(*debut_vision < ANGLE_NULL){
                *debut_vision += 2*PI_DEGRE;
            }
            printf("fin  --> %d    ",*debut_vision);

            return JOUEUR_A_BOUGE;
        default:
           // printf("le default est active\n");
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
        joueur.y = PAS_DU_JOUEUR_PIXEL* position_joueur->y + DECALAGE;

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
        joueur.y = PAS_DU_JOUEUR_PIXEL* ancienne_position_joueur->y + DECALAGE;

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
        
        SDL_RenderDrawLine(rendu,origine->x,origine->y + DECALAGE,extremite->x,extremite->y + DECALAGE);
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

int position_du_centre(SDL_Point* position, SDL_Point*  position_du_centre){
    
    if((position == NULL) || (position_du_centre == NULL)){
        printf("Erreur: les positions envoyees en argument de la fonction position_du_centre sont non valides\n");
        return ECHEC_POSITION;
    }
    else{
        position_du_centre->x = position->x*TAILLE_JOUEUR + TAILLE_JOUEUR/2;
        position_du_centre->y = position->y*TAILLE_JOUEUR + TAILLE_JOUEUR/2;
        return POSITION_SUCCES;
    }
    
}

/*-------------------------------------------------------------------------------------------------------------*/

int incrementer_ou_decrementer_une_coordonnee(int coordonnee, int mode){
    while(coordonnee % TAILLE_JOUEUR != COORDONNEE_DECREMENTEE){
        if(mode == DECREMENTATION)
            coordonnee--;
        else if (mode == INCREMENTATION)
            coordonnee++;
        else{
            printf("veuillez choisir votre mode : soit une INCREMENTATION ou soit un DECREMENTATION\n");
            printf("Arret du programme ! changez votre mode et reessayer !\n");
            exit(EXIT_FAILURE);
        }
    }
    return coordonnee;
}

/*-------------------------------------------------------------------------------------------------------------*/

int est_ce_un_mur(int coordonnee_x, int coordonnee_y, int** map){

    if((map == NULL)){
        printf("Erreur: map non valide dans la fonction est_ce_un_mur\nArret automatique du programme\n");
        exit(EXIT_FAILURE);
    }
    else{
        coordonnee_x = coordonnee_x/TAILLE_JOUEUR;
        coordonnee_y = coordonnee_y/TAILLE_JOUEUR;
        //printf("coordonnee_x = %d et coordonnee_y = %d\n",coordonnee_x,coordonnee_y);
        //printf("il s'agit du map[%d][%d] = %d\n",(coordonnee_x/TAILLE_JOUEUR),(coordonnee_y/TAILLE_JOUEUR),map[(coordonnee_x/TAILLE_JOUEUR)][(coordonnee_y/TAILLE_JOUEUR)]);
        if(map[coordonnee_y][coordonnee_x] != ESPACE_VIDE){
            return OUI;
        }
        else{
            return NON;
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------*/

int intersection_verticale(int coordonnee_x, int angle){
    int coordonnee_y = ABS(((double)coordonnee_x*tanl(conversion_radian_angle(angle))));
    //printf("l'intersection a donne en y -> %d\n",coordonnee_y);
    return coordonnee_y;
}

/*-------------------------------------------------------------------------------------------------------------*/

int intersection_horizontale(int coordonnee_y, int angle){
    int coordonnee_x =  ABS(((double)coordonnee_y/tanl(conversion_radian_angle(angle))));
    //printf("l'intersection a donne en x -> %d\n",coordonnee_x);
    return coordonnee_x;
}

/*-------------------------------------------------------------------------------------------------------------*/

int est_une_intersection(int coordonnee_x, int coordonnee_y){
    if(coordonnee_x % TAILLE_JOUEUR == OUI){
        //printf("intersection verticale\n");
        return INTERSECTION_VERTICALE;
    }
    else if(coordonnee_y % TAILLE_JOUEUR == OUI){
       // printf("intersection horizontale\n");
        return INTERSECTION_HORIZONTALE;
    }
    else{
        return NON;
    }

}
/*-------------------------------------------------------------------------------------------------------------*/

int calculer_distance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

/*-------------------------------------------------------------------------------------------------------------*/

int chercher_extremite_rayon(SDL_Point* position, int angle, SDL_Point* extremite, int** map, int* distances){
    int compteur_intersection = 0, save_position;
    float dx = CENTRE,dy = CENTRE,coeff_dir = CENTRE;

    if((position == NULL) || (extremite == NULL) || (map == NULL)){
        printf("Erreur : position joueur ou extremite ou map invalide dans chercher_extremite_rayon() .\n");
        return ECHEC_POSITION;
    }
    else{
        // initialisation de point extremite du rayon :
        extremite->x = position->x;
        extremite->y = position->y;
        // selon l'angle, donc selon le cadran trigonometrique, on applique l'algorithme qu'on a developpé :

        switch (angle)
        {
        case ANGLE_NULL:
            while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION){
                // si le rayon n'a pas encore bougé :
                if((dx == CENTRE) && (dy == CENTRE)){
                    dx += TAILLE_JOUEUR/2;
                }
                else{
                    dx += TAILLE_JOUEUR;
                }
                // verification de s'il on hurte un mur ou pas avec les bonnes coordonnees :
                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee((extremite->x + dx + TAILLE_JOUEUR), DECREMENTATION),incrementer_ou_decrementer_une_coordonnee(extremite->y + dy, DECREMENTATION),map) == OUI){
                    return POSITION_SUCCES;
                }
            }
            break;
        case PI_DEGRE:
            while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION){
                // si le rayon n'a pas encore bougé :
                if((dx == CENTRE) && (dy == CENTRE)){
                    dx -= TAILLE_JOUEUR/2;
                }
                else{
                    dx -= TAILLE_JOUEUR;
                }
                // verification de s'il on hurte un mur ou pas avec les bonnes coordonnees :
                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee((extremite->x + dx - TAILLE_JOUEUR),DECREMENTATION),incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                    return POSITION_SUCCES;
                }
            }
            break;

        case PI_SUR_2:
            while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION){
                // si le rayon n'a pas encore bougé :
                if((dx == CENTRE) && (dy == CENTRE)){
                    dy -= TAILLE_JOUEUR/2;
                }
                else{
                    dy -= TAILLE_JOUEUR;
                }
                // verification de s'il on hurte un mur ou pas avec les bonnes coordonnees :
                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee((extremite->y + dy - TAILLE_JOUEUR),DECREMENTATION),map) == OUI){
                    return POSITION_SUCCES;
                }
            }
            break;
        case PI_DEGRE+PI_SUR_2:
            while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION){
                // si le rayon n'a pas encore bougé :
                if((dx == CENTRE) && (dy == CENTRE)){
                    dy += TAILLE_JOUEUR/2;
                }
                else{
                    dy += TAILLE_JOUEUR;
                }
                // verification de s'il on hurte un mur ou pas avec les bonnes coordonnees :
                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee((extremite->y + dy + TAILLE_JOUEUR),DECREMENTATION),map) == OUI){
                    return POSITION_SUCCES;
                }
            }
            break;

        default:
            
            // si l'angle est le premier cadran
            if(angle < PI_SUR_2){
                // si en plus il est inferieur a 45°:
                if(angle < PI_SUR_4){
                    coeff_dir = (float)tanl(conversion_radian_angle(angle));
                    while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION){
                        // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                        if((dx == CENTRE) && (dy == CENTRE)){
                            dx += TAILLE_JOUEUR/2;
                            dy -= dx*(float)tanl(conversion_radian_angle(angle));
                        }
                        else{
                            dx++;
                            dy-= coeff_dir;
                        }

                        // on verifie s'il le rayon intersecte un mur ou pas:
                        if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                            if(est_ce_un_mur(extremite->x + dx,incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                        else if(est_une_intersection(extremite->x + dx,extremite->y + dy) == INTERSECTION_HORIZONTALE){
                            if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee(extremite->y + dy-TAILLE_JOUEUR,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }

                       
                    }
                    extremite->x += dx;
                    extremite->y += dy;
                }
                else{
                    // si l'angle est compris entre 45° et 90°:
                    coeff_dir = (float)tanl(conversion_radian_angle(PI_SUR_2 - angle));
                    while((*distances = calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy))) < PORTEE_VISION && (abs(dy) < extremite->y-TAILLE_MUR)){
                        // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                        if((dx == CENTRE) && (dy == CENTRE)){
                            dy -= TAILLE_JOUEUR/2;
                            dx += abs(dy)*(float)tanl(conversion_radian_angle(PI_SUR_2 - angle));
                        }
                        else{
                            dy--;
                            dx += coeff_dir;
                        }
                        // on verifie s'il le rayon intersecte un mur ou pas:
                        if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                            if(est_ce_un_mur(extremite->x + dx,incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                        else if(est_une_intersection(extremite->x + dx,extremite->y + dy) == INTERSECTION_HORIZONTALE){
                            if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee(extremite->y + dy -TAILLE_JOUEUR,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }

                    }
                    extremite->x += dx;
                    extremite->y += dy;
                }
            }
            else{
                // si l'angle fait partie du 2em cadran :
                // et si enplus il est compris entre 90° et 135°
                if(angle < PI_SUR_2 + PI_SUR_4){
                    coeff_dir = (float)tanl(conversion_radian_angle(angle - PI_SUR_2));
                    while((calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) < PORTEE_VISION) && (abs(dy) < extremite->y-TAILLE_MUR)&& (abs(dx) < extremite->x-TAILLE_MUR)){
                        // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                        if((dx == CENTRE) && (dy == CENTRE)){
                            dy -= TAILLE_JOUEUR/2;
                            dx -= dy*(float)tanl(conversion_radian_angle(angle - PI_SUR_2));
                        }
                        else{
                            dy--;
                            dx -= coeff_dir;
                        }

                        // on verifie s'il le rayon intersecte un mur ou pas:
                        if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                            if(est_ce_un_mur(extremite->x + dx -TAILLE_JOUEUR,incrementer_ou_decrementer_une_coordonnee( extremite->y + dy,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                        else if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_HORIZONTALE){
                            if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee( extremite->y + dy -TAILLE_JOUEUR,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                    }
                    extremite->x += dx;
                    extremite->y += dy;
                }
                else{
                    if(angle < PI_DEGRE){
                    // si l'angle est dans la 2em moitier du 2iem cadran :
                    coeff_dir = (float)tanl(conversion_radian_angle(PI_DEGRE - angle));
                    while((calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) < PORTEE_VISION) && (abs(dy) < extremite->y-TAILLE_MUR)&& (abs(dx) < extremite->x-TAILLE_MUR)){
                        // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                        if((dx == CENTRE) && (dy == CENTRE)){
                            dx -= TAILLE_JOUEUR/2;
                            dy -= dx*(float)tanl(conversion_radian_angle(PI_DEGRE - angle));
                        }
                        else{
                            dx--;
                            dy -= coeff_dir;
                        }

                        // on verifie s'il le rayon intersecte un mur ou pas:
                        if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                            if(est_ce_un_mur(extremite->x + dx -TAILLE_JOUEUR,incrementer_ou_decrementer_une_coordonnee( extremite->y + dy,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                        else if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_HORIZONTALE){
                            if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee( extremite->y + dy -TAILLE_JOUEUR,DECREMENTATION),map) == OUI){
                                extremite->x += dx;
                                extremite->y += dy;
                                return POSITION_SUCCES;
                            }
                        }
                    }
                    extremite->x += dx;
                    extremite->y += dy;
                    }
                }
            }
            // 3em et 4iem quadran
            if(angle > PI_DEGRE){
                // si l'angle est dans le 3iem cadran 
                if(angle < PI_DEGRE + PI_SUR_2){
                    // et s'il s'agit de la premiere partie du cadran 3
                    if(angle < PI_DEGRE + PI_SUR_4){
                        coeff_dir = (float)tanl(conversion_radian_angle(angle - PI_DEGRE));
                        while((calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) < PORTEE_VISION) && (abs(dx) < extremite->x - TAILLE_MUR) ){
                            // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                            if((dx == CENTRE) && (dy == CENTRE)){
                                dx -= TAILLE_JOUEUR/2;
                                dy += abs(dx) * (float)tanl(conversion_radian_angle(angle - PI_DEGRE));
                            }
                            else{
                                dx--;
                                dy += coeff_dir;
                            }

                            // on verifie s'il le rayon intersecte un mur ou pas:
                            if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                                if(est_ce_un_mur(extremite->x + dx - TAILLE_JOUEUR,incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                    extremite->x += dx;
                                    extremite->y += dy;
                                    return POSITION_SUCCES;
                                }
                            }
                            else if(est_une_intersection(extremite->x + dx,extremite->y + dy) == INTERSECTION_HORIZONTALE){
                                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                    extremite->x += dx;
                                    extremite->y += dy;
                                    return POSITION_SUCCES;
                                }
                            }
                        }
                        extremite->x += dx;
                        extremite->y += dy;
                    }
                    else if(angle < PI_DEGRE + PI_SUR_2){
                        // sinon s'il est dans sa 2em partie
                        printf("2em partie\n");
                        coeff_dir = (float)tanl(conversion_radian_angle((PI_DEGRE + PI_SUR_2) - angle));
                        while((calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) <= PORTEE_VISION) && ((extremite->x + dx) >= TAILLE_MUR) ){
                            // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                            if((dx == CENTRE) && (dy == CENTRE)){
                                dy += TAILLE_JOUEUR/2;
                                dx -= dy*(float)tanl(conversion_radian_angle(PI_DEGRE + PI_SUR_2 - angle));
                            }
                            else{
                                dy++;
                                dx -= coeff_dir;
                            }
                            // on verifie s'il le rayon intersecte un mur ou pas:
                            if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                                if(est_ce_un_mur(extremite->x + dx ,incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                    extremite->x += dx;
                                    extremite->y += dy;
                                    return POSITION_SUCCES;
                                }
                            }
                            else if(est_une_intersection(extremite->x + dx,extremite->y + dy) == INTERSECTION_HORIZONTALE){
                                if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION), extremite->y + dy, map) == OUI){
                                    extremite->x += dx;
                                    extremite->y += dy;
                                    return POSITION_SUCCES;
                                }
                            }
                        }
                        extremite->x += dx;
                        extremite->y += dy;
                        
                    }

                }
                else{
                    // sinon si l'angle est dans le 4iem cadran
                        if(angle < (PI_DEGRE + PI_SUR_2 + PI_SUR_4)){

                            //s'il s'agit de la premiere partie :
                            coeff_dir = (float)tanl(conversion_radian_angle(angle - (PI_DEGRE + PI_SUR_2)));
                            while(calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) < PORTEE_VISION){
                                // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                                
                                if((dx == CENTRE) && (dy == CENTRE)){
                                    dy = TAILLE_JOUEUR/2;
                                    dx = (float)(TAILLE_JOUEUR/2)*(float)tanl(conversion_radian_angle(angle - (PI_DEGRE + PI_SUR_2)));
                                    save_position = dy;
                                }
                                else{
                                    dy++;
                                    dx += coeff_dir;
                                    save_position = dy;
                                }

                                // on verifie s'il le rayon intersecte un mur ou pas:
                                if(est_une_intersection(extremite->x+dx,extremite->y+dy) == INTERSECTION_VERTICALE){
                                    if(est_ce_un_mur(extremite->x+dx,incrementer_ou_decrementer_une_coordonnee(extremite->y+dy,DECREMENTATION),map) == OUI){
                                        extremite->x += dx;
                                        extremite->y += dy;
                                        return POSITION_SUCCES;
                                    }
                                }
                                else if(est_une_intersection(extremite->x+dx,extremite->y+dy) == INTERSECTION_HORIZONTALE){
                                    if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x+dx,DECREMENTATION),extremite->y+dy,map) == OUI){
                                        extremite->x += dx;
                                        extremite->y += dy;
                                        return POSITION_SUCCES;
                                    }
                                }
                            }
                            extremite->x += dx;
                            extremite->y += dy;
                        }
                        else{

                            // si en plus c'est sur la derniere partie du quadrant
                            coeff_dir = (float)tanl(conversion_radian_angle(2*PI_DEGRE - angle));
                            while(calculer_distance((extremite->x),(extremite->y),(extremite->x + dx),(extremite->y + dy)) < PORTEE_VISION){
                                // si le rayon n'a pas encore bouge alors on le lance a l'exterieur du rectangle joueur :
                                if((dx == CENTRE) && (dy == CENTRE)){
                                    dx += TAILLE_JOUEUR/2;
                                    dy += (float)(TAILLE_JOUEUR/2)*(float)tanl(conversion_radian_angle(2*PI_DEGRE - angle));
                                    save_position = dx;
                                }
                                else{
                                    dx++;
                                    dy += coeff_dir;
                                    save_position = dx;
                                }

                                // on verifie s'il le rayon intersecte un mur ou pas:
                                if(est_une_intersection(extremite->x + dx, extremite->y + dy) == INTERSECTION_VERTICALE){
                                    if(est_ce_un_mur(extremite->x + dx,incrementer_ou_decrementer_une_coordonnee(extremite->y + dy,DECREMENTATION),map) == OUI){
                                        extremite->x += dx;
                                        extremite->y += dy;
                                        return POSITION_SUCCES;
                                    }
                                }
                                else if(est_une_intersection(extremite->x + dx,extremite->y + dy) == INTERSECTION_HORIZONTALE){
                                    if(est_ce_un_mur(incrementer_ou_decrementer_une_coordonnee(extremite->x + dx,DECREMENTATION),extremite->y + dy,map) == OUI){
                                        extremite->x += dx;
                                        extremite->y += dy;
                                        return POSITION_SUCCES;
                                    }
                                }
                            }
                            extremite->x += dx;
                            extremite->y += dy;

                        }
                        
                    

                }

            }
            break;
        }
    }
}

/*-------------------------------------------------------------------------------------------------------------*/