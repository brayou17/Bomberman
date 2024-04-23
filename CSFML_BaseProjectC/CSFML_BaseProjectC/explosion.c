#include "explosion.h"
#include "player.h"
#include "gamepadx.h"

#define GT_EXPLOSION STD_LIST_GETDATA(explosionList, Explosion_struct, x)

sfCircleShape* crl_expl;
sfRectangleShape* rct_colExpl;

void initExplosion()
{
	rct_colExpl = sfRectangleShape_create();

	crl_expl = sfCircleShape_create();
	explosionList = STD_LIST_CREATE(Explosion_struct, 0);
}

void addExplosion(sfVector2f _pos)
{
	Explosion_struct tmp;

	tmp.color = sfColor_fromRGBA(255,0,0,255);
	tmp.pos = _pos;
	tmp.radius = 10.0f;
	tmp.colRect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);

	explosionList->push_back(&explosionList, &tmp);
}

void updateExplosion()
{
	float delta = getDeltaTime();

	for (int x = 0; x < explosionList->size(explosionList); x++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (sfFloatRect_intersects(&GT_EXPLOSION->colRect, &player[i].colRect, NULL))
			{
				setVibration(i, 1.0, 1.0);
			}


		}
			GT_EXPLOSION->radius += 30.0f * delta;
			if (GT_EXPLOSION->radius > 20.0f)
			{
				explosionList->erase(&explosionList, x);
				setVibration(0, 0.0, 0.0);
				setVibration(1, 0.0, 0.0);
				setVibration(2, 0.0, 0.0);
				setVibration(3, 0.0, 0.0);
			
			}
	}
}

void displayExplosion(Window* _window)
{
	for (int x = 0; x < explosionList->size(explosionList); x++)
	{
		sfCircleShape_setPosition(crl_expl, GT_EXPLOSION->pos);
		sfCircleShape_setFillColor(crl_expl, GT_EXPLOSION->color);
		sfCircleShape_setRadius(crl_expl, GT_EXPLOSION->radius);
		sfCircleShape_setOrigin(crl_expl, vector2f(GT_EXPLOSION->radius, GT_EXPLOSION->radius));
		GT_EXPLOSION->colRect = sfCircleShape_getGlobalBounds(crl_expl);
		
		//sfRectangleShape_setPosition(rct_colExpl, vector2f(GT_EXPLOSION->colRect.left, GT_EXPLOSION->colRect.top));
		//sfRectangleShape_setSize(rct_colExpl, vector2f(GT_EXPLOSION->colRect.width, GT_EXPLOSION->colRect.width));

		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_expl, NULL);
		//sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_colExpl, NULL);
	}
}
