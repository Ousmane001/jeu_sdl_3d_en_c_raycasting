#include "game.h"

//gcc ../sources/game/main.c ../sources/gestion_du_joueur/joueur.c ../sources/game/game.c ../sources/gestion_du_map/map.c -I include -L lib -lmingw32 -lSDL2main -lSDL2 -o  bin/prog

int main(int argc, char* argv[]){
    printf("debut du test de fenetre\n\n");

    int** map = NULL;
    int i,j,nb_ligne,nb_colonne, debut_vision = 0, ancienne_debut_vision;
    SDL_Point joueur, ancienne_position, extremite_rayon,position_centre_joueur =  {0,0};

    joueur.x =1;
    joueur.y =1;
    
    ancienne_position.x = joueur.x;
    ancienne_position.y = joueur.y;

    if(scanner_une_map(FICHIER_MAP,&nb_ligne,&nb_colonne) != MAP_CORRECT){
    printf("map incorrect\n");
  }
  else{
    printf("map correct\n");
    printf("dimension -> %d x %d\n",nb_ligne,nb_colonne);
    if(allouer_une_map_correcte(&map,nb_ligne,nb_colonne) != MATRICE_CREEE){
      printf("erreur d'allocation\n");
    
    }
    else{
      printf("allocation correcte\n");
      
      if(charger_une_map(FICHIER_MAP,map) != MATRICE_CHARGEE_AVEC_SUCCES){
        printf("erreur de chargement\n");
      
      }
      else{
        printf("chargement effectuee avec succes\n");
      }
        
    }
  }
    

    // initialisation de la sdl :
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Window* fenetre = NULL;
    SDL_Renderer* rendu = NULL;
    SDL_Event evenement;
    SDL_bool program_launched = SDL_TRUE;

    

    // creation de la fenetre et du rendu :
    if(SDL_CreateWindowAndRenderer(LONGUEUR_FENETRE, LARGEUR_FENETRE, SDL_WINDOW_ALWAYS_ON_TOP , &fenetre, &rendu) != 0){
        printf("Erreur de creation de la fenetre plein ecran et du rendu -> %s\n",SDL_GetError());
    }
    
    // gestion d'evenement:
    if(afficher_une_map(rendu,map,nb_ligne,nb_colonne,0,0) != MAP_AFFICHEE_AVEC_SUCCES){
      printf("erreur d'affichage de la map\n");
    }
    else{
      afficher_joueur(rendu,&joueur);
      position_du_centre(&joueur,&position_centre_joueur);
      chercher_extremite_rayon(&position_centre_joueur,85,&extremite_rayon,map);
      tracer_effacer_un_rayon(rendu,&position_centre_joueur,&extremite_rayon,DESSIN_RAYON);
      SDL_RenderPresent(rendu);
      printf("map bien affichee \n");
    }
    while(program_launched){
        while(SDL_PollEvent(&evenement)){
            switch (evenement.type)
            {
              case SDL_QUIT:
                // s'il decide de fermet le jeu :
                program_launched = SDL_FALSE;
                break;
              
              case SDL_KEYDOWN: 
                afficher_une_map(rendu,map,nb_ligne,nb_colonne,0,0);
                ancienne_debut_vision = debut_vision;
                if(deplacer_joueur(evenement,map,nb_ligne,nb_colonne,&joueur,&ancienne_position,&debut_vision) == JOUEUR_A_BOUGE){


                  effacer_ancienne_position_joueur(rendu,&ancienne_position);
                  //tracer_effacer_un_rayon(rendu,&position_centre_joueur,&extremite_rayon,EFFACEMENT_RAYON);
                  //dessiner_ou_supprimer_vision_joueur(rendu,&ancienne_position,ancienne_debut_vision,EFFACEMENT_RAYON);


                  afficher_joueur(rendu,&joueur);
                  //dessiner_ou_supprimer_vision_joueur(rendu,&joueur,debut_vision,DESSIN_RAYON);
                  position_du_centre(&joueur,&position_centre_joueur);
                  
                  
                  chercher_extremite_rayon(&position_centre_joueur,85,&extremite_rayon,map);
                  tracer_effacer_un_rayon(rendu,&position_centre_joueur,&extremite_rayon,DESSIN_RAYON);
                  printf("\n\n les extremite trouvees sont x = %d et y = %d \n\n",extremite_rayon.x,extremite_rayon.y);
                 // tracer_effacer_un_rayon(rendu,&position_centre_joueur,&extremite_rayon,DESSIN_RAYON);
                  


                } 

              default:
                break;
            }
            
            

        }
    }




  // fermeture convenable du jeu avec liberation adequate : 

    if(detruire_une_map(&map,nb_ligne) != MAP_DETRUITE_AVEC_SUCCES){
      printf("erreur de liberation de la memoire du map \n");
    }
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    
    printf("\nfin du test\n");


    return 0;
}