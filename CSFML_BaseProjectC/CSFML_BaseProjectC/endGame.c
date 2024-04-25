#include "endGame.h"
#include "createParticles.h"
#include "fontManager.h"

sfRectangleShape* rct_endGBG;
sfRectangleShape* rct_endGAllBG;
sfVector2f BG_pos;

sfText* txt_endGame;
float alpha;

float timer_particles;
void initEndGame()
{
	timer_particles =0.0f;
	txt_endGame = sfText_create();
	sfText_setFont(txt_endGame, getDefaultFont());
	rct_endGBG = sfRectangleShape_create();
	rct_endGAllBG = sfRectangleShape_create();
	BG_pos = vector2f(600.f,-600.f);

	sfRectangleShape_setFillColor(rct_endGBG, sfColor_fromRGBA(20, 20, 20, 200));
	sfRectangleShape_setSize(rct_endGBG, vector2f(800.0f,600.f));

	alpha = 0;
	sfRectangleShape_setFillColor(rct_endGAllBG, sfColor_fromRGBA(0, 0, 0, alpha));
	sfRectangleShape_setSize(rct_endGAllBG, vector2f(1920.f, 1080.f));
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

	sfRectangleShape_setPosition(rct_endGBG, BG_pos);
	sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_endGBG, NULL);

}
