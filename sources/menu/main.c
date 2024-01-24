#include <stdio.h>
#include <SDL.h>


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

gcc main.c -o prog $(sdl2-config --cflags --libs)

*/


#include <SDL_ttf.h>

SDL_Window *window;  // Fenêtre SDL
SDL_Renderer *renderer;  // Renderer SDL pour le dessin
TTF_Font *font;  // Police SDL_ttf pour le texte

typedef struct {
    int x, y, w, h;  // Coordonnées et dimensions du bouton
    SDL_Color color;  // Couleur du bouton
    const char *text;  // Texte affiché sur le bouton
} Button;

Button jouerButton, optionsButton, creditsButton, quitterButton;  // Boutons du menu

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

    window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
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

    font = TTF_OpenFont("arial.ttf", 24);  // Utilisez le chemin complet du fichier de police
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
void initButtons() {
    jouerButton.x = 100;
    jouerButton.y = 100;
    jouerButton.w = 200;
    jouerButton.h = 50;
    jouerButton.color = (SDL_Color){255, 0, 0, 255};  // Rouge
    jouerButton.text = "Jouer";

    optionsButton.x = 100;
    optionsButton.y = 200;
    optionsButton.w = 200;
    optionsButton.h = 50;
    optionsButton.color = (SDL_Color){0, 255, 0, 255};  // Vert
    optionsButton.text = "Options";

    creditsButton.x = 100;
    creditsButton.y = 300;
    creditsButton.w = 200;
    creditsButton.h = 50;
    creditsButton.color = (SDL_Color){0, 0, 255, 255};  // Bleu
    creditsButton.text = "Crédits";

    quitterButton.x = 100;
    quitterButton.y = 400;
    quitterButton.w = 200;
    quitterButton.h = 50;
    quitterButton.color = (SDL_Color){255, 255, 0, 255};  // Jaune
    quitterButton.text = "Quitter";
}

// Afficher un bouton
void renderButton(const Button *button) {
    // Remplir le rectangle avec la couleur du bouton
    SDL_SetRenderDrawColor(renderer, button->color.r, button->color.g, button->color.b, button->color.a);
    SDL_RenderFillRect(renderer, &(SDL_Rect){button->x, button->y, button->w, button->h});

    // Créer une surface texte
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, button->text, (SDL_Color){255, 255, 255, 255});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Positionner et afficher le texte au centre du bouton
    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {
        button->x + (button->w - textW) / 2,
        button->y + (button->h - textH) / 2,
        textW,
        textH
    };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Libérer les ressources de la texture et de la surface texte
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

int main(int nbarg, char** argv){
    if (initSDL() != 0) {
        return -1;
    }

    initButtons();

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
                    // Action lorsque le bouton "Jouer" est cliqué
                    SDL_Log("Bouton Jouer cliqué !");
                } else if (mouseX >= optionsButton.x && mouseX <= optionsButton.x + optionsButton.w &&
                           mouseY >= optionsButton.y && mouseY <= optionsButton.y + optionsButton.h) {
                    // Action lorsque le bouton "Options" est cliqué
                    SDL_Log("Bouton Options cliqué !");
                } else if (mouseX >= creditsButton.x && mouseX <= creditsButton.x + creditsButton.w &&
                           mouseY >= creditsButton.y && mouseY <= creditsButton.y + creditsButton.h) {
                    // Action lorsque le bouton "Crédits" est cliqué
                    SDL_Log("Bouton Crédits cliqué !");
                } else if (mouseX >= quitterButton.x && mouseX <= quitterButton.x + quitterButton.w &&
                           mouseY >= quitterButton.y && mouseY <= quitterButton.y + quitterButton.h) {
                    // Action lorsque le bouton "Quitter" est cliqué
                    SDL_Log("Bouton Quitter cliqué !");
                    quit = 1;
                }
            }
        }

        // Effacer l'écran avec une couleur blanche
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Afficher les boutons
        renderButton(&jouerButton);
        renderButton(&optionsButton);
        renderButton(&creditsButton);
        renderButton(&quitterButton);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Libérer les ressources avant de quitter
    cleanup();

    return 0;
}
