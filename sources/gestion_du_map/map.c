#include "map.h"

/*********************************************************************************************************************************************/

int scanner_une_map(char* fichier, int* nombre_de_ligne, int* nombre_de_colonne){
  FILE* fichier_map = fopen(fichier, "r");
  char chaine_lecture[TAILLE_MAX_TAMPON] = "";
  unsigned int nb_lignes = 0,nb_colonnes = 0,compteur_ligne,compteur_colonne,compteur_caractere;
  
  if(fichier_map == NULL){
    printf("Erreur d'ouverture du fichier");
    return ERREUR_OUVERTURE;
  }
  else{
    // lecture des dimension de la matrice (i.e les 2 premieres lignes)
    fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map);
    nb_lignes = atoi(chaine_lecture);
    fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map);
    nb_colonnes = atoi(chaine_lecture);

    // sauvegarde des dimensions de la map:
    *nombre_de_ligne = nb_lignes;
    *nombre_de_colonne = nb_colonnes;
    
    // parcours de la matrice et recherches d'erreurs :
    compteur_ligne = 0;
    while(fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map) != NULL){
      compteur_colonne = 0;
      compteur_caractere = 0;

      while(chaine_lecture[compteur_caractere] != '\0'){
        if(chaine_lecture[compteur_caractere] == CARACTERE_SEPARATEUR){
          compteur_colonne++;
        }
        compteur_caractere++;
      }
      if(compteur_colonne != nb_colonnes){
        printf("Erreur de format: il ya au moins une colonne qui ne correspond pas aux dimensions attendue !");
        return ERREUR_MAP;
      }
      compteur_ligne++;
    
    }
    if(compteur_ligne != nb_lignes){
      printf("Erreur de format: il ya au moins une ligne qui ne correspond pas aux dimensions attendue !");
      return ERREUR_MAP;
    }
    return MAP_CORRECT;
  }
  
}
/*********************************************************************************************************************************************/

int allouer_une_map_correcte(int*** map, int nombre_de_ligne, int nombre_de_colonne){
  int compteur_ligne;

    // allocation de la matrice map
    *map = (int**)malloc(nombre_de_ligne * sizeof(int*));

    if(*map == NULL){
      printf("Erreur d'allocation de la matrice");
      return ERREUR_MAP;
    }
    else{
      for(compteur_ligne = 0; compteur_ligne < nombre_de_ligne; compteur_ligne++){
        (*map)[compteur_ligne] = (int*)calloc(nombre_de_colonne,sizeof(int));
      }
      return MATRICE_CREEE;
    }
}

/*********************************************************************************************************************************************/

int charger_une_map(char* fichier, int** map){
  FILE* fichier_map = fopen(fichier, "r");
  char chaine_lecture[TAILLE_MAX_TAMPON] = "";
  char caractere_actuel = 0;
  unsigned int nb_lignes = 0,nb_colonnes = 0,compteur_ligne,compteur_colonne,compteur_caractere;

  if(fichier_map == NULL){
    printf("Erreur d'ouverture du fichier");
    return ERREUR_OUVERTURE;
  }
  else{
    // lecture des dimension de la matrice (i.e les 2 premieres lignes)
    fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map);
    nb_lignes = atoi(chaine_lecture);
    fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map);
    nb_colonnes = atoi(chaine_lecture);

    // lecture caractere par caractere du fichier map:
    compteur_ligne = 0;
    compteur_colonne = 0;

    while(fgets(chaine_lecture, TAILLE_MAX_TAMPON, fichier_map) != NULL){
      compteur_caractere = 0;
      while(chaine_lecture[compteur_caractere] != '\0'){
        if(chaine_lecture[compteur_caractere] != CARACTERE_SEPARATEUR){

          // s'il s'agit d'un caractere, on le convertit en entier:
          if(chaine_lecture[compteur_caractere] != '\n'){
            map[compteur_ligne][compteur_colonne] = atoi(&chaine_lecture[compteur_caractere]);
            compteur_colonne++;
          }
          else{
            compteur_ligne++;
            compteur_colonne = 0;
          }
        }
        compteur_caractere++;
      }
    }
    
  }
  return MATRICE_CHARGEE_AVEC_SUCCES;
}

/*********************************************************************************************************************************************/

int afficher_une_map(SDL_Renderer* rendu, int** map, int nombre_de_ligne, int nombre_de_colonne, int debut_x, int debut_y){
  SDL_Rect rectangle;
  int compteur_ligne,compteur_colonne;

  // caracteristique du mur :
  rectangle.w = TAILLE_MUR;
  rectangle.h = TAILLE_MUR;
  rectangle.x = debut_x;
  rectangle.y = debut_y;

  // dessin 2D des mur :

  // on efface d'abord la fenetre : 
  COULEUR_NOIRE(rendu);
  //SDL_RenderClear(rendu);

  for(compteur_ligne = 0; compteur_ligne < nombre_de_ligne; compteur_ligne++){
    rectangle.y = (compteur_ligne+debut_y) * TAILLE_MUR;

    for(compteur_colonne = 0; compteur_colonne < nombre_de_colonne; compteur_colonne++){
        rectangle.x = (compteur_colonne+debut_x) * TAILLE_MUR;

        // s'il s'agit d'un mur :
        if(map[compteur_ligne][compteur_colonne] == OBSTACLE){
          if(dessiner_un_mur_2D(rendu, &rectangle) != MUR_DESSINE_AVEC_SUCCES)
            return ERREUR_AFFICHAGE_MAP;
        }
        
    }
    
  }
  return MAP_AFFICHEE_AVEC_SUCCES;

}
/*********************************************************************************************************************************************/

int dessiner_un_mur_2D(SDL_Renderer* rendu, SDL_Rect* mur){

  if((rendu == NULL) || (mur == NULL)){
    printf("Erreur: argument incorrect dans le dessin d'un mur  en 2D :\n");
    return ERREUR_DESSIN_MUR;
  }

  COULEUR_BLANCHE(rendu);
  SDL_RenderFillRect(rendu, mur);
  COULEUR_ROUGE(rendu);
  SDL_RenderDrawRect(rendu, mur);
  SDL_RenderPresent(rendu);
  
  return MUR_DESSINE_AVEC_SUCCES;
}

/*********************************************************************************************************************************************/

int detruire_une_map(int*** map, int nombre_de_ligne){
  int compteur_ligne;

  for(compteur_ligne = 0; compteur_ligne < nombre_de_ligne; compteur_ligne++){
    free((*map)[compteur_ligne]);
  }
  free(*map);
  *map = NULL;

  //   /!\ la fonction free ne retourne aucun code d'erreur :
  // mais nous somme entrain de rechercher un moyen pour savoir si la memoire a bien ete libere :

  return MAP_DETRUITE_AVEC_SUCCES;
}

/*********************************************************************************************************************************************/