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
	sfColor color;

	sfBool isTouched;
	sfBool wasTouched;
	sfBool lockDirection;
	int direction;
	sfBool check;

}Bombe_struct;

stdList* bombeList;

/// <summary>
/// This function init all elements of Bombs
/// </summary>
void initBombe();

/// <summary>
/// This function create a bombs
/// </summary>
/// <param name="_pos">position wanted</param>
/// <param name="_idPlayer">id of player</param>
/// <param name="_numCase">number of case</param>
void createBombe(sfVector2f _pos, int _idPlayer, int _numCase);
/// <summary>
/// This function update all elements of Bombs
/// </summary>
void updateBombe();
/// <summary>
/// This function display all elements of Bombs
/// </summary>
/// <param name="_window"></param>
void displayBombe(Window* _window);
/// <summary>
/// This function ckecks all the bombs with this id
/// </summary>
/// <param name="_idPlayer">The id</param>
/// <param name="_numOfBombe">The number max of bombs</param>
/// <returns></returns>
sfBool checkBombeId(int _idPlayer, int _numOfBombe);
/// <summary>
/// This function checks all bombs' pos
/// </summary>
/// <param name="_pos"></param>
/// <returns></returns>
sfBool checkPosBombe(sfVector2f _pos);
/// <summary>
/// This funtion moves the position the bomb
/// </summary>
/// <param name="_idPlayer">The id of the player</param>
/// <param name="_direction">The direction</param>
void moveBombe(int _idPlayer, int _direction);
/// <summary>
/// This function checks the collision with players
/// </summary>
/// <param name="_NextPos"></param>
/// <param name="_NextPos2"></param>
/// <returns></returns>
sfBool checkBombePlayer2(sfVector2f _NextPos, sfVector2f _NextPos2);
