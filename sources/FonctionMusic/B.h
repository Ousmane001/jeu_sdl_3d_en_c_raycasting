#include <stdio.h>
#include <stdlib.h>


#include <SDL.h>
#include <SDL_mixer.h>


Mix_Music* loadM(char* p);
void InitialisationM();
void liberation_des_musiques(Mix_Music** musique,unsigned int nb_musique);
void erreur_sdlm(const char * message,Mix_Music* musique,Mix_Chunk* chunk);
void liberation_des_musiques(Mix_Music** musique,unsigned int nb_musique);
void jouerM(Mix_Music* musique,int tour);
void initialisationCanal(int canal);
Mix_Chunk * loadChunk(char * p);
void enjeuM(int volume,int volume2,Mix_Music* musique,Mix_Chunk* chunk,int canal);
void closemusic(Mix_Music** musique,Mix_Chunk** chunk);