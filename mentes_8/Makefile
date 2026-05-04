all:
	gcc -Iinclude -Iobj/include -Iobj/include/obj src/*.c obj/src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lglu32 -lopengl32 -lm -o cube.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o cube -Wall -Wextra -Wpedantic
