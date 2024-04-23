#include "player.h"
#include "map.h"
#include "gamepad.h"
#include "math.h"
#include "gamepadx.h"
#include "bombe.h"

#define SPEED_PLAYER 150.f

sfCircleShape* crl_player;

sfVector2f playerPos;
sfVector2f playerVel;


void initPlayer()
{

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
		player[i].speed = vector2f(150.0f,150.0f);
		player[i].timerUseBombe = 0.0f;
		player[i].colRect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);
		player[i].numOfBombe = 1;
		player[i].numCaseBombe = 10;
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
		/*player[i].nextPos = addVectorsrf(player[i].pos, vector2f(player[i].vel.x * delta, player[i].vel.y * delta));

		if (isButtonPressed(i, DPAD_DOWN))
		{
			player[i].direction = DOWN;
			player[i].vel = vector2f(0.0f, SPEED_PLAYER);
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_UP))
		{
			player[i].direction = UP;
			player[i].vel = vector2f(0.0f, -SPEED_PLAYER);
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_LEFT))
		{
			player[i].direction = LEFT;
			player[i].vel = vector2f(-SPEED_PLAYER, 0.0f);
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].canMove = sfTrue;
			}
		}
		else if (isButtonPressed(i, DPAD_RIGHT))
		{
			player[i].direction = RIGHT;
			player[i].vel = vector2f(SPEED_PLAYER, 0.0f);
			if (!isCollision(player[i].pos, player[i].direction))
			{
				player[i].canMove = sfTrue;
			}
		}
		else
			player[i].canMove = sfFalse;

		if (player[i].canMove)
			player[i].pos = addVectorsrf(player[i].pos,vector2f( player[i].vel.x * delta, player[i].vel.y * delta));*/

		if (isButtonPressed(i, DPAD_DOWN) && !collision(player[i].colRect, DOWN, player[i].speed))
		{
			player[i].pos.y += player[i].speed.y * delta;
		}
		else if (isButtonPressed(i, DPAD_UP) && !collision(player[i].colRect, UP, player[i].speed))
		{
			player[i].pos.y -= player[i].speed.y * delta;

		}
		else if (isButtonPressed(i, DPAD_LEFT) && !collision(player[i].colRect, LEFT, player[i].speed))
		{
			player[i].pos.x -= player[i].speed.x * delta;

		}
		else if (isButtonPressed(i, DPAD_RIGHT) && !collision(player[i].colRect, RIGHT, player[i].speed))
		{
			player[i].pos.x += player[i].speed.x * delta;

		}

		player[i].timerUseBombe += delta;
		if (isButtonPressed(i, B) && player[i].timerUseBombe > 0.5f)
		{
			createBombe(vector2f(player[i].pos.x - ((int) player[i].pos.x %TAILLE_BLOCK) + TAILLE_BLOCK/2.f, player[i].pos.y - ((int)player[i].pos.y % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f), i, player[i].numCaseBombe);
			player[i].timerUseBombe = 0.0f;
		}
	}
}

void displayPlayer(Window* _window)
{
	for (int i = 0; i < 4; i++)
	{
		sfCircleShape_setPosition(crl_player, player[i].pos);
		sfCircleShape_setFillColor(crl_player, player[i].color);
		player[i].colRect = sfCircleShape_getGlobalBounds(crl_player);
		sfRenderWindow_drawCircleShape(_window->renderWindow, crl_player, NULL);
	}

}
