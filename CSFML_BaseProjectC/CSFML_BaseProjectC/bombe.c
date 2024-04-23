#include "bombe.h"
#include "map.h"

#define GT_BOMBES STD_LIST_GETDATA(bombeList, Bombe_struct, i)

sfCircleShape* crl_bombe;

void initBombe()
{
	crl_bombe = sfCircleShape_create();
	sfCircleShape_setFillColor(crl_bombe, sfColor_fromRGBA(50, 50, 50, 255));
	sfCircleShape_setRadius(crl_bombe, TAILLE_BLOCK/3.f);
	sfCircleShape_setOrigin(crl_bombe, vector2f(TAILLE_BLOCK / 3.f, TAILLE_BLOCK / 3.f));
	bombeList = STD_LIST_CREATE(Bombe_struct, 0);
}

void createBombe(sfVector2f _pos, int _idPlayer, int _numCase)
{
	Bombe_struct tmp;

	tmp.idPlayer = _idPlayer;
	tmp.pos = _pos;
	tmp.numCase = _numCase;
	tmp.timer_dead = 2.f;
	tmp.time_dead = 0.0f;

	bombeList->push_back(&bombeList, &tmp);
}

void updateBombe()
{
	float delta = getDeltaTime();
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		GT_BOMBES->time_dead += delta;
		if (GT_BOMBES->time_dead > GT_BOMBES->timer_dead)
		{
			explosionBombe(GT_BOMBES->pos, GT_BOMBES->numCase);
			bombeList->erase(&bombeList, i);
		}
	}
}

void displayBombe(Window* _window)
{
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		sfCircleShape_setPosition(crl_bombe, GT_BOMBES->pos);
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_bombe, NULL);
	}
}