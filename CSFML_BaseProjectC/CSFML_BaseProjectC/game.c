#include "game.h"
#include "textureManager.h"
#include "viewManager.h"
#include "stateManager.h"
#include "Gamepad.h"
#include "pause.h"
#include "map.h"
#include <Windows.h>
#include "player.h"


void initGame(Window* _window)
{
	Texture_Onload(GAME);

	initMap();
	initPlayer();
	SetViewPosition(mainView, vector2f(960.f, 540.f));
	
	
	GamepadDetection();

	

	w.state = sfTrue;

}

void updateGame(Window* _window)
{
	updateMap();
	updatePlayer();
}

void displayGame(Window* _window)
{
	displayMap(_window);
	displayPlayer(_window);

}

void deinitGame()
{
	deinitPause();

	RemoveWasteTexture();
}