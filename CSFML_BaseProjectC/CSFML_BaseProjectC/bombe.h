#pragma once
#include "tools.h"
#include "windowManager.h"
#include "List.h"

typedef struct {
	sfVector2f pos;
	sfFloatRect colRect;
	sfBool canDead;
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