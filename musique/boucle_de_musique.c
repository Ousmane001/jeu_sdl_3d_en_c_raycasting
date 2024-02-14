#include "B.h"

//Besoin d un int volume | int canal est le numero du canal | canal = -1 signifie tous les canaux
//a mettre dans la boucle de jeu apres "case SDL_KEYDOWN"
void enjeuM(int volume,int volume2,Mix_Music* musique,Mix_Chunk* chunk,int canal,SDL_Event event){
    switch(event.key.keysym.sym){
        
        //jouer un effet sonore
        case SDLK_SPACE:
            if(Mix_PlayChannel(canal, chunk, 0)!=0){
                
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
        break;
    }
    Mix_Volume(canal,volume2);
    Mix_VolumeMusic(volume);
    return;
}

void operationMusique(int op,int volume){
    switch(op){
    case 0:
        if(Mix_PausedMusic()==1){
            Mix_ResumeMusic();
        }
    else{
        Mix_PauseMusic();
        }
    break;
    case 1:
        Mix_RewindMusic();
    break;
    case 2:
        Mix_HaltMusic();
    break;
    case 3:
        if(volume > 0){
            volume--;
        }
    break;
    case 4:
        if(volume < MIX_MAX_VOLUME){
            volume++;
        }
    break;
    default:
    break;
    }
}


