#include "B.h"



//p est le chemin vers un fichier .mp3
Mix_musique* loadM(char* p){

    Mix_Music* musique=NULL;
    musique = Mix_LoadMUS(p);
    if(musique==NULL){
        erreur_sdlm("Impossible de charger la musique",musique);
    }
    return musique;
}

void InitialisationM(){
    //44100 = qualite du son   1024 = taux d'echantillonage
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 1024)!=0){
        erreur_sdlm("Impossible de charger la sdl_mixer",NULL,NULL);
    }
    return;
}

void liberation_des_musiques(Mix_Music** musique,unsigned int nb_musique){
    for(int i=0;i<nb_musique;i++){
        Mix_FreeMusic(musique[i]);
    }
    Mix_CloseAudio();
    return;
}

void jouerM(Mix_Music* musique,int tour){
    //tour = nombre de repetition | -1 = infini | 0 = 1 tour | 1 = 2 tour
    if(Mix_PlayMusic(musique,tour)!=0){
        erreur_sdlm("Impossible de lancer la musique", musique,NULL);
    }
    return;
}

void initialisationCanal(int canal){
    if(Mix_AllocateChannels(canal)!=canal){
        erreur_sdlm("Impossible de d initialiser le canal", musique,NULL);
    }
    Mix_Volume(canal,MIX_MAX_VOLUME/2);
    return;
}

//p est le chemin vers un fichier .wav
Mix_Chunk * loadChunk(char * p){
    chunk=Mix_LoadWAV(p);
    if(chunk==NULL){
        erreur_sdlm("Impossible de changer l effet sonore", NULL,chunk);
    }

}

//Besoin d un int volume | int canal est le numero du canal | canal = -1 signifie tous les canaux
//a mettre dans la boucle de jeu
void enjeuM(int volume,int volume2,Mix_Music* musique,Mix_ chunk,int canal){
    switch(event.key.keysym.sym){
        //pause unpause
        case SDLK_p:
            if(Mix_PausedMusic()==1){
                Mix_ResumeMusic();
            }
            else{
                Mix_PauseMusic();
            }
        break;

        //rewind
        case SDLK_r:
            Mix_RewindMusic();
        break;

        //arret
        case SDLK_s:
            Mix_HaltMusic();
        break;

        //baisse du volume
        case SDLK_2:
            if(volume > 0){
                volume--;
            }
        break;

        //augmentation du volume
        case SDLK_2:
            if(volume < MIX_MAX_VOLUME){
                volume++;
            }
        break;

        //jouer un effet sonore
        case SDLK_SPACE:
            if(Mix_PlayChannel(canal, chunk[0], 0)!=0){
                erreur_sdlm("Impossible de lancer l effet sonore",musique,chunk)
            }
        break;

        //arret du canal
        case SDLK_o:
            Mix_HaltChannel(canal);
        break;

        //pause unpause du canal
        case SDLK_j:
            if(Mix_Paused(canal)==1){
                Mix_Resume(canal);
            }
            else if(Mix_Playing(canal)==1){
                Mix_Pause(canal);
            }
        break;

        case SDLK_y:
            if(volume2>0){
                volume2--;
            }
        break;

        case SDLK_e:
            if(volume2<MIX_MAX_VOLUME){
                volume2++;
            }
        break;
        default:
        continue;
    }
    Mix_Volume(canal,volume2)
    Mix_VolumeMusic(volume);
    return;
}

void closemusic(Mix_Music** musique,Mix_Chunk** chunk){

    for(int i=0;i<nb_musique;i++){
        Mix_FreeMusic(musique[i]);
    }
    for(int i=0;i<nb_chunk;i++){
        Mix_FreeMusic(chunk[i]);
    }
    Mix_CloseAudio();
    return;
}

void erreur_sdlm(const char * message,Mix_Music* musique,Mix_Chunk* chunk){
    SDL_Log("Erreur : %s %s> %s",message, SDL_GetError());
    if (musique != NULL)
        Mix_FreeMusic(musique);
    if (chunk != NULL)
        Mix_FreeChunk(chunk);

    Mix_CloseAudio();
    SDL_Quit();
    exit(EXIT_FAILURE);
}