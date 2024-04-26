#include "game.h"
#include "textureManager.h"
#include "viewManager.h"
#include "stateManager.h"
#include "Gamepad.h"
#include "pause.h"
#include "map.h"
#include <Windows.h>
#include "player.h"
#include "bombe.h"
#include "explosion.h"
#include "bonus.h"
#include "hud.h"
#include "soundManager.h"


void initGame(Window* _window)
{
	Texture_Onload(GAME);
	Sound_Onload(GAME);
	stopSound("Mmenu");
	stopSound("Mscore");
	stopSound("Mfeu");
	playSound("Mgame",sfTrue);

	GamepadDetection();
	initMap();
	initPlayer();
	initExplosion();
	initBombe();
	initHud();
	initBonus();
	SetViewPosition(mainView, vector2f(960.f, 540.f));
	
	

	

	w.state = sfTrue;

}

void updateGame(Window* _window)
{
	updateMap();
	updatePlayer(_window);
	updateBombe();
	updateExplosion();
	updateBonus();
	updateHud();
}

void displayGame(Window* _window)
{
	displayMap(_window);
	displayBombe(_window);
	displayExplosion(_window);
	displayBonus(_window);
	displayPlayer(_window);
	displayHud(_window);

}

void deinitGame()
{
	deinitPause();

	RemoveWasteTexture();
}