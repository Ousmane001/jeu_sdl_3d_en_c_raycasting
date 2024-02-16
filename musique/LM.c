#include "B.h"

//Initialisation
void InitialisationM(){
    //44100 = qualite du son   1024 = taux d'echantillonage
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 1024)!=0){
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return;
}

void initialisationCanal(int numCanal,int volume){
    if(Mix_AllocateChannels(numCanal)!=numCanal){
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    Mix_Volume(numCanal,volume);
    return;
}

//p est le chemin vers un fichier .mp3
Mix_Music* loadM(char* p){

    Mix_Music* musique=NULL;
    musique = Mix_LoadMUS(p);
    if(musique==NULL){
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return musique;
}

//p est le chemin vers un fichier .wav
Mix_Chunk * loadChunk(char * p){
    Mix_Chunk* chunk;
    chunk=Mix_LoadWAV(p);
    if(chunk==NULL){
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return chunk;
}

void jouerC(int numCanal,Mix_Chunk* chunk,int tour){
    if(Mix_PlayChannel(numCanal-1, chunk, tour)!=0){
        Mix_FreeChunk(chunk);
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void jouerM(Mix_Music* musique,int tour){
    //tour = nombre de repetition | -1 = infini | 0 = 1 tour | 1 = 2 tour
    if(Mix_PlayMusic(musique,tour)!=0){
        Mix_CloseAudio();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return;
}


///Mix_CloseAudio();
///SDL_Quit();
