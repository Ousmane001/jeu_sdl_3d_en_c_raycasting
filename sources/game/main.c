#include "game.h"

//gcc ../sources/game/main.c ../sources/gestion_du_joueur/joueur.c ../sources/game/game.c ../sources/gestion_du_map/map.c -I include -L lib -lmingw32 -lSDL2main -lSDL2 -o  bin/prog

int main(int argc, char* argv[]){
    printf("debut du test de fenetre\n\n");

    int** map = NULL;
    int i,j,nb_ligne,nb_colonne;
    SDL_Point joueur;
    joueur.x =2;
    joueur.y =2;

    if(scanner_une_map("../sources/gestion_du_map/fichier_map.csv",&nb_ligne,&nb_colonne) != MAP_CORRECT){
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
      
      if(charger_une_map("../sources/gestion_du_map/fichier_map.csv",map) != MATRICE_CHARGEE_AVEC_SUCCES){
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
    if(afficher_une_map(rendu,map,nb_ligne,nb_colonne,30,30) != MAP_AFFICHEE_AVEC_SUCCES){
      printf("erreur d'affichage de la map\n");
    }
    else{
      afficher_joueur(rendu,&joueur);
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
                //sinon : 
                  if(deplacer_joueur(evenement,map,nb_ligne,nb_colonne,&joueur) != JOUEUR_NE_BOUGE_PAS){
                    afficher_une_map(rendu,map,nb_ligne,nb_colonne,30,30);
                    afficher_joueur(rendu,&joueur);
                    SDL_RenderPresent(rendu);
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