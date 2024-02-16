#include <stdio.h>
#include <stdlib.h>


#include <SDL.h>
#include <SDL_mixer.h>

void InitialisationM();
Mix_Music* loadM(char* p);
void jouerM(Mix_Music* musique,int tour);

void initialisationCanal(int numCanal,int volume);
Mix_Chunk * loadChunk(char * p);
void jouerC(int numCanal,Mix_Chunk* chunk,int tour);

void operationChunk(int op,int volume2,int numCanal);
void operationMusique(int op,int volume);


