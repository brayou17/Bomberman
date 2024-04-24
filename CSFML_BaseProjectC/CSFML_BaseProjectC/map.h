#pragma once
#include "tools.h"
#include"windowManager.h"
#include "player.h"

#define TAILLE_MAPY 13
#define TAILLE_MAPX 15
#define TAILLE_BLOCK 64


typedef enum {
	BLOCK_WALL = 3,
	BLOCK_BRICK,
	BLOCK_NOTHING_TOP,
}Type_blockTop;

typedef struct {
	sfBool isSolid;
	sfBool canBeDestroyed;
	sfBool canUpdate;
	sfColor color;
	int id;
}Map_struct;

Map_struct mapTop[TAILLE_MAPY][TAILLE_MAPX];

void initMap();
void updateMap();
void displayMap(Window* _window);
sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse, int idControl);
void explosionBombe(sfVector2f _pos, int _numCase);
