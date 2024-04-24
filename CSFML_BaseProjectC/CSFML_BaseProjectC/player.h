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
	int life;
	float timerUseBombe;
	sfFloatRect colRect;

	int numCaseBombe;
	int numOfBombe;
	int numBombePlaced;

	sfBool isUsingSpeed;
	float time_speed;

	sfBool isUsingPushBombe;
	float time_pushBombe;

	sfBool isUsingEvil;
	float time_evil;

	sfBool isTouched;

}Player_struct;

Player_struct player[4];

void initPlayer();
void updatePlayer();
void displayPlayer(Window* _window);;
