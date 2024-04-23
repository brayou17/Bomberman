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
	sfVector2f vel;
	sfVector2f speed;
	sfColor color;
	int idControl;
	float timerUseBombe;
	sfFloatRect colRect;

	int numCaseBombe;
	int numOfBombe;
}Player_struct;

Player_struct player[4];

void initPlayer();
void updatePlayer();
void displayPlayer(Window* _window);;
