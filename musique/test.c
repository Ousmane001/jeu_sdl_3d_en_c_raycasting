
#include "B.h"
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
    
    //variable de sons
    int volume=MIX_MAX_VOLUME/2;
    int volume2=MIX_MAX_VOLUME/2;
    int numCanal=1;
    
    //init 
    InitialisationM();
    
    //load
    Mix_Music* M1=NULL;
    M1=loadM("sons/kahoot.mp3");
    
    //Canal
    initialisationCanal(numCanal,volume2);
    Mix_Chunk* C1=NULL;
    C1=loadChunk("sons/pyke.wav");
    
    //jouerM(M1,-1);
    jouerM(M1,-1);
    //boucle de jeu
    SDL_bool continuer = SDL_TRUE;
    
   
    int a=0;
    while(continuer){

        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch(event.type){
            	
                case SDL_QUIT:
                    continuer = SDL_FALSE;
                break;
           
            }
            if(a==0){
                operationMusique(0,volume);
            }
            a=a+1;
            if(a==40)
                operationMusique(0,volume);
            if(a==10)
                jouerC(1,C1,0);
        }
        Mix_Volume(numCanal,volume2);
        Mix_VolumeMusic(volume);
    }
    Mix_FreeMusic(M1);
    Mix_FreeChunk(C1);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    SDL_Quit();
    return EXIT_SUCCESS;
   
}
