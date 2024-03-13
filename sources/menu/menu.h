#ifndef MENU_H
#define MENU_H

	#include <stdio.h>
	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <stdbool.h>

	//Macro-constantes pour les couleurs
	#define LONGUEUR_FENETRE 720
	#define LARGEUR_FENETRE 480
	#define WINDOW_WIDTH 720

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

	// Déclarations des fonctions
	int initSDL();
	void initButton(Button *button, int x, int y, int w, int h, SDL_Color color, const char *text);
	void renderButton(const Button *button);
	void cleanup();

	void displayCredits();

	void displayOptions();
	void toggleFullscreen();

#endif /* MENU_H */


