#include "endGame.h"
#include "createParticles.h"
#include "fontManager.h"
#include "gamepad.h"
#include "player.h"

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
}EndGame_struct;

EndGame_struct Gb[NBR_ELEM_GB];

sfRectangleShape* rct_endGBG;
sfRectangleShape* rct_endGAllBG;
sfVector2f BG_pos;
sfBool isOnePassedEG;

sfText* txt_endGame;
float alpha;

float timer_particles;
char bufferGb[50];
int playerWon;

void initEndGame()
{
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
	
}

void updateEndGame()
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

	for (int i = 0; i < NBR_ELEM_GB; i++)
	{
		switch (i)
		{
		case EG_NAME_PLAYER:
			Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 100.f);
			sfText_setCharacterSize(txt_endGame, 60);
			sprintf(bufferGb, "Player %d WIN !", playerWon+1);
			Gb[i].string =  bufferGb;
			break;
		case EG_NBR_BOMBE:
			Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 200.f);
			sfText_setCharacterSize(txt_endGame, 30);
			sprintf(bufferGb, "Bombes placed %d", player[playerWon].numBombePlaced);
			Gb[i].string = bufferGb;
			break;
		case EG_NBR_SPEED:
			Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 300.f);
			sfText_setCharacterSize(txt_endGame, 30);
			sprintf(bufferGb, "Nbr of used speed %d", player[playerWon].countspeed);
			Gb[i].string = bufferGb;
			break;
		case EG_NBR_EVIL:
			Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 400.f);
			sfText_setCharacterSize(txt_endGame, 30);
			sprintf(bufferGb, "Nbr of used evil %d", player[playerWon].countEvil);
			Gb[i].string = bufferGb;
			break;
		case EG_NBR_PUSH:
			Gb[i].pos = vector2f(BG_pos.x + 200.f, BG_pos.y + 500.f);
			sfText_setCharacterSize(txt_endGame, 30);
			sprintf(bufferGb, "Nbr of used push %d", player[playerWon].countPush);
			Gb[i].string = bufferGb;
			break;
		}

		sfText_setPosition(txt_endGame, Gb[i].pos);
		sfText_setString(txt_endGame, Gb[i].string);
		sfRenderWindow_drawText(_window->renderWindow, txt_endGame, NULL);
	}
}
