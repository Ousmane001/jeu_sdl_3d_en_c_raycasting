
#include <B.h>

int main(int nbarg, char** argv){

    //Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)==-1){
        SDL_Log("Erreur : Impossible de charger la SDL2 en mémoire > %s\n",SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    //Fenetre et rendu
    SDL_Window* fenetre=NULL;
    
    fenetre=SDL_CreateWindow("DOOM",5,5,800,400,0);
    InitialisationM();
    Mix_Music** m=NULL;
    m=malloc(2*sizeof(Mix_Music*));
    m[0]=loadM("sons/kahoot.mp3");
    m[1]=loadM("sons/kahoot.mp3");
    jouerM(m[0],-1);
    
    //boucle de jeu
    SDL_bool continuer = SDL_TRUE;
    while(continuer){

        SDL_Event event;

        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                    break;
                default:
                break;
            }
        }

    }

    SDL_DestroyWindow(fenetre);
    liberation_des_musiques(m,2);
    SDL_Quit();
    return EXIT_SUCCESS;
}