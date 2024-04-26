#include "endGame.h"
#include "createParticles.h"
#include "fontManager.h"
#include "gamepad.h"
#include "gamepadx.h"
#include "player.h"
#include "soundManager.h"

#define NBR_ELEM_GB 5

typedef enum {
	EG_NAME_PLAYER,
	EG_NBR_BOMBE,
	EG_NBR_SPEED,
	EG_NBR_EVIL,
	EG_NBR_PUSH
};

typedef struct {
	sfVector2f pos;
	char* string;
	sfBool canDisplay;
}EndGame_struct;

EndGame_struct Gb[NBR_ELEM_GB];
EndGame_struct Gb2[4];

sfCircleShape* crl_trophy;

sfRectangleShape* rct_endGBG;
sfRectangleShape* rct_endGAllBG;
sfVector2f BG_pos;
sfBool isOnePassedEG;
sfBool endOfMap;

sfText* txt_endGame;
float alpha;

float timer_particles;
float timer_EG;
char bufferGb[50];
int playerWon;

void defaultScore()
{
	FILE* file = fopen("../Ressources/Save/score.bin", "wb");
	for (int i = 0; i < 4; i++)
	{
		player[i].score = 0;
		fwrite(&player[i].score, sizeof(int), 1, file);
	}
	fclose(file);
}

void writeScore()
{
	FILE* file = fopen("../Ressources/Save/score.bin", "wb");
	for (int i = 0; i < 4; i++)
	{
		if (player[i].score == NULL)
			player[i].score = 0;
		fwrite(&player[i].score, sizeof(int), 1, file);
	}
	fclose(file);
}

void readScore()
{
	FILE* file = fopen("../Ressources/Save/score.bin", "rb");
	if (file == NULL)
	{
		printf("Fichier introuvable en readScore");
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			fread(&player[i].score, sizeof(int), 1,file);
		}
		fclose(file);
	}
}

void initEndGame()
{
	crl_trophy = sfCircleShape_create();
	sfCircleShape_setFillColor(crl_trophy, sfYellow);
	sfCircleShape_setRadius(crl_trophy, 20.0f);

	timer_particles = 0.0f;
	txt_endGame = sfText_create();
	sfText_setFont(txt_endGame, getDefaultFont());
	sfText_setColor(txt_endGame, sfWhite);

	rct_endGBG = sfRectangleShape_create();
	rct_endGAllBG = sfRectangleShape_create();
	BG_pos = vector2f(600.f,-600.f);

	sfRectangleShape_setFillColor(rct_endGBG, sfColor_fromRGBA(20, 20, 20, 200));
	sfRectangleShape_setSize(rct_endGBG, vector2f(800.0f,600.f));

	alpha = 0;
	sfRectangleShape_setFillColor(rct_endGAllBG, sfColor_fromRGBA(0, 0, 0, alpha));
	sfRectangleShape_setSize(rct_endGAllBG, vector2f(1920.f, 1080.f));

	isOnePassedEG = sfFalse;
	endOfMap = sfFalse;

	for (int x = 0; x < 4; x++)
	{
		Gb2[x].canDisplay = sfFalse;
		if (x == 0)Gb2[x].string = "Player 1 :";
		if (x == 1)Gb2[x].string = "Player 2 :";
		if (x == 2)Gb2[x].string = "Player 3 :";
		if (x == 3)Gb2[x].string = "Player 4 :";
	}

	for (int i = 0; i < NBR_ELEM_GB; i++)
	{
		Gb[i].canDisplay = sfTrue;
	}
	timer_EG = 0.0f;
}

void updateEndGame(Window* _window)
{
	float delta = getDeltaTime();

	if (alpha < 255)
		alpha += 100.f * delta;
	sfRectangleShape_setFillColor(rct_endGAllBG, sfColor_fromRGBA(0, 0, 0,(int) alpha ));

	if(BG_pos.y < 200.f)
		BG_pos.y += delta * 100.f;

	timer_particles += 10.0f * delta;
	if (timer_particles > 10.f)
	{
		timer_particles = 0.0f;
		CreateParticles(vector2f(rand_float(100.0f, 1820.f), rand_float(100.f, 980.f)), vector2f(10.f,10.f),vector2f(20.0f,20.0f),vector2f(0.5f,0.5f),0,360,0.f,0.f,1000.f,1000.f,10.0f,sfColor_fromRGBA(rand_int(0,255), rand_int(0, 255), rand_int(0, 255),255), sfColor_fromRGBA(rand_int(0, 255), rand_int(0, 255), rand_int(0, 255), 0),1.5f,2.f,50,"nul",IntRect(0,0,0,0),NULL,0.0f,0.5f,3.f);
	}
	timer_EG += delta;
	for (int i = 0; i < playernber; i++)
	{
		if (isButtonPressed(i, A) && timer_EG > 0.2f)
		{
			if (!Gb2[0].canDisplay)
			{
				player[playerWon].score++;
				writeScore();
				for (int i = 0; i < NBR_ELEM_GB; i++)
				{
					Gb[i].canDisplay = sfFalse;
				}
				for (int x = 0; x < 4; x++)
				{
					Gb2[x].canDisplay = sfTrue;
				}
			}
			else if (endOfMap)
			{
				toggleEndGame();
				defaultScore();
				changeState(_window, MENU);
			}
			else
			{
				if (player[playerWon].score == 3)
				{
					endOfMap = sfTrue;
				}
				else
				{
					toggleEndGame();
					changeState(_window, GAME);
				}
			}
			timer_EG = 0.0f;
		}

	}
}

