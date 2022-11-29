OBJS = src/main.c src/game/map.c src/game/polyomino.c src/gui/renderer.c src/gui/window.c src/gui/ui.c

CC = gcc

COMPILER_FLAGS = -Wall -pedantic

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

OBJ_NAME = main

	
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

run: $(OBJS)
	./$(OBJ_NAME)

clean:
	rm -rf ./$(OBJ_NAME)