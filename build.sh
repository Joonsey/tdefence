if [ ! -d "build" ]; then
	mkdir build
fi
clang src/*.c -o build/main -lm -lSDL2 -lSDL2_image -lSDL2_gfx -ggdb
