#pragma once
#include "tools.h"
#include "windowManager.h"
#include "List.h"

typedef enum {
	BONUS_NBR_CASE,
	BONUS_NBR_BOMBE,
	BONUS_SPEED,
	BONUS_PUSH_BOMBE,
	BONUS_EVIL,
}Bonus_enum;

typedef struct
{
	sfVector2f pos;
	sfFloatRect colrect;
	int idBonus;
	sfBool canBeDestroyed;
	float time_beDestroyed;
}Bonus_struct;

stdList* bonusList;

void initBonus();
void addBonus(sfVector2f _pos, int _idBonus);
void updateBonus();
void displayBonus(Window* _window);
