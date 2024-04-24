#include "bombe.h"
#include "map.h"
#include "explosion.h"
#include "player.h"
#include "math.h"

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
	tmp.isNotColPlayer = sfFalse;
	tmp.isTouched = sfFalse;
	tmp.direction = UP;

	bombeList->push_back(&bombeList, &tmp);
}

void updateBombe()
{
	float delta = getDeltaTime();
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		if (GT_BOMBES->isTouched)
		{
				sfVector2i posMap = vector2i(GT_BOMBES->pos.x / TAILLE_BLOCK, GT_BOMBES->pos.y / TAILLE_BLOCK);
				switch (GT_BOMBES->direction)
				{
				case UP:
					if (!mapTop[posMap.y - 1][posMap.x].isSolid)
					{
						GT_BOMBES->pos = vector2f(GT_BOMBES->pos.x, GT_BOMBES->pos.y - 450.f *delta);
					}
					else
					{
						GT_BOMBES->pos.y -= TAILLE_BLOCK / 2.f;
						GT_BOMBES->isTouched = sfFalse;
					}
					break;
				case DOWN:
					if (!mapTop[posMap.y + 1][posMap.x].isSolid)
					{
						GT_BOMBES->pos = vector2f(GT_BOMBES->pos.x, GT_BOMBES->pos.y + 450.f * delta);
					}
					else
					{
						GT_BOMBES->pos.y += TAILLE_BLOCK / 2.f;
						GT_BOMBES->isTouched = sfFalse;
					}
					break;
				case RIGHT:
					if (!mapTop[posMap.y][posMap.x + 1].isSolid)
					{
						GT_BOMBES->pos = vector2f(GT_BOMBES->pos.x + 450.f * delta, GT_BOMBES->pos.y);
					}
					else
					{
						GT_BOMBES->pos.x += TAILLE_BLOCK / 2.f;
						GT_BOMBES->isTouched = sfFalse;
					}
					break;
				case LEFT:
					if (!mapTop[posMap.y][posMap.x - 1].isSolid)
					{
						GT_BOMBES->pos = vector2f(GT_BOMBES->pos.x - 450.f * delta, GT_BOMBES->pos.y);
					}
					else
					{
						GT_BOMBES->pos.x -= TAILLE_BLOCK / 2.f;
						GT_BOMBES->isTouched = sfFalse;
					}
					break;
				}
			
		}

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

		if (!GT_BOMBES->isNotColPlayer)// TODO calcul à la main du rect
		{
			int a = 0;
			for (int z = 0; z < 4; z++)
			{
				if (!sfFloatRect_intersects(&GT_BOMBES->colRect, &player[z].colRect, NULL))
					a++;
			}
			if (a == 4)
			{
				GT_BOMBES->isNotColPlayer = sfTrue;
			}
		}
	}
}


sfBool checkBombeId(int _idPlayer, int _numOfBombe) // mettre tout dans une boucle existante ou mettre ++ quand player use et -- quand bombe id player explose
{
	int count = 0;
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		if (GT_BOMBES->idPlayer == _idPlayer)count++;
	}
	if (count >= _numOfBombe) return sfFalse;
	else return sfTrue;
}

sfBool checkPosBombe(sfVector2f _pos)
{
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		sfVector2f posB = GT_BOMBES->pos;
		if (posB.x >= _pos.x - 10.f && posB.x <= _pos.x + 10.f  && posB.y >= _pos.y - 10.f && posB.y <= _pos.y + 10.f)
			return sfFalse;
	}
	return sfTrue;
}

void moveBombe(int _idPlayer, int _direction)
{
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		if (sfFloatRect_intersects(&player[_idPlayer].colRect, &GT_BOMBES->colRect, NULL) && GT_BOMBES->isNotColPlayer  && !GT_BOMBES->isTouched)
		{
			GT_BOMBES->isTouched = sfTrue;
			GT_BOMBES->direction = _direction;
		}
	}
}

sfBool checkBombePlayer2(sfVector2f _NextPos, sfVector2f _NextPos2)
{
	for (int i = 0; i < bombeList->size(bombeList); i++)
	{
		if ((sfFloatRect_contains(&GT_BOMBES->colRect, _NextPos.x, _NextPos.y) || sfFloatRect_contains(&GT_BOMBES->colRect, _NextPos2.x, _NextPos2.y)) && GT_BOMBES->isNotColPlayer)
			return sfTrue;
	}
	return sfFalse;
}