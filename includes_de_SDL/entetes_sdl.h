#ifndef ENTETES_SDL_H

    #define ENTETES_SDL_H


    #include <stdio.h>
    #include <stdlib.h>
    #include "include/SDL.h"

    #define COULEUR_ROUGE(x) SDL_SetRenderDrawColor((x),255,0,0,SDL_ALPHA_OPAQUE)
    #define COULEUR_BLANCHE(x) SDL_SetRenderDrawColor((x),255,255,255,SDL_ALPHA_OPAQUE)
    #define COULEUR_NOIRE(x) SDL_SetRenderDrawColor((x),0,0,0,SDL_ALPHA_OPAQUE)
#endif