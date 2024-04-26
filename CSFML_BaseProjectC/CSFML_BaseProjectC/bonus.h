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

/// <summary>
/// This function init all elements of bonus
/// </summary>
void initBonus();
/// <summary>
/// This function create a bonus
/// </summary>
/// <param name="_pos">The wanted pos</param>
/// <param name="_idBonus">The bonus' id</param>
void addBonus(sfVector2f _pos, int _idBonus);
/// <summary>
/// This function update all elements of bonus
/// </summary>
void updateBonus();
/// <summary>
/// This function display all elements of bonus
/// </summary>
/// <param name="_window"></param>
void displayBonus(Window* _window);