void displayEndGame1(Window* _window)
{
	sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_endGAllBG, NULL);

}

void displayEndGame2(Window* _window)
{
	if (!isOnePassedEG)
	{
		isOnePassedEG = sfTrue;
		readScore();
		stopSound("Mgame");
		stopSound("Mmenu");
		playSound("Mfeu", sfTrue);
		playSound("Mscore", sfTrue);
		for (int x = 0; x < playernber; x++)
		{
			if (player[x].life > 0)
			{
				playerWon = x;
				break;
			}
		}
	}

	sfRectangleShape_setPosition(rct_endGBG, BG_pos);
	sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_endGBG, NULL);
	if (!endOfMap)
	{
		for (int i = 0; i < NBR_ELEM_GB; i++)
		{
			if (Gb[i].canDisplay == sfFalse)continue;
			switch (i)
			{
			case EG_NAME_PLAYER:
				Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 100.f);
				sfText_setCharacterSize(txt_endGame, 60);
				sprintf(bufferGb, "Player %d WON !", playerWon + 1);
				Gb[i].string = bufferGb;
				break;
			case EG_NBR_BOMBE:
				Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 200.f);
				sfText_setCharacterSize(txt_endGame, 30);
				sprintf(bufferGb, "Bombs placed %d", player[playerWon].numBombePlaced);
				Gb[i].string = bufferGb;
				break;
			case EG_NBR_SPEED:
				Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 300.f);
				sfText_setCharacterSize(txt_endGame, 30);
				sprintf(bufferGb, "Nbr of speed used %d", player[playerWon].countspeed);
				Gb[i].string = bufferGb;
				break;
			case EG_NBR_EVIL:
				Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 400.f);
				sfText_setCharacterSize(txt_endGame, 30);
				sprintf(bufferGb, "Nbr of evil used %d", player[playerWon].countEvil);
				Gb[i].string = bufferGb;
				break;
			case EG_NBR_PUSH:
				Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 500.f);
				sfText_setCharacterSize(txt_endGame, 30);
				sprintf(bufferGb, "Nbr of push used %d", player[playerWon].countPush);
				Gb[i].string = bufferGb;
				break;
			}

			sfText_setPosition(txt_endGame, Gb[i].pos);
			sfText_setString(txt_endGame, Gb[i].string);
			sfRenderWindow_drawText(_window->renderWindow, txt_endGame, NULL);
		}

		for (int x = 0; x < playernber; x++)
		{
			if (!Gb2[x].canDisplay) continue;
			Gb2[x].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 150.0f + 100.f * x);
			if (x == 0)Gb2[x].string = "Player 1 :";
			if (x == 1)Gb2[x].string = "Player 2 :";
			if (x == 2)Gb2[x].string = "Player 3 :";
			if (x == 3)Gb2[x].string = "Player 4 :";

			sfText_setCharacterSize(txt_endGame, 30);
			sfText_setPosition(txt_endGame, Gb2[x].pos);
			sfText_setString(txt_endGame, Gb2[x].string);

			sfRenderWindow_drawText(_window->renderWindow, txt_endGame, NULL);
		}

		for (int a = 0; a < playernber; a++)
		{
			if (!Gb2[0].canDisplay) continue;
			for (int y = 0; y < player[a].score; y++)
			{
				sfCircleShape_setPosition(crl_trophy, vector2f(BG_pos.x + 400.f + y * 50.0f, BG_pos.y + 150.0f + 100.f * a));
				sfRenderWindow_drawCircleShape(_window->renderWindow, crl_trophy, NULL);
			}
		}
	}
	else
	{
		sfText_setPosition(txt_endGame, vector2f(BG_pos.x + 200.f, BG_pos.y + 100.f));
		sprintf(bufferGb, "PLAYER %d IS THE WINNER !!", playerWon + 1);
		sfText_setString(txt_endGame, bufferGb);

		sfRenderWindow_drawText(_window->renderWindow, txt_endGame, NULL);
	}
}
