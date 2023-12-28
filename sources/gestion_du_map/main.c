#include "map.h"
//gcc ../sources/gestion_du_map/main.c ../sources/gestion_du_map/map.c -I include -L lib -lmingw32 -lSDL2main -lSDL2 -o  bin/prog
int main(int argc, char *argv[]){

    printf("debut du test map\n");
    int** map;
  int i,j,nb_ligne,nb_colonne;
  
  charger_une_map(FICHIER_MAP,map);

    printf("fin du test\n");
    return 0;
}