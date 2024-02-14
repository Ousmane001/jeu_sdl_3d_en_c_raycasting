#include <stdio.h>
#include <stdlib.h>


#include <SDL.h>
#include <SDL_mixer.h>

void InitialisationM();
Mix_Music* loadM(char* p);
void jouerM(Mix_Music* musique,int tour);



void erreurmusique(const char * message,Mix_Music* musique);
void erreurchunk(const char * message,Mix_Chunk* chunk);


void initialisationCanal(int canal);
Mix_Chunk * loadChunk(char * p);

void enjeuM(int volume,int volume2,Mix_Music* musique,Mix_Chunk* chunk,int canal,SDL_Event event);
void operationMusique(int op,int volume);


