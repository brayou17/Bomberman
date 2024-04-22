#include "player.h"
#include "map.h"
#include "gamepad.h"
#include "math.h"
#include "gamepadx.h"

#define SPEED_PLAYER 150.f

sfCircleShape* crl_player;

sfVector2f playerPos;
sfVector2f playerVel;

sfRectangleShape* rct_colP1;

void initPlayer()
{
	rct_colP1 = sfRectangleShape_create();
	sfRectangleShape_setSize(rct_colP1, vector2f(TAILLE_BLOCK / 3.f, TAILLE_BLOCK / 3.f));

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			player[i].pos = vector2f(TAILLE_BLOCK + TAILLE_BLOCK/2.f, TAILLE_BLOCK + TAILLE_BLOCK / 2.f);
			player[i].color = sfColor_fromRGBA(255, 255, 255, 255);
			break;
		case 1:
			player[i].pos = vector2f(TAILLE_MAPX * TAILLE_BLOCK - TAILLE_BLOCK * 2 + TAILLE_BLOCK / 2.f, TAILLE_BLOCK + TAILLE_BLOCK / 2.f);
			player[i].color = sfColor_fromRGBA(0, 255, 255, 255);
			break;
		case 2:
			player[i].pos = vector2f(TAILLE_BLOCK + TAILLE_BLOCK / 2.f,TAILLE_MAPY * TAILLE_BLOCK - TAILLE_BLOCK*2 + TAILLE_BLOCK / 2.f);
			player[i].color = sfColor_fromRGBA(255, 127, 0, 255);
			break;
		case 3:
			player[i].pos = vector2f(TAILLE_MAPX * TAILLE_BLOCK - TAILLE_BLOCK*2 + TAILLE_BLOCK / 2.f, TAILLE_MAPY * TAILLE_BLOCK - TAILLE_BLOCK * 2 + TAILLE_BLOCK / 2.f);
			player[i].color = sfColor_fromRGBA(0, 0, 0, 255);
			break;
		}
		player[i].vel = vector2f(0.0f, 0.0f);
		player[i].idControl = i;
		player[i].canMove = sfFalse;
		player[i].direction = i;
	}
	crl_player = sfCircleShape_create();
	sfCircleShape_setRadius(crl_player, TAILLE_BLOCK / 3.f);
	sfCircleShape_setOrigin(crl_player, vector2f(TAILLE_BLOCK / 3.f, TAILLE_BLOCK / 3.f));
}

void updatePlayer()
{
	float delta = getDeltaTime();
	for (int i = 0; i < 4; i++)
	{
		//player[i].nextPos = addVectorsrf(player[i].pos, vector2f(player[i].vel.x * delta, player[i].vel.y * delta));

		if (isButtonPressed(i, DPAD_DOWN))
		{
			player[i].direction = DOWN;
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].vel = vector2f(0.0f, SPEED_PLAYER);
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_UP))
		{
			player[i].direction = UP;
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].vel = vector2f(0.0f, -SPEED_PLAYER);
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_LEFT))
		{
			player[i].direction = LEFT;
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].vel = vector2f(-SPEED_PLAYER, 0.0f);
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_RIGHT))
		{
			player[i].direction = RIGHT;
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].vel = vector2f(SPEED_PLAYER, 0.0f);
				player[i].canMove = sfTrue;
			}
		}
		else
			player[i].canMove = sfFalse;

		if (player[i].canMove)
			player[i].pos = addVectorsrf(player[i].pos,vector2f( player[i].vel.x * delta, player[i].vel.y * delta));
	}
}

void displayPlayer(Window* _window)
{
	for (int i = 0; i < 4; i++)
	{
		sfCircleShape_setPosition(crl_player, player[i].pos);
		sfCircleShape_setFillColor(crl_player, player[i].color);
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_player, NULL);
	sfRectangleShape_setPosition(rct_colP1, player[i].nextPos);
	sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_colP1, NULL);
	}

}
