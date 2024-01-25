/* pour compiler avec de la sdl sur windows 

gcc main.c -I include -L lib -lmingw32 -lSDL2main -lSDL2 -o  bin/mon_exectutable

*/

/*après avoir installé ubuntu 
1- ouvrir le terminal linux et faire une mise à jour
sudo apt update
sudo apt upgrade

2- installe le langage c grace au comilateur gcc
sudo apt install build-essential
sudo apt install gcc
 
 3- installer la sdl
 sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0
 */


/* pour compiler avec la sdl sous linux 

gcc main.c -o prog $(sdl2-config --cflags --libs) -lSDL_TTF

*/

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

// Macro-constantes pour les dimensions de la fenêtre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Macro-constantes pour les couleurs
#define RED_COLOR (SDL_Color){255, 0, 0, 255}
#define GREEN_COLOR (SDL_Color){0, 255, 0, 255}
#define BLUE_COLOR (SDL_Color){0, 0, 255, 255}
#define YELLOW_COLOR (SDL_Color){255, 255, 0, 255}
#define BACKGROUND_COLOR (SDL_Color){0, 15, 100, 255}
#define BACKG_COLOR 0, 15, 100, 255

// Macro-constante pour le chemin de la police
#define FONT_PATH "arial.ttf"

// Structure générique pour un bouton
typedef struct {
    int x, y, w, h;
    SDL_Color color;
    const char *text;
} Button;

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;

// Initialisation de la SDL et de SDL_ttf
int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Erreur TTF_Init : %s", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("Erreur SDL_CreateWindow : %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Erreur SDL_CreateRenderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    font = TTF_OpenFont(FONT_PATH, 24);
    if (!font) {
        SDL_Log("Erreur TTF_OpenFont : %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

// Initialisation des boutons
void initButton(Button *button, int x, int y, int w, int h, SDL_Color color, const char *text) {
    button->x = x;
    button->y = y;
    button->w = w;
    button->h = h;
    button->color = color;
    button->text = text;
}

// Afficher un bouton
void renderButton(const Button *button) {
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(renderer, &(SDL_Rect){button->x, button->y, button->w, button->h});

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, button->text, BACKGROUND_COLOR);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {
        button->x + (button->w - textW) / 2,
        button->y + (button->h - textH) / 2,
        textW,
        textH
    };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

// Libérer les ressources
void cleanup() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv) {
    if (initSDL() != 0) {
        return -1;
    }

    Button jouerButton, optionsButton, creditsButton, quitterButton;

    initButton(&jouerButton, 100, 100, 200, 50, RED_COLOR, "Jouer");
    initButton(&optionsButton, 100, 200, 200, 50, GREEN_COLOR, "Options");
    initButton(&creditsButton, 100, 300, 200, 50, BLUE_COLOR, "Crédits");
    initButton(&quitterButton, 100, 400, 200, 50, YELLOW_COLOR, "Quitter");

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= jouerButton.x && mouseX <= jouerButton.x + jouerButton.w &&
                    mouseY >= jouerButton.y && mouseY <= jouerButton.y + jouerButton.h) {
                    SDL_Log("Bouton Jouer cliqué !");
                } else if (mouseX >= optionsButton.x && mouseX <= optionsButton.x + optionsButton.w &&
                           mouseY >= optionsButton.y && mouseY <= optionsButton.y + optionsButton.h) {
                    SDL_Log("Bouton Options cliqué !");
                } else if (mouseX >= creditsButton.x && mouseX <= creditsButton.x + creditsButton.w &&
                           mouseY >= creditsButton.y && mouseY <= creditsButton.y + creditsButton.h) {
                    SDL_Log("Bouton Crédits cliqué !");
                } else if (mouseX >= quitterButton.x && mouseX <= quitterButton.x + quitterButton.w &&
                           mouseY >= quitterButton.y && mouseY <= quitterButton.y + quitterButton.h) {
                    SDL_Log("Bouton Quitter cliqué !");
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, BACKG_COLOR);
        SDL_RenderClear(renderer);

        renderButton(&jouerButton);
        renderButton(&optionsButton);
        renderButton(&creditsButton);
        renderButton(&quitterButton);

        SDL_RenderPresent(renderer);
    }

    cleanup();

    return 0;
}