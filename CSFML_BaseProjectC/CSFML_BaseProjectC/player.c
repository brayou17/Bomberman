#include "player.h"
#include "map.h"
#include "gamepad.h"
#include "math.h"
#include "gamepadx.h"
#include "bombe.h"
#include "stateManager.h"
#include "explosion.h"
#include "endGame.h"

#define SPEED_PLAYER 150.f
#define GETLEFTS getSticksPos(i, LEFT_THUMB)

sfCircleShape* crl_player;

sfVector2f playerPos;
sfVector2f playerVel;


sfRectangleShape* rct_colPlayer;

float timer_pause;
float timer_debug;

sfShader* shaPlayer;
sfRenderStates rsPlayer;

void initPlayer()
{

	shaPlayer = sfShader_createFromFile(NULL,NULL,SHADER_PATH"Evil.frag");
	if (shaPlayer == NULL)
	{
		printf("Shader not found\n");
	}
	else
	{
		rsPlayer.shader = shaPlayer;
		rsPlayer.blendMode = sfBlendAlpha;
		rsPlayer.transform = sfTransform_Identity;
		rsPlayer.texture = NULL;
	}

	if (!firstLoad2)
	{
		defaultScore();
		firstLoad2 = sfTrue;
	}
	readScore();
	countDead = 0;
	rct_colPlayer = sfRectangleShape_create();
	for (int i = 0; i < playernber; i++)
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
		player[i].numOfBombe = 1;
		player[i].colRect = FlRect(0.0f, 0.0f, 0.0f, 0.0f);
		player[i].numCaseBombe = 1;
		player[i].isTouched = sfFalse;
		player[i].life = 1;
		player[i].numBombePlaced = 0;
		player[i].isUsingEvil = sfFalse;
		player[i].isUsingPushBombe = sfFalse;
		player[i].isUsingSpeed = sfFalse;
		player[i].time_evil = 0.0f;
		player[i].time_pushBombe = 0.0f;
		player[i].time_speed = 0.0f;
		player[i].countDead = sfFalse;
		player[i].countEvil = 0;
		player[i].countspeed = 0;
		player[i].countPush = 0;
		player[i].shaderTime = 0.0f;
	}
	crl_player = sfCircleShape_create();
	sfCircleShape_setRadius(crl_player, TAILLE_BLOCK / 3.f);
	sfCircleShape_setOrigin(crl_player, vector2f(TAILLE_BLOCK / 3.f, TAILLE_BLOCK / 3.f));
	timer_pause = 0.0f;
	timer_debug = 0.0f;
}

void updatePlayer(Window* _window)
{
	if (countDead == playernber-1)
	{
		bombeList->clear(&bombeList);
		explosionList->clear(&explosionList);
		toggleEndGame();
	}
	else if (countDead >= playernber)
	{
		bombeList->clear(&bombeList);
		explosionList->clear(&explosionList);
		changeState(_window, GAME);
	}
	float delta = getDeltaTime();

	timer_pause += delta;

	for (int i = 0; i < playernber; i++)
	{
		if (isButtonPressed(i, START) && timer_pause > 0.2f)
		{
			timer_pause = 0.0f;
			togglePause();
		}

		if (player[i].life <= 0)
			continue;
		
		if ((GETLEFTS.y < -50 || isButtonPressed(i, DPAD_DOWN)) && !collision(player[i].colRect, DOWN, player[i].speed,i))
		{
			if (player[i].isUsingPushBombe)moveBombe(i,DOWN);
			player[i].pos.y += player[i].speed.y * delta;
		}
		 else if ((GETLEFTS.y > 50 || isButtonPressed(i, DPAD_UP)) && !collision(player[i].colRect, UP, player[i].speed,i))
		{
			if (player[i].isUsingPushBombe)moveBombe(i, UP);
			player[i].pos.y -= player[i].speed.y * delta;

		}
		 if ((GETLEFTS.x < -50 || isButtonPressed(i, DPAD_LEFT)) && !collision(player[i].colRect, LEFT, player[i].speed,i))
		{
			if (player[i].isUsingPushBombe)moveBombe(i, LEFT);
			player[i].pos.x -= player[i].speed.x * delta;

		}
		 else if ((GETLEFTS.x > 50 || isButtonPressed(i, DPAD_RIGHT)) && !collision(player[i].colRect, RIGHT, player[i].speed,i))
		{
			if (player[i].isUsingPushBombe)moveBombe(i, RIGHT);
			player[i].pos.x += player[i].speed.x * delta;

		}

		player[i].timerUseBombe += delta;
		if (isButtonPressed(i, B) && player[i].timerUseBombe > 0.4f  && checkBombeId(i, player[i].numOfBombe)  && !player[i].isUsingEvil && checkPosBombe(vector2f(player[i].pos.x - ((int)player[i].pos.x % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f, player[i].pos.y - ((int)player[i].pos.y % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f)))
		{
			createBombe(vector2f(player[i].pos.x - ((int) player[i].pos.x %TAILLE_BLOCK) + TAILLE_BLOCK/2.f, player[i].pos.y - ((int)player[i].pos.y % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f), i, player[i].numCaseBombe);
			player[i].numBombePlaced++;
			player[i].timerUseBombe = 0.0f;
		}

		if (player[i].isUsingSpeed)
		{
			player[i].time_speed += delta;
			player[i].speed = vector2f(300.0f,300.0f);
			if (player[i].time_speed > 5.f)
			{
				player[i].time_speed = 0.0f;
				player[i].speed = vector2f(150.0f, 150.0f);
				player[i].isUsingSpeed = sfFalse;
			}
		}

		if (player[i].isUsingEvil)
		{
			player[i].time_evil += delta;
			if(checkBombeId(i, player[i].numOfBombe)  && checkPosBombe(vector2f(player[i].pos.x - ((int)player[i].pos.x % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f, player[i].pos.y - ((int)player[i].pos.y % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f)))
				createBombe(vector2f(player[i].pos.x - ((int)player[i].pos.x % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f, player[i].pos.y - ((int)player[i].pos.y % TAILLE_BLOCK) + TAILLE_BLOCK / 2.f), i, player[i].numCaseBombe);

			if (player[i].time_evil > 5.f)
			{
				player[i].time_evil = 0.0f;
				player[i].isUsingEvil = sfFalse;
			}
		}

		if (player[i].isUsingPushBombe)
		{
			player[i].time_pushBombe += delta;
			if (player[i].time_pushBombe > 50.f)
			{
				player[i].time_pushBombe = 0.0f;
				player[i].isUsingPushBombe = sfFalse;
			}
		}

		if (isDebugMode)
		{
			if (isButtonPressed(i, A) && isButtonPressed(i, LB) && isButtonPressed(i, RB))
			{
				player[i].life = 100;
			}

		}

	}
		if (isDebugMode)
		{
			timer_debug += delta;

			if (timer_debug > 0.2f && sfKeyboard_isKeyPressed(sfKeyNumpad1))
			{
				for (int i = 0; i < playernber; i++)
				{
					player[i].isUsingSpeed = sfTrue;
				}
				timer_debug = 0.0f;
			}
			if (timer_debug > 0.2f && sfKeyboard_isKeyPressed(sfKeyNumpad2))
			{
				for (int i = 0; i < playernber; i++)
				{
					player[i].isUsingPushBombe = sfTrue;
				}
				timer_debug = 0.0f;
			}
			if (timer_debug > 0.2f && sfKeyboard_isKeyPressed(sfKeyNumpad0))
			{
				for (int i = 0; i < playernber; i++)
				{
					player[i].isUsingEvil = sfTrue;
				}
				timer_debug = 0.0f;
			}
			if (timer_debug > 0.2f && sfKeyboard_isKeyPressed(sfKeyNumpad4))
			{
				for (int i = 0; i < playernber; i++)
				{
					player[i].numOfBombe++;
				}
				timer_debug = 0.0f;
			}
			if (timer_debug > 0.2f && sfKeyboard_isKeyPressed(sfKeyNumpad5))
			{
				for (int i = 0; i < playernber; i++)
				{
					player[i].numCaseBombe++;
				}
				timer_debug = 0.0f;
			}
		}
}

void displayPlayer(Window* _window)
{
	for (int i = 0; i < playernber; i++)
	{
		if (player[i].life <= 0) continue;

		sfCircleShape_setPosition(crl_player, player[i].pos);
		sfCircleShape_setFillColor(crl_player, player[i].color);
		player[i].colRect = sfCircleShape_getGlobalBounds(crl_player);
		//sfRectangleShape_setPosition(rct_colPlayer,vector2f(player[i].colRect.left, player[i].colRect.top) );
		//sfRectangleShape_setSize(rct_colPlayer, vector2f(player[i].colRect.width, player[i].colRect.height));
		if(!player[i].isUsingEvil)
			sfRenderWindow_drawCircleShape(_window->renderWindow, crl_player, NULL);
		else
		{
			player[i].shaderTime += getDeltaTime();
			sfShader_setFloatUniform(shaPlayer, "u_Time", player[i].shaderTime);
			sfRenderWindow_drawCircleShape(_window->renderWindow, crl_player, &rsPlayer);
		}

		//sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_colPlayer, NULL);
	}

}
