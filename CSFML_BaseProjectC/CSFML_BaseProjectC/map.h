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
/// <summary>
/// This function checks the collisions with the player
/// </summary>
/// <param name="_sprite">The FLoatRect of the sprite</param>
/// <param name="_direction">The direction</param>
/// <param name="_vitesse">The speed</param>
/// <param name="idControl">The id of thhe player</param>
/// <returns>If there's a collision</returns>
sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse, int idControl);
/// <summary>
/// This function create an explosion
/// </summary>
/// <param name="_pos">The wanted position</param>
/// <param name="_numCase">The number of case</param>
void explosionBombe(sfVector2f _pos, int _numCase);
