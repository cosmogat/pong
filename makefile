# 21-07-2013
# billy

EXE = pong # Executable
OBJ = pong.o # Objectes
COM = gcc # Compilador
LIB = -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf # Llibreries (-l*, -L*, -I*)
MAC = -D_GNU_SOURCE # Macros (-D*)
AVS = -W -Wall -Wextra -ansi -pedantic # Avisos
OPT = -march=native -O2 -pipe # Optimitzacio
DEP = -g # Depuracio, no recomanable junt amb $(OPT)
OPC = $(OPT) $(AVS) $(MAC) -std=c99 # Opcions
DIR = ~/bin # Directori per a instalar

all: $(EXE)

$(EXE): $(OBJ)
	@echo Enllaçant $(OBJ) per a crear $(EXE)
	$(COM) $(LIB) $(OBJ) -o $@

pong.o: pong.c
	@echo Compilant $<
	$(COM) $(OPC) -c $<

exe: all
	./$(EXE)

install: all
	mkdir -p $(DIR)
	cp $(EXE) $(DIR)

clean:
	@echo Netejant...
	rm -rf $(EXE) $(OBJ) *~
