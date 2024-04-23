#pragma once
#include "tools.h"
#include "windowManager.h"
#include "List.h"


typedef struct {
	sfVector2f pos;
	sfColor color;
	float radius;
	sfFloatRect colRect;
}Explosion_struct;

stdList* explosionList;

void initExplosion();
void addExplosion(sfVector2f _pos);
void updateExplosion();
void displayExplosion(Window* _window);
