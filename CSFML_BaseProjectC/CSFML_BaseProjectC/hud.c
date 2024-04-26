#include "hud.h"
#include "gamepad.h"
#include "fontManager.h"
#include "player.h"

#define NBR_ELEMENT_HUD 20

sfRectangleShape* rct_hud;
sfText* txt_hud;

sfBool isDraw;

typedef enum
{
	BG_PLAYER1,
	BG_PLAYER2,
	BG_PLAYER3,
	BG_PLAYER4,
};

typedef enum {
	NBR_BOMBE1,
	NBR_BOMBE_BLOC1,
	CAN_MOVE1,
	PLAYER1,
	SPEED1,

	NBR_BOMBE2,
	NBR_BOMBE_BLOC2,
	CAN_MOVE2,
	PLAYER2,
	SPEED2,

	NBR_BOMBE3,
	NBR_BOMBE_BLOC3,
	CAN_MOVE3,
	PLAYER3,
	SPEED3,

	NBR_BOMBE4,
	NBR_BOMBE_BLOC4,
	CAN_MOVE4,
	PLAYER4,
	SPEED4,
};

typedef struct {
	sfVector2f pos;
	sfVector2f size;
	sfColor color;
	char* string;
}HudRec_struct;

HudRec_struct HugRec[4];
HudRec_struct HudText[NBR_ELEMENT_HUD];
char buffer[50];

int HUDminutes;
float HUDsecondes;
float timer_draw;

void initHud()
{
	HUDminutes = 1;
	HUDsecondes = 59.0f;
	isDraw = sfFalse;
	timer_draw = 0.0f;
	rct_hud = sfRectangleShape_create();
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0 :
			HugRec[i].color = sfWhite;
			break;
		case 1 : 
			HugRec[i].color = sfCyan ; 
			break;
		case 2:
			HugRec[i].color = sfColor_fromRGBA(255, 127, 0, 255);
			break;
		case 3:
			HugRec[i].color = sfBlack;
			break;
		}
		HugRec[i].pos = vector2f(1000.0f, 100.0f + 200.f * i);
		HugRec[i].size = vector2f(500.0f, 190.0f);
		HugRec[i].string = NULL;
	}

	for (int x = 0; x < NBR_ELEMENT_HUD; x++)
	{
		HudText[x].color = sfWhite;

		switch (x)
		{
		case NBR_BOMBE1:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 50.f, HugRec[0].pos.y + 80.f);
			HudText[x].color = sfBlack;
			break;
		case NBR_BOMBE2:
			HudText[x].pos = vector2f(HugRec[1].pos.x + 50.f, HugRec[1].pos.y + 80.f);

			break;
		case NBR_BOMBE3:
			HudText[x].pos = vector2f(HugRec[2].pos.x + 50.f, HugRec[2].pos.y + 80.f);

			break;
		case NBR_BOMBE4:
			HudText[x].pos = vector2f(HugRec[3].pos.x + 50.f, HugRec[3].pos.y + 80.f);

			break;
		case NBR_BOMBE_BLOC1:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[0].pos.y + 80.f);
			HudText[x].color = sfBlack;
			break;
		case NBR_BOMBE_BLOC2:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[1].pos.y + 80.f);

			break;
		case NBR_BOMBE_BLOC3:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[2].pos.y + 80.f);

			break;
		case NBR_BOMBE_BLOC4:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[3].pos.y + 80.f);

			break;
		case PLAYER1:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 20.f , HugRec[0].pos.y + 20.f);
			HudText[x].color = sfBlack;

			break;
		case PLAYER2:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 20.f, HugRec[1].pos.y + 20.f);

			break;
		case PLAYER3:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 20.f, HugRec[2].pos.y + 20.f);

			break;
		case PLAYER4:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 20.f, HugRec[3].pos.y + 20.f);

			break;
		case CAN_MOVE1:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 50.f, HugRec[0].pos.y + 120.f);
			HudText[x].color = sfBlack;
			break;
		case CAN_MOVE2:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 50.f, HugRec[1].pos.y + 120.f);
			break;
		case CAN_MOVE3:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 50.f, HugRec[2].pos.y + 120.f);
			break;
		case  CAN_MOVE4:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 50.f, HugRec[3].pos.y + 120.f);
			break;
		case SPEED1:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[0].pos.y + 120.f);
			HudText[x].color = sfBlack;
			break;
		case SPEED2:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[1].pos.y + 120.f);
			break;
		case SPEED3:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[2].pos.y + 120.f);
			break;
		case SPEED4:
			HudText[x].pos = vector2f(HugRec[0].pos.x + 250.f, HugRec[3].pos.y + 120.f);
			break;
		}
	}
	txt_hud = sfText_create();
	sfText_setFont(txt_hud, getDefaultFont());
}

