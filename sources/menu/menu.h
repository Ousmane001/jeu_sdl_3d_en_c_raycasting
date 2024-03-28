#ifndef MENU_H

	#define MENU_H
	#include <stdio.h>
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <stdbool.h>

	// Macro-constantes pour les couleurs
	#define RED_COLOR (SDL_Color){255, 0, 0, 255}
	#define GREEN_COLOR (SDL_Color){0, 255, 0, 255}
	#define BLUE_COLOR (SDL_Color){0, 0, 255, 255}
	#define YELLOW_COLOR (SDL_Color){255, 255, 0, 255}
	#define BACKGROUND_COLOR (SDL_Color){0, 15, 100, 255}
	#define BACKG_COLOR 0, 15, 100, 255

	// Macro-constante pour le chemin de la police
	#define FONT_PATH "arial.ttf"

	extern SDL_Window *window;
	extern SDL_Renderer *renderer;
	extern TTF_Font *font;
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


