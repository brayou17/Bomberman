#pragma once
#include "tools.h"
#include "windowManager.h"
#include "List.h"

typedef struct {
	sfVector2f pos;
	sfFloatRect colRect;
	sfBool canDead;
	sfBool isNotColPlayer;
	int numCase;
	int idPlayer;
	float time_dead;
	float timer_dead;
}Bombe_struct;

stdList* bombeList;


void initBombe();
void createBombe(sfVector2f _pos, int _idPlayer, int _numCase);
void updateBombe();
void displayBombe(Window* _window);
sfBool checkBombeId(int _idPlayer, int _numOfBombe);
sfBool checkPosBombe(sfVector2f _pos);
void moveBombe(int _idPlayer, int _direction);

sfBool checkBombePlayer2(sfVector2f _NextPos, sfVector2f _NextPos2);
