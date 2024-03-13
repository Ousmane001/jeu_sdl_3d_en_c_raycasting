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

//#include "../game/game.h"