void updateHud(Window* _window)
{
	if(!isDraw)
		HUDsecondes -=getDeltaTime();
	if (HUDminutes == 0 && HUDsecondes < 0.0f)
	{
		isDraw = sfTrue;
		timer_draw += getDeltaTime();
		if(timer_draw > 2.f)
			changeState(_window, GAME);
	}
	else
	{
		if (HUDsecondes < 0.0f)
		{
			HUDminutes--;
			HUDsecondes = 59.f;
		}
	}
}

void displayHud(Window* _window)
{
	for (int i = 0; i < playernber; i++)
	{
		sfRectangleShape_setPosition(rct_hud, HugRec[i].pos);
		sfRectangleShape_setFillColor(rct_hud, HugRec[i].color);
		sfRectangleShape_setOutlineColor(rct_hud, sfWhite);
		sfRectangleShape_setOutlineThickness(rct_hud, 1.0f);
		sfRectangleShape_setSize(rct_hud, HugRec[i].size);

		sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_hud, NULL);
	}

	for (int x = 0; x < playernber*5; x++)
	{
		switch (x)
		{
		case NBR_BOMBE1:
			sprintf(buffer, "BOMBS %d", player[0].numOfBombe);
			HudText[x].string = buffer;
			break;
		case NBR_BOMBE2:
			sprintf(buffer, "BOMBS %d", player[1].numOfBombe);
			HudText[x].string = buffer;

			break;
		case NBR_BOMBE3:
			sprintf(buffer, "BOMBS %d", player[2].numOfBombe);
			HudText[x].string = buffer;

			break;
		case NBR_BOMBE4:
			sprintf(buffer, "BOMBS %d", player[3].numOfBombe);
			HudText[x].string = buffer;

			break;
		case NBR_BOMBE_BLOC1:
			sprintf(buffer, "RANGE %d", player[0].numCaseBombe);
			HudText[x].string = buffer;
			break;
		case NBR_BOMBE_BLOC2:
			sprintf(buffer, "RANGE %d", player[1].numCaseBombe);
			HudText[x].string = buffer;
			break;
		case NBR_BOMBE_BLOC3:
			sprintf(buffer, "RANGE %d", player[2].numCaseBombe);
			HudText[x].string = buffer;
			break;
		case NBR_BOMBE_BLOC4:
			sprintf(buffer, "RANGE %d", player[3].numCaseBombe);
			HudText[x].string = buffer;
			break;
		case PLAYER1:
			HudText[x].string = "PLAYER 1";
			break;
		case PLAYER2:
			HudText[x].string = "PLAYER 2";
			break;
		case PLAYER3:
			HudText[x].string = "PLAYER 3";
			break;
		case PLAYER4:
			HudText[x].string = "PLAYER 4";
			break;
		case CAN_MOVE1:
			if (player[0].isUsingPushBombe)
				HudText[x].string = "PUSH YES";
			else
				HudText[x].string = "PUSH NO";
			break;
		case CAN_MOVE2:
			if (player[1].isUsingPushBombe)
				HudText[x].string = "PUSH YES";
			else
				HudText[x].string = "PUSH NO";
			break;
		case CAN_MOVE3:
			if (player[2].isUsingPushBombe)
				HudText[x].string = "PUSH YES";
			else
				HudText[x].string = "PUSH NO";
			break;
		case  CAN_MOVE4:
			if (player[3].isUsingPushBombe)
				HudText[x].string = "PUSH YES";
			else
				HudText[x].string = "PUSH NO";
			break;
		case SPEED1:
			if (player[0].isUsingSpeed)
				HudText[x].string = "SPEED YES";
			else
				HudText[x].string = "SPEED NO";
			break;
		case SPEED2:
			if (player[1].isUsingSpeed)
				HudText[x].string = "SPEED YES";
			else
				HudText[x].string = "SPEED NO";
			break;
		case SPEED3:
			if (player[2].isUsingSpeed)
				HudText[x].string = "SPEED YES";
			else
				HudText[x].string = "SPEED NO";
			break;
		case SPEED4:
			if (player[3].isUsingSpeed)
				HudText[x].string = "SPEED YES";
			else
				HudText[x].string = "SPEED NO";
			break;
		}
		sfText_setString(txt_hud, HudText[x].string);
		sfText_setPosition(txt_hud, HudText[x].pos);
		sfText_setFillColor(txt_hud, HudText[x].color);
		sfText_setCharacterSize(txt_hud, 30);

		sfRenderWindow_drawText(_window->renderWindow, txt_hud, NULL);
	}

	sprintf(buffer, "Time remaining %d : %.0f", HUDminutes, HUDsecondes);
	sfText_setString(txt_hud, buffer);
	sfText_setPosition(txt_hud, vector2f(200.f, 900.f));
	sfRenderWindow_drawText(_window->renderWindow, txt_hud, NULL);

	if (isDraw)
	{
		sfText_setString(txt_hud, "DRAW !!!");
		sfText_setPosition(txt_hud, vector2f(200.f, 1000.f));
		sfRenderWindow_drawText(_window->renderWindow, txt_hud, NULL);
	}
}
