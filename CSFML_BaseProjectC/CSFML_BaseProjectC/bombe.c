#include "bombe.h"
#include "map.h"
#include "explosion.h"

#define GT_BOMBES STD_LIST_GETDATA(bombeList, Bombe_struct, i)
#define GT_EXPLOSION STD_LIST_GETDATA(explosionList, Explosion_struct, x)


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
	tmp.canDead = sfFalse;
	tmp.colRect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);

	bombeList->push_back(&bombeList, &tmp);
}

void updateBombe()
{
	float delta = getDeltaTime();
	/*for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		for (int x = 0; x < explosionList->size(explosionList); x++)
		{
			if (Equals(GT_BOMBES->pos, GT_EXPLOSION->pos))
			{
				explosionBombe(GT_BOMBES->pos, GT_BOMBES->numCase);
				bombeList->erase(&bombeList, i);

			}
		}
		GT_BOMBES->time_dead += delta;
		if (GT_BOMBES->time_dead > GT_BOMBES->timer_dead)
		{
			explosionBombe(GT_BOMBES->pos, GT_BOMBES->numCase);
			bombeList->erase(&bombeList, i);
		}
	}*/

	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		if (GT_BOMBES->canDead == sfFalse)
		{
			GT_BOMBES->time_dead += delta;
			if (GT_BOMBES->time_dead > GT_BOMBES->timer_dead)
			{
				explosionBombe(GT_BOMBES->pos, GT_BOMBES->numCase);
				bombeList->erase(&bombeList, i);
			}
		}
		else
		{
			GT_BOMBES->time_dead += delta;
			if (GT_BOMBES->time_dead > 0.1f)
			{
				explosionBombe(GT_BOMBES->pos, GT_BOMBES->numCase);
				bombeList->erase(&bombeList, i);
			}
		}
	}

	for (int x = 0; x < explosionList->size(explosionList); x++)
	{
		for (int i = 0; i < bombeList->size(bombeList); i++)
		{
			if (sfFloatRect_intersects(&GT_BOMBES->colRect, &GT_EXPLOSION->colRect, NULL))
			{
				GT_BOMBES->canDead = sfTrue;
				GT_BOMBES->time_dead = 0.0f;
				break;
			}
		}
	}
}

void displayBombe(Window* _window)
{
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		sfCircleShape_setPosition(crl_bombe, GT_BOMBES->pos);
		GT_BOMBES->colRect = sfCircleShape_getGlobalBounds(crl_bombe);
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_bombe, NULL);
	}
}