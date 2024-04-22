#pragma once
#include "tools.h"
#include "windowManager.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
}Direction;

typedef struct {
	sfVector2f pos;
	sfVector2f nextPos;
	sfVector2f vel;
	sfColor color;
	Direction direction;
	int idControl;
	sfBool canMove;
}Player_struct;

Player_struct player[4];

void initPlayer();
void updatePlayer();
void displayPlayer(Window* _window);;
