if [ ! -d "build" ]; then
	mkdir build
fi
clang src/*.c -o build/main -lm -lraylib -ggdb
