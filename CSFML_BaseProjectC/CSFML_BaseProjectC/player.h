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
	int countspeed;

	sfBool isUsingPushBombe;
	float time_pushBombe;
	int countPush;

	sfBool isUsingEvil;
	float time_evil;
	int countEvil;

	sfBool isTouched;
	sfBool countDead;

	int score;

}Player_struct;

Player_struct player[4];
int countDead;

void initPlayer();
void updatePlayer();
void displayPlayer(Window* _window);;
