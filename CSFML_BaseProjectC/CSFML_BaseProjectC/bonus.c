#include "bonus.h"
#include "player.h"
#include "map.h"

#define GT_BONUS STD_LIST_GETDATA(bonusList, Bonus_struct, y)


sfCircleShape* crl_bonus;

void initBonus()
{
	crl_bonus = sfCircleShape_create();
	sfCircleShape_setPointCount(crl_bonus, 3);
	sfCircleShape_setRadius(crl_bonus, TAILLE_BLOCK / 3.f);

	bonusList = STD_LIST_CREATE(Bonus_struct, 0);
}

void addBonus(sfVector2f _pos, int _idBonus)
{
	Bonus_struct tmp;

	tmp.colrect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);
	tmp.idBonus = _idBonus;
	tmp.pos = _pos;
	tmp.canBeDestroyed = sfFalse;
	tmp.time_beDestroyed = 0.0f;

	bonusList->push_back(&bonusList, &tmp);
}

void updateBonus()
{
	float delta = getDeltaTime();
	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < bonusList->size(bonusList); y++)
		{
			GT_BONUS->time_beDestroyed += delta;
			if (GT_BONUS->time_beDestroyed > 2.0f)
				GT_BONUS->canBeDestroyed = sfTrue;

			if (sfFloatRect_intersects(&player[i].colRect, &GT_BONUS->colrect, NULL))
			{
				switch (GT_BONUS->idBonus)
				{
				case BONUS_NBR_CASE:
					player[i].numCaseBombe++;
					break;
				case BONUS_NBR_BOMBE:
					player[i].numOfBombe++;
					break;
				case BONUS_SPEED:
					player[i].time_speed = 0.0f;
					player[i].isUsingSpeed = sfTrue;
					player[i].countspeed++;
					break;
				case BONUS_PUSH_BOMBE:
					player[i].time_pushBombe = 0.0f;
					player[i].isUsingPushBombe = sfTrue;
					player[i].countPush++;
					break;
				case BONUS_EVIL:
					player[i].time_evil = 0.0f;
					player[i].isUsingEvil = sfTrue;
					player[i].countEvil++;
					break;
				}
				bonusList->erase(&bonusList, y);
			}
		}
	}
}

void displayBonus(Window* _window)
{
	for (int y = 0; y < bonusList->size(bonusList); y++)
	{
		switch (GT_BONUS->idBonus)
		{
		case BONUS_NBR_CASE:
			sfCircleShape_setOutlineColor(crl_bonus, sfBlue);
			sfCircleShape_setOutlineThickness(crl_bonus, 2.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125,125,125));
			break;
		case BONUS_NBR_BOMBE:
			sfCircleShape_setOutlineColor(crl_bonus, sfGreen);
			sfCircleShape_setOutlineThickness(crl_bonus, 2.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125, 125, 125));
			break;
		case BONUS_SPEED:
			sfCircleShape_setOutlineColor(crl_bonus, sfRed);
			sfCircleShape_setOutlineThickness(crl_bonus, 2.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125, 125, 125));
			break;
		case BONUS_PUSH_BOMBE:
			sfCircleShape_setOutlineColor(crl_bonus, sfMagenta);
			sfCircleShape_setOutlineThickness(crl_bonus, 2.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125, 125, 125));
			break;
		case BONUS_EVIL:
			sfCircleShape_setOutlineColor(crl_bonus,sfRed);
			sfCircleShape_setOutlineThickness(crl_bonus, 0.0f);
			sfCircleShape_setFillColor(crl_bonus, sfRed);
			break;
		}

		sfCircleShape_setPosition(crl_bonus, GT_BONUS->pos);
		GT_BONUS->colrect = sfCircleShape_getGlobalBounds(crl_bonus);
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_bonus, NULL);
	}
}
