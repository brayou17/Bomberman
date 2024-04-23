#include "explosion.h"

#define GT_EXPLOSION STD_LIST_GETDATA(explosionList, Explosion_struct, x)

sfCircleShape* crl_expl;

void initExplosion()
{
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
		GT_EXPLOSION->radius += 30.0f * delta;
		if (GT_EXPLOSION->radius > 20.0f)
			explosionList->erase(&explosionList, x);
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
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_expl, NULL);
	}
}
