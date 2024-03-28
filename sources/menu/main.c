#include "../game/game.h"

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

    void cleanup();

    return 0;
}

