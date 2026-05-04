CC     = gcc
CFLAGS = -Iinclude -Iobj/include -Iobj/include/obj -Wall -Wextra -Wpedantic
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lglu32 -lopengl32 -lm

SRC = src/app.c src/camera.c src/environment.c src/main.c src/scene.c src/texture.c src/utils.c
OBJ_SRC = obj/src/draw.c obj/src/info.c obj/src/load.c obj/src/model.c obj/src/transform.c

win:
	$(CC) $(CFLAGS) $(SRC) $(OBJ_SRC) $(LFLAGS) -o cube.exe

linux:
	$(CC) $(CFLAGS) $(SRC) $(OBJ_SRC) \
	    -lSDL2 -lSDL2_image -lGL -lGLU -lm -o cube

.PHONY: win linux
