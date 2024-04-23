#pragma once
#include "tools.h"
#include "windowManager.h"

typedef struct {
	sfVector2f pos;
	sfColor color;
}Explosion_struct;

void initExplosion();
void addExplosion(sfVector2f _pos);
void updateExplosion();
void displayExplosion();
