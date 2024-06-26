#include "menu.h"
#include "textureManager.h"
#include "gamepad.h"
#include "viewManager.h"
#include "soundManager.h"

sfSprite* spr_backGround;

sfFont* venture3D;

sfText* Play;
sfText* Options;
sfText* Quit;

int menuSelection;


void initMenu(Window* _window)
{
	Texture_Onload(MENU);
	Sound_Onload(MENU);

	stopSound("Mgame");
	stopSound("Mscore");
	stopSound("Mfeu");
	playSound("Mmenu", sfTrue);

	spr_backGround = sfSprite_create();
	sfSprite_setTexture(spr_backGround, GetTexture("menu"),sfTrue);


	venture3D = sfFont_createFromFile(FONT_PATH"bombe.ttf");

	SetViewPosition(mainView, vector2f(mainView->defaultVideoMode.x / 2.0f, mainView->defaultVideoMode.y / 2.0f));

	Play = sfText_create();
	Options = sfText_create();
	Quit = sfText_create();
	sfText_setFont(Play, venture3D);
	sfText_setFont(Options, venture3D);
	sfText_setFont(Quit, venture3D);
	sfText_setString(Play, "Play");
	sfText_setString(Options, "Options");
	sfText_setString(Quit, "Quit");
	sfText_setCharacterSize(Play, 72);
	sfText_setCharacterSize(Options, 72);
	sfText_setCharacterSize(Quit, 72);
	sfText_setPosition(Play, vector2f(mainView->PosView.x - 600.0f ,mainView->PosView.y - 100.0f));
	sfText_setPosition(Options, vector2f(mainView->PosView.x - 400.0f, mainView->PosView.y + 100.0f));
	sfText_setPosition(Quit, vector2f(mainView->PosView.x - 180.0f, mainView->PosView.y + 300.0f));

	GamepadDetection();
	menuSelection = 0;
}

void updateMenu(Window* _window)
{
	static float timer = 0.0f;
	timer += getDeltaTime();

	switch (menuSelection)
	{
	case 0:
		sfText_setColor(Play, sfRed);
		sfText_setColor(Options, sfBlack);
		sfText_setColor(Quit, sfBlack);
		break;
	case 1:
		sfText_setColor(Play, sfBlack);
		sfText_setColor(Options, sfRed);
		sfText_setColor(Quit, sfBlack);
		break;
	case 2:
		sfText_setColor(Play, sfBlack);
		sfText_setColor(Options, sfBlack);
		sfText_setColor(Quit, sfRed);
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 8; i++)
	{
		if (Gamepad_isButtonPressed(i, CROIX) && timer > 0.2f)
		{
			switch (menuSelection)
			{
			case 0:
				changeState(_window, GAME);
				break;
			case 1:
				toggleOptions();
				break;
			case 2:
				_window->isDone = sfTrue;
				break;
			default:
				break;
			}
			timer = 0.0f;
		}
		if ((Gamepad_isJoystickMoved(i, CROSSY) > 0 || Gamepad_isJoystickMoved(i, STICKLY) < 0) && timer > 0.2f)
		{
			menuSelection--;
			if (menuSelection < 0)
				menuSelection = 2;
			timer = 0.0f;
		}
		if ((Gamepad_isJoystickMoved(i, CROSSY) < 0 || Gamepad_isJoystickMoved(i, STICKLY) > 0) && timer > 0.2f)
		{
			menuSelection++;
			if (menuSelection > 2)
				menuSelection = 0;
			timer = 0.0f;
		}
	}

	if (sfKeyboard_isKeyPressed(sfKeyUp) && timer > 0.2f)
	{
		menuSelection--;
		if (menuSelection < 0)
			menuSelection = 2;
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyDown) && timer > 0.2f)
	{
		menuSelection++;
		if (menuSelection > 2)
			menuSelection = 0;
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyEnter) && timer > 0.2f)
	{
		switch (menuSelection)
		{
		case 0:
			changeState(_window, GAME);
			break;
		case 1:
			toggleOptions();
			break;
		case 2:
			_window->isDone = sfTrue;
			break;
		default:
			break;
		}
		timer = 0.0f;	
	}

}

void displayMenu(Window* _window)
{
	sfRenderWindow_drawSprite(_window->renderWindow, spr_backGround, NULL);
	sfRenderWindow_drawText(_window->renderWindow, Play, NULL);
	sfRenderWindow_drawText(_window->renderWindow, Options, NULL);
	sfRenderWindow_drawText(_window->renderWindow, Quit, NULL);
}

void deinitMenu()
{
	
	sfFont_destroy(venture3D);
	RemoveWasteTexture();
	sfText_destroy(Play);
	sfText_destroy(Options);
	sfText_destroy(Quit);
}