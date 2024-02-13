# variable contenant le nom de notre compilateur:  
# (si un jour on change de compilateur ça sera beaucoup plus facile de modifier le makefile :)
COMPILATEUR = gcc

#variable contenant le nom de notre executable :
EXECUTABLE = prog
#addresse relative ou on stoque l'executable du projet:
ADRESSE_EXE = includes_de_SDL/bin/

# stockage dans une variable des inclusion sdl necessaire pour la compilation :

#INCLUSION = -I includes_de_SDL/include -L includes_de_SDL/lib -lmingw32 -lSDL2main -lSDL2
INCLUSION = $(shell sdl2-config --cflags --libs)  -lm

# creation d'une liste contenant l'ensemble des fichier sources (*.c) de notre programme :
SOURCES = $(wildcard sources/*.c sources/game/*.c sources/gestion_du_joueur/*.c sources/gestion_du_map/*.c)

# creation a partir de l'ensemble des fichiers sources, une liste de fichier objet (.o)
OBJETS = $(SOURCES:*.c=*.o)



# debut de la compilation proprement dite :
compilation : $(EXECUTABLE)

# compilation séparé de chaque fichier_source en fichier objet :

%.o : %.c 
	$(COMPILATEUR) -c $< -o $@ $(INCLUSION)

# edition des liens de tous les fichier objets obtenu pour creer l'executable :

$(EXECUTABLE) : $(OBJETS)
	$(COMPILATEUR) -o $(ADRESSE_EXE)$@ $(OBJETS) $(INCLUSION)
#	$(COMPILATEUR) -o $@ $(OBJETS) $(INCLUSION)

execution : 
	$(ADRESSE_EXE)$(EXECUTABLE)

#https://yunes.informatique.univ-paris-diderot.fr/wp-content/uploads/cours/INFOGRAPHIE/08-Raycasting.pdf

#gcc -o prog sources/game/game.c sources/game/main.c sources/gestion_du_joueur/joueur.c sources/gestion_du_map/map.c -lm $(sdl2-config --cflags --libs)