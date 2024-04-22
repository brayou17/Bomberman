#include "options.h"
#include "soundManager.h"
#include "stateManager.h"
#include "viewManager.h"

sfRectangleShape* backgroundOpt;
sfRectangleShape* sfxVolumeBar;
sfRectangleShape* MusicVolumeBar;
sfRectangleShape* fullscreenTick;
sfText* Option;
sfText* Fullscreen;
sfText* SfxSoundTxt;
sfText* MusicSoundTxt;
sfText* returnTxt;
int optionSelect;


void initOptions(Window* _window)
{
	backgroundOpt = sfRectangleShape_create();
	sfRectangleShape_setSize(backgroundOpt, vector2f(500.0f, 300.0f));
	sfRectangleShape_setFillColor(backgroundOpt, sfBlack);
	sfRectangleShape_setOutlineColor(backgroundOpt, sfWhite);
	sfRectangleShape_setOutlineThickness(backgroundOpt, 2.0f);
	sfRectangleShape_setOrigin(backgroundOpt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).width / 2.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).height / 2.0f));
	sfRectangleShape_setPosition(backgroundOpt, mainView->PosView);

	Option = sfText_create();
	sfText_setFont(Option, getDefaultFont());
	sfText_setColor(Option, sfRed);
	sfText_setString(Option, "OPTIONS");
	sfText_setCharacterSize(Option, 30);
	sfText_setOrigin(Option, vector2f(sfText_getGlobalBounds(Option).width / 2.0f, sfText_getGlobalBounds(Option).height / 2.0f));
	sfText_setPosition(Option, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + sfRectangleShape_getGlobalBounds(backgroundOpt).width / 2.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 20.0f));

	returnTxt = sfText_create();
	sfText_setFont(returnTxt, getDefaultFont());
	sfText_setColor(returnTxt, sfWhite);
	sfText_setString(returnTxt, "RETOUR");
	sfText_setCharacterSize(returnTxt, 20);
	sfText_setOrigin(returnTxt, vector2f(sfText_getGlobalBounds(returnTxt).width / 2.0f, sfText_getGlobalBounds(returnTxt).height / 2.0f));
	sfText_setPosition(returnTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + sfRectangleShape_getGlobalBounds(backgroundOpt).width / 2.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + sfRectangleShape_getGlobalBounds(backgroundOpt).height - 40.0f));


	Fullscreen = sfText_create();
	sfText_setFont(Fullscreen, getDefaultFont());
	sfText_setColor(Fullscreen, sfWhite);
	sfText_setString(Fullscreen, "FullScreen : ");
	sfText_setCharacterSize(Fullscreen, 20);
	sfText_setPosition(Fullscreen, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f , sfRectangleShape_getGlobalBounds(backgroundOpt).top + 80.0f));


	SfxSoundTxt = sfText_create();
	sfText_setFont(SfxSoundTxt, getDefaultFont());
	sfText_setColor(SfxSoundTxt, sfWhite);
	sfText_setString(SfxSoundTxt, "Sfx Volume : ");
	sfText_setCharacterSize(SfxSoundTxt, 20);
	sfText_setPosition(SfxSoundTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f,  sfRectangleShape_getGlobalBounds(backgroundOpt).top + 140.0f));


	MusicSoundTxt = sfText_create();
	sfText_setFont(MusicSoundTxt, getDefaultFont());
	sfText_setColor(MusicSoundTxt, sfWhite);
	sfText_setString(MusicSoundTxt, "Music Volume : ");
	sfText_setCharacterSize(MusicSoundTxt, 20);
	sfText_setPosition(MusicSoundTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 200.0f));


	sfxVolumeBar = sfRectangleShape_create();
	sfRectangleShape_setSize(sfxVolumeBar, vector2f(getSFXVolume(), 20.0f));
	sfRectangleShape_setFillColor(sfxVolumeBar, sfWhite);
	sfRectangleShape_setPosition(sfxVolumeBar, vector2f( sfText_getGlobalBounds(SfxSoundTxt).left + sfText_getGlobalBounds(SfxSoundTxt).width + 10.0f , sfText_getGlobalBounds(SfxSoundTxt).top));

	MusicVolumeBar = sfRectangleShape_create();
	sfRectangleShape_setSize(MusicVolumeBar, vector2f(getMusicVolume(), 20.0f));
	sfRectangleShape_setFillColor(MusicVolumeBar, sfWhite);
	sfRectangleShape_setPosition(MusicVolumeBar, vector2f(sfText_getGlobalBounds(MusicSoundTxt).left + sfText_getGlobalBounds(MusicSoundTxt).width + 10.0f, sfText_getGlobalBounds(MusicSoundTxt).top));

	fullscreenTick = sfRectangleShape_create();
	sfRectangleShape_setSize(fullscreenTick, vector2f(20.0f, 20.0f));
	if (IsFullscreen(_window))
		sfRectangleShape_setFillColor(fullscreenTick, sfWhite);
	else
		sfRectangleShape_setFillColor(fullscreenTick, sfBlack);
	sfRectangleShape_setOutlineColor(fullscreenTick, sfWhite);
	sfRectangleShape_setOutlineThickness(fullscreenTick, 2.0f);
	sfRectangleShape_setPosition(fullscreenTick, vector2f(sfText_getGlobalBounds(Fullscreen).left + sfText_getGlobalBounds(Fullscreen).width + 10.0f, sfText_getGlobalBounds(Fullscreen).top));


	optionSelect = 0;
}

void updateOptions(Window* _window)
{
	static float timer = 0.0f;
	timer += getDeltaTime();

	if (sfKeyboard_isKeyPressed(sfKeyEscape) && timer > 0.2f)
	{
		toggleOptions();
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyDown) && timer > 0.2f)
	{
		optionSelect++;
		if (optionSelect > 3)
			optionSelect = 0;
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyUp) && timer > 0.2f)
	{
		optionSelect--;
		if (optionSelect < 0)
			optionSelect = 3;
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyEnter) && timer > 0.2f)
	{
		if (optionSelect == 0)
		{
			ToggleFullscreen(_window);
		}
		if (optionSelect == 3)
		{
			toggleOptions();
		}
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyRight) && timer > 0.1f)
	{
		if (optionSelect == 1)
		{
			if(getSFXVolume() < 100 )
				setSoundVolume(getSFXVolume() + 1.0f);
		}
		else if (optionSelect == 2)
		{
			if (getMusicVolume() < 100)
				setMusicVolume(getMusicVolume() + 1.0f);
		}
		timer = 0.0f;
	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft) && timer > 0.1f)
	{
		if (optionSelect == 1)
		{
			if (getSFXVolume() > 0)
				setSoundVolume(getSFXVolume() - 1.0f);
		}
		else if (optionSelect == 2)
		{
			if (getMusicVolume() > 0)
				setMusicVolume(getMusicVolume() - 1.0f);
		}
		timer = 0.0f;
	}

	if (optionSelect == 0)
	{
		sfText_setColor(Fullscreen, sfRed);
		sfText_setColor(SfxSoundTxt, sfWhite);
		sfText_setColor(MusicSoundTxt, sfWhite);
		sfText_setColor(returnTxt, sfWhite);
	}
	else if (optionSelect == 1)
	{
		sfText_setColor(Fullscreen, sfWhite);
		sfText_setColor(SfxSoundTxt, sfRed);
		sfText_setColor(MusicSoundTxt, sfWhite);
		sfText_setColor(returnTxt, sfWhite);
	}
	else if (optionSelect == 2)
	{
		sfText_setColor(Fullscreen, sfWhite);
		sfText_setColor(SfxSoundTxt, sfWhite);
		sfText_setColor(MusicSoundTxt, sfRed);
		sfText_setColor(returnTxt, sfWhite);
	}
	else if (optionSelect == 3)
	{
		sfText_setColor(Fullscreen, sfWhite);
		sfText_setColor(SfxSoundTxt, sfWhite);
		sfText_setColor(MusicSoundTxt, sfWhite);
		sfText_setColor(returnTxt, sfRed);
	}

	sfText_setPosition(Option, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + sfRectangleShape_getGlobalBounds(backgroundOpt).width / 2.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 20.0f));
	sfText_setPosition(Fullscreen, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 80.0f));
	sfText_setPosition(SfxSoundTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 140.0f));
	sfText_setPosition(MusicSoundTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + 20.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + 200.0f));
	sfText_setPosition(returnTxt, vector2f(sfRectangleShape_getGlobalBounds(backgroundOpt).left + sfRectangleShape_getGlobalBounds(backgroundOpt).width / 2.0f, sfRectangleShape_getGlobalBounds(backgroundOpt).top + sfRectangleShape_getGlobalBounds(backgroundOpt).height - 40.0f));

	sfRectangleShape_setSize(sfxVolumeBar, vector2f(getSFXVolume(), 20.0f));
	sfRectangleShape_setSize(MusicVolumeBar, vector2f(getMusicVolume(), 20.0f));
	sfRectangleShape_setPosition(backgroundOpt, mainView->PosView);
	sfRectangleShape_setPosition(fullscreenTick, vector2f(sfText_getGlobalBounds(Fullscreen).left + sfText_getGlobalBounds(Fullscreen).width + 10.0f, sfText_getGlobalBounds(Fullscreen).top));
	sfRectangleShape_setPosition(MusicVolumeBar, vector2f(sfText_getGlobalBounds(MusicSoundTxt).left + sfText_getGlobalBounds(MusicSoundTxt).width + 10.0f, sfText_getGlobalBounds(MusicSoundTxt).top));
	sfRectangleShape_setPosition(sfxVolumeBar, vector2f(sfText_getGlobalBounds(SfxSoundTxt).left + sfText_getGlobalBounds(SfxSoundTxt).width + 10.0f, sfText_getGlobalBounds(SfxSoundTxt).top));


	if (IsFullscreen(_window))
		sfRectangleShape_setFillColor(fullscreenTick, sfWhite);
	else
		sfRectangleShape_setFillColor(fullscreenTick, sfBlack);
}

void displayOptions(Window* _window)
{
	sfRenderWindow_drawRectangleShape(_window->renderWindow, backgroundOpt, NULL );
	sfRenderWindow_drawRectangleShape(_window->renderWindow, fullscreenTick, NULL);
	sfRenderWindow_drawRectangleShape(_window->renderWindow, sfxVolumeBar, NULL);
	sfRenderWindow_drawRectangleShape(_window->renderWindow, MusicVolumeBar, NULL);
	sfRenderWindow_drawText(_window->renderWindow, Option, NULL);
	sfRenderWindow_drawText(_window->renderWindow, Fullscreen, NULL);
	sfRenderWindow_drawText(_window->renderWindow, SfxSoundTxt, NULL);
	sfRenderWindow_drawText(_window->renderWindow, MusicSoundTxt, NULL);
	sfRenderWindow_drawText(_window->renderWindow, returnTxt, NULL);
}

void deinitOptions()
{
	sfRectangleShape_destroy(backgroundOpt);
	sfRectangleShape_destroy(fullscreenTick);
	sfRectangleShape_destroy(sfxVolumeBar);
	sfRectangleShape_destroy(MusicVolumeBar);
	sfText_destroy(Option);
	sfText_destroy(Fullscreen);
	sfText_destroy(SfxSoundTxt);
	sfText_destroy(MusicSoundTxt);
	sfText_destroy(returnTxt);
}