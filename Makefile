# Makefile compilant les fichiers sources

# Définition des variables :

# Numéro du tp, utile pour les noms de certains fichiers
NUM_TP := X

# Répertoires
REP_SRC := src
REP_EXE := bin
REP_DOC := doc

# Compilation
CC := gcc
COPTION := -Wall -g -fsanitize=adress

# Liste des fichiers sources
SRC := $(wildcard $(REP_SRC)/*.c)

# Liste des fichiers objets
OBJ := $(patsubst $(REP_SRC)/%.c, $(REP_EXE)/%.o, $(SRC))


# Définition du nom de l'exécutable et de son emplacement final
EXE := charriersi-tp$(NUM_TP).out
CHE_EXE := $(REP_EXE)/$(EXE)

#Liste des extensions de fichiers à supprimer avec clean dans le répertoire source
SUPPR := *~ .out .old .bak \#*\#

#Doxyfile
DOXYFILE := Doxyfile



# Cible all
all: $(CHE_EXE)

# Règle de compilation
$(CHE_EXE): $(OBJ)
	$(CC) $(COPTION) $^ -o $@ -lm

# Règle pour les fichiers objets
$(REP_EXE)/%.o: $(REP_SRC)/%.c
	$(CC) $(COPTION) -c $< -o $@ -lm



# Cible clean
clean: 
	rm -f $(REP_EXE)/*.o $(CHE_EXE) $(REP_SRC)/$(SUPPR)


# Cible pour créer le fichier Doxyfile
$(REP_DOC)/Doxyfile:
	doxygen -g $@
	sed -i 's#OUTPUT_DIRECTORY.*=.*#OUTPUT_DIRECTORY       = $(REP_DOC)#' $@

# Cible pour générer la documentations
doc: $(REP_DOC)/Doxyfile
	doxygen $<

# Cible pour générer seulement le fichier Doxyfile
cdoc: $(REP_DOC)/Doxyfile

# Cible exe
exe:
	./$(CHE_EXE)

# Cible dir
dir:
	mkdir bin doc src

.PHONY: all clean doc exe cdoc dir
