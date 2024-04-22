#include "player.h"
#include "map.h"

sfCircleShape* crl_player;

void initPlayer()
{
	crl_player = sfCircleShape_create();
	sfCircleShape_setFillColor(crl_player, sfColor_fromRGBA(255, 127, 0, 255));
	sfCircleShape_setRadius(crl_player, TAILLE_BLOCK / 2.f);
	sfCircleShape_setPointCount(crl_player, 3);
	sfCircleShape_setPosition(crl_player, vector2f(100.0f, 100.0f));
}

void updatePlayer()
{

}

void displayPlayer(Window* _window)
{
	sfRenderWindow_drawCircleShape(_window->renderWindow, crl_player, NULL);
}
