#include "stateManager.h"
#include "ressourcesManager.h"
#include "textureManager.h"
#include "soundManager.h"
#include "pause.h"
#include "menu.h"
#include "game.h"
#include "dialogBox.h"
#include "options.h"
#include "viewManager.h"
#include "endGame.h"
#include "createParticles.h"

void stateInit(Window* _window)
{
	static sfBool firstload = sfFalse;
	if (!firstload)
	{
		firstLoad2 = sfFalse;
		OnLoad("../Ressources/ressources.load");
		Texture_Onload(ALL);
		Sound_Onload(ALL);
		spLoading = sfSprite_create();
		sfSprite_setTexture(spLoading, GetTexture("loading"), sfTrue);
		sfIntRect AnimRect = { 0, 0, 128, 128 };
		sfSprite_setOrigin(spLoading, vector2f(64.0f, 64.0f));
		sfSprite_setPosition(spLoading, vector2f(mainView->PosView.x, mainView->PosView.y));
		sfSprite_setTextureRect(spLoading, AnimRect);
		sfRenderWindow_setMouseCursorVisible(_window->renderWindow, sfFalse);

		setSoundVolume(10.0f);
		setMusicVolume(10.0f);
		w.state = sfTrue;
		fontScore = sfFont_createFromFile("../Ressources/Fonts/full_Pack_2025.ttf");
		
		firstload = sfTrue;
	}

	if (!onePass)
	{
		isDialogBox = sfFalse;
		onePass = sfTrue;
		if (state == INTRO)
		{
			
		}
		if (state == MENU)
		{
			initMenu(_window);
			initOptions(_window);
		}
		if (state == GAME)
		{
			w.mutex = sfMutex_create();
			w.state = sfFalse;
			loadingThread = sfThread_create(&initGame, _window);
			sfThread_launch(loadingThread);
			initPause(_window);
			initOptions(_window);
			initEndGame();
			initParticlesSystem();
		}
		if (state == EDITOR)
		{

		}
		if (state == END)
		{
			
		}
	}
}

void stateEventUpdate(Window* _window, sfEvent* _event)
{
	if (w.state)
	{
			if (state == INTRO)
			{

			}
			else if (state == MENU)
			{
				
			}
			else if (state == GAME)
			{
				
			}
			else if (state == END)
			{

			}
		
	}
}

void stateUpdate(Window* _window)
{
	if (w.state)
	{
		if (sfKeyboard_isKeyPressed(sfKeySpace))
		{
			changeState(_window,GAME);
		}
		if (!isDialogBox)
		{
			if (state == INTRO)
			{

			}
			else if (state == MENU)
			{
				if (isOption)
					updateOptions(_window);
				else
					updateMenu(_window);
			}
			else if (state == GAME)
			{
				if (isPaused)
				{
					if (isOption)
						updateOptions(_window);
					else
					updatePause(_window);	
				}	
				else
				{
					updateParticlesSystem();
					if (isEndGame)
					{
						updateEndGame(_window);
					}
					else
						updateGame(_window);
				}
			}
			else if (state == EDITOR)
			{
			}
			else if (state == END)
			{

			}
		}
		else
		{
			dialogBoxUpdate(_window);
		}
	}
	else if (!w.state)
	{
		static sfIntRect AnimRect = { 0, 0, 128, 128 };
		static int frame = 0;
		static float timer = 0.0f;
		timer += getDeltaTime();

		sfMutex_lock(w.mutex);
		sfSprite_setOrigin(spLoading, vector2f(64.0f, 64.0f));
		sfSprite_setPosition(spLoading, vector2f(mainView->PosView.x, mainView->PosView.y));
		sfSprite_setTextureRect(spLoading, AnimRect);
		if (timer > 0.1f)
		{
			frame++;
			if (frame > 8)
				frame = 0;
			AnimRect.left = frame * 128;
			
			timer = 0.0f;
		}
		sfMutex_unlock(w.mutex);
	}
}

void stateDisplay(Window* _window)
{
	if (w.state)
	{
		if (state == INTRO)
		{

		}
		if (state == MENU)
		{
			displayMenu(_window);
			if (isOption)
			{
				displayOptions(_window);
			}
			if (isDialogBox)
			{
				dialogBoxDisplay(_window);
			}
		}
		if (state == GAME)
		{
			displayGame(_window);
			if(!isEndGame)
				displayParticlesSystem(_window);
			if (isEndGame)
			{
				displayEndGame1(_window);
				displayParticlesSystem(_window);
				displayEndGame2(_window);
			}
			if (isPaused)
			{
				displayPause(_window);
				if (isOption)
				{
					displayOptions(_window);
				}
			}
			if (isDialogBox)
			{
				dialogBoxDisplay(_window);
			}
		}
		else if (state == EDITOR)
		{
		}
		if (state == END)
		{

		}
	}
	else if (!w.state)
	{
		sfMutex_lock(w.mutex);
			
		sfRenderWindow_drawSprite(_window->renderWindow, spLoading, NULL);
		
		sfMutex_unlock(w.mutex);
	}
}

void stateDeinit(Window* _window)
{
	if (state == INTRO)
	{

	}
	if (state == MENU)
	{
		deinitMenu();
		deinitOptions();
	}
	if (state == GAME)
	{
		deinitGame();
		deinitOptions();
	}
	if (state == END)
	{

	}
}

void changeState(Window* _window, State _state)
{
	stateDeinit(_window);
	state = _state;
	onePass = sfFalse;
	stateInit(_window);
}

void togglePause()
{
	isPaused = !isPaused;
}

void toggleOptions()
{
	isOption = !isOption;
}

void toggleEndGame()
{
	isEndGame = !isEndGame;
}
