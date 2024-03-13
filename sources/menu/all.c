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


/* pour compiler sous linux 

gcc main.c -o prog $(sdl2-config --cflags --libs) -lSDL_TTF

*/


	#include <stdio.h>
	#include <SDL.h>
	#include <SDL_ttf.h> 
	#include <stdbool.h> //Pour le type de données bool
	
	//#include "../game/game.h"
	
	//Macro-constantes pour les couleurs
	#define LONGUEUR_FENETRE 800
	#define LARGEUR_FENETRE 600

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

    window = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LONGUEUR_FENETRE, LARGEUR_FENETRE, 0);
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

// Déclaration d'une variable globale pour suivre l'état du plein écran
bool fullscreen = false;

void toggleFullscreen() {
    fullscreen = !fullscreen; // Inversion de l'état du plein écran

    if (fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // Passage en mode plein écran
    } else {
        SDL_SetWindowFullscreen(window, 0); // Retour au mode fenêtré
    }
}

void displayOptions() {
    bool quitOptions = false; // Variable pour suivre si l'utilisateur souhaite quitter le menu des options

    while (!quitOptions) { // Boucle jusqu'à ce que l'utilisateur choisisse de quitter le menu des options
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the options menu
        SDL_Color textColor = {255, 255, 255}; // White color
        SDL_Rect textRect;

        // Example: Displaying a title
        TTF_Font* font = TTF_OpenFont("arial.ttf", 36); // Load a font (change the path as needed)
        if (!font) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Options", textColor); // Render text to surface
        if (!textSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); // Create texture from surface
        if (!textTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            return;
        }

        // Positioning the text
        textRect.x = (LONGUEUR_FENETRE - textSurface->w) / 2; // Center horizontally
        textRect.y = 50; // 50 pixels from the top
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        // Rendering the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);

        // Example: Displaying options settings (adjust sound, fullscreen, etc.)
        // Implement your options menu here...

        // Example: Toggle fullscreen option
        TTF_Font* optionFont = TTF_OpenFont("arial.ttf", 24); // Load a font for options
        if (!optionFont) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* optionSurface = TTF_RenderText_Solid(optionFont, "Basculer en plein ecran", textColor);
        if (!optionSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(optionFont);
            return;
        }

        SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        if (!optionTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(optionSurface);
            TTF_CloseFont(optionFont);
            return;
        }

        SDL_Rect optionRect;
        optionRect.x = 100; // Position X de l'option
        optionRect.y = 150; // Position Y de l'option
        optionRect.w = optionSurface->w;
        optionRect.h = optionSurface->h;

        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);
        SDL_DestroyTexture(optionTexture);
        TTF_CloseFont(optionFont);



        // Draw "Return to main menu (Escape)"
	TTF_Font* escapeFont = TTF_OpenFont("arial.ttf", 20); // Load a font for options
        if (!optionFont) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* escapeSurface = TTF_RenderText_Solid(escapeFont, "Revenir au menu principal (Echap)", textColor);
        if (!escapeSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(escapeFont);
            return;
        }

        SDL_Texture* escapeTexture = SDL_CreateTextureFromSurface(renderer, escapeSurface);
        if (!escapeTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(escapeSurface);
            TTF_CloseFont(escapeFont);
            return;
        }

        SDL_Rect escapeRect;
        escapeRect.x = 100; // Position X de l'echap
        escapeRect.y = 500; // Position Y de l'echap
        escapeRect.w = escapeSurface->w;
        escapeRect.h = escapeSurface->h;

        SDL_RenderCopy(renderer, escapeTexture, NULL, &escapeRect);
        SDL_FreeSurface(escapeSurface);
        SDL_DestroyTexture(escapeTexture);
        TTF_CloseFont(escapeFont);

        // Render present to display changes
        SDL_RenderPresent(renderer);

        // Événements pour quitter le menu d'options
        SDL_Event event;
        int quit = 0;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // Si l'utilisateur ferme la fenêtre, on quitte tout le programme
                quitOptions = true;
                quit = true; // Quitte la boucle principale
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    // Si l'utilisateur appuie sur Échap, on quitte le menu des options
                    quitOptions = true;
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= optionRect.x && mouseX <= optionRect.x + optionRect.w &&
                    mouseY >= optionRect.y && mouseY <= optionRect.y + optionRect.h) {
                    // Si l'utilisateur clique sur l'option de basculement en plein écran
                    toggleFullscreen();
                } else if (mouseX >= escapeRect.x && mouseX <= escapeRect.x + escapeRect.w &&
                           mouseY >= escapeRect.y && mouseY <= escapeRect.y + escapeRect.h) {
                    // Si l'utilisateur clique sur l'option de retour au menu principal
                    quitOptions = true;
                }
            }
        }
    }
}

