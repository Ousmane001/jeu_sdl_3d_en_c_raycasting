#include "B.h"

void operationChunk(int op,int volume2,int numCanal){
    switch(op){
        case 0:
            if(Mix_Paused(numCanal)==1){
                Mix_Resume(numCanal);
            }
            else{
                Mix_Pause(numCanal);
            }
        break;
	case 1:
	    Mix_HaltChannel(numCanal);
	break;
	case 2:
	    if(volume2>0){
                volume2--;
            }
	break;
	case 3:
	    if(volume2<MIX_MAX_VOLUME){
                volume2++;
            }
	break;
	default:
	break;
    }
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



