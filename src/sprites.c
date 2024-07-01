#include "sprites.h"

Texture2D load_sprite(char* path){
	return LoadTexture(path);
}

Texture2D load_spritesheet(char* path){
	return load_sprite(path);
}