void displayCredits() {
	bool quitCredits = false; // Variable pour suivre si l'utilisateur souhaite quitter le menu des credits

    while (!quitCredits) { // Boucle jusqu'à ce que l'utilisateur choisisse de quitter le menu des Credits
        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the credits menu
        SDL_Color textColor = {255, 255, 255}; // White color
        SDL_Rect textRect;

        // Example: Displaying a title
        TTF_Font* font = TTF_OpenFont("arial.ttf", 36); // Load a font (change the path as needed)
        if (!font) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Credits", textColor); // Render text to surface
        if (!textSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(font);
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); // Create texture from surface
        if (!textTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            TTF_CloseFont(font);
            return;
        }

        // Positioning the text
        textRect.x = (LONGUEUR_FENETRE - textSurface->w) / 2; // Center horizontally
        textRect.y = 50; // 50 pixels from the top
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        // Rendering the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);

        // ajouts de noms dans les credits ici

        // noms
        TTF_Font* optionFont = TTF_OpenFont("arial.ttf", 16); // Load a font for options
        if (!optionFont) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* optionSurface = TTF_RenderText_Solid(optionFont, "Diakite Alpha-Ousmane, "
        							      "Djerlil Salah-Eddine et "
        							      "Lacroze Maxime", textColor);
        if (!optionSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(optionFont);
            return;
        }

        SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
        if (!optionTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(optionSurface);
            TTF_CloseFont(optionFont);
            return;
        }

        SDL_Rect optionRect;
        optionRect.x = 100; // Position X des credits
        optionRect.y = 250; // Position Y des credits
        optionRect.w = optionSurface->w;
        optionRect.h = optionSurface->h;

        SDL_RenderCopy(renderer, optionTexture, NULL, &optionRect);
        SDL_FreeSurface(optionSurface);
        SDL_DestroyTexture(optionTexture);
        TTF_CloseFont(optionFont);



        // Draw "Return to main menu (Escape)"
	TTF_Font* escapeFont = TTF_OpenFont("arial.ttf", 20); // Load a font for options
        if (!optionFont) {
            fprintf(stderr, "Erreur lors du chargement de la police : %s\n", TTF_GetError());
            return;
        }

        SDL_Surface* escapeSurface = TTF_RenderText_Solid(escapeFont, "Revenir au menu principale (Echap)", textColor);
        if (!escapeSurface) {
            fprintf(stderr, "Erreur lors du rendu du texte : %s\n", TTF_GetError());
            TTF_CloseFont(escapeFont);
            return;
        }

        SDL_Texture* escapeTexture = SDL_CreateTextureFromSurface(renderer, escapeSurface);
        if (!escapeTexture) {
            fprintf(stderr, "Erreur lors de la création de la texture : %s\n", SDL_GetError());
            SDL_FreeSurface(escapeSurface);
            TTF_CloseFont(escapeFont);
            return;
        }

        SDL_Rect escapeRect;
        escapeRect.x = 100; // Position X de l'echap
        escapeRect.y = 500; // Position Y de l'echap
        escapeRect.w = escapeSurface->w;
        escapeRect.h = escapeSurface->h;

        SDL_RenderCopy(renderer, escapeTexture, NULL, &escapeRect);
        SDL_FreeSurface(escapeSurface);
        SDL_DestroyTexture(escapeTexture);
        TTF_CloseFont(escapeFont);

        // Render present to display changes
        SDL_RenderPresent(renderer);

        // Événements pour quitter le menu d'options
        SDL_Event event;
        int quit = 0;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // Si l'utilisateur ferme la fenêtre, on quitte tout le programme
                quitCredits = true;
                quit = true; // Quitte la boucle principale
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    // Si l'utilisateur appuie sur Échap, on quitte le menu des options
                    quitCredits = true;
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= escapeRect.x && mouseX <= escapeRect.x + escapeRect.w &&
                           mouseY >= escapeRect.y && mouseY <= escapeRect.y + escapeRect.h) {
                    // Si l'utilisateur clique sur l'option de retour au menu principal
                    quitCredits = true;
                }
            }
        }
    }
}

	
	
int main(int argc, char** argv) {
    if (initSDL() != 0) {
        return -1;
    }

    Button jouerButton, optionsButton, creditsButton, quitterButton;

    initButton(&jouerButton, 100, 100, 200, 50, RED_COLOR, "Jouer");
    initButton(&optionsButton, 100, 200, 200, 50, GREEN_COLOR, "Options");
    initButton(&creditsButton, 100, 300, 200, 50, BLUE_COLOR, "Credits");
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
                    //launch_game();
                } else if (mouseX >= optionsButton.x && mouseX <= optionsButton.x + optionsButton.w &&
                           mouseY >= optionsButton.y && mouseY <= optionsButton.y + optionsButton.h) {
                    SDL_Log("Bouton Options cliqué !");
                    displayOptions();
                } else if (mouseX >= creditsButton.x && mouseX <= creditsButton.x + creditsButton.w &&
                           mouseY >= creditsButton.y && mouseY <= creditsButton.y + creditsButton.h) {
                    SDL_Log("Bouton Crédits cliqué !");
                    displayCredits();
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


