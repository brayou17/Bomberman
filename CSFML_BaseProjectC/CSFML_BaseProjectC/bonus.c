#include "bonus.h"
#include "player.h"

#define GT_BONUS STD_LIST_GETDATA(bonusList, Bonus_struct, y)


sfCircleShape* crl_bonus;

void initBonus()
{
	crl_bonus = sfCircleShape_create();
	sfCircleShape_setPointCount(crl_bonus, 3);

	bonusList = STD_LIST_CREATE(Bonus_struct, 0);
}

void addBonus(sfVector2f _pos, int _idBonus)
{
	Bonus_struct tmp;

	tmp.colrect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);
	tmp.idBonus = _idBonus;
	tmp.pos = _pos;

	bonusList->push_back(&bonusList, &tmp);
}

void updateBonus()
{
	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < bonusList->size(bonusList); y++)
		{
			if (sfFloatRect_intersects(&player[i].colRect, &GT_BONUS->colrect, NULL))
			{
				switch (GT_BONUS->idBonus)
				{
				case BONUS_NBR_CASE:

					break;
				case BONUS_NBR_BOMBE:

					break;
				case BONUS_SPEED:

					break;
				case BONUS_PUSH_BOMBE:

					break;
				case BONUS_EVIL:

					break;
				}
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
			sfCircleShape_setOutlineThickness(crl_bonus, 0.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125,125,125));
			break;
		case BONUS_NBR_BOMBE:
			sfCircleShape_setOutlineColor(crl_bonus, sfColor_fromRGB(200, 20, 0));
			sfCircleShape_setOutlineThickness(crl_bonus, 0.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125, 125, 125));
			break;
		case BONUS_SPEED:
			sfCircleShape_setOutlineColor(crl_bonus, sfRed);
			sfCircleShape_setOutlineThickness(crl_bonus, 0.0f);
			sfCircleShape_setFillColor(crl_bonus, sfColor_fromRGB(125, 125, 125));
			break;
		case BONUS_PUSH_BOMBE:
			sfCircleShape_setOutlineColor(crl_bonus, sfMagenta);
			sfCircleShape_setOutlineThickness(crl_bonus, 0.0f);
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
