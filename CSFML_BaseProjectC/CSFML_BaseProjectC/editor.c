//#include "editor.h"
//#include "map.h"
//
//void initEditor()
//{
//	initMap();
//
//}
//
//void updateEditor(Window* _window)
//{
//	updateMap();
//
//}
//
//void displayEditor(Window* _window)
//{
//	displayMap(_window);
//
//}

#include "editor.h"
#include "map.h"

int choiceBlockMapTop;

float timer_editeur;

sfBool isChosingMap;

sfRectangleShape* rct_editeur;
sfTexture* txr_texture;

void saveMap();


void initEditor()
{
	initMap();
	timer_editeur = 0.0f;
	choiceBlockMapTop = 3;

	rct_editeur = sfRectangleShape_create();
	sfRectangleShape_setSize(rct_editeur, vector2f(TAILLE_BLOCK, TAILLE_BLOCK));

}

void updateEditor(Window* _window)
{
	updateMap();
	float delta = getDeltaTime();
	timer_editeur += delta;

		if (sfKeyboard_isKeyPressed(sfKeyLeft) && timer_editeur > 0.2f)
		{
			if (choiceBlockMapTop == 5) choiceBlockMapTop = 3;
			else choiceBlockMapTop++;
			timer_editeur = 0.0f;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyRight) && timer_editeur > 0.2f)
		{
			if (choiceBlockMapTop == 3) choiceBlockMapTop = 5;
			else choiceBlockMapTop--;
			timer_editeur = 0.0f;
		}

		sfVector2i mousePos = vector2i(sfMouse_getPosition(_window->renderWindow).x / TAILLE_BLOCK, sfMouse_getPosition(_window->renderWindow).y / TAILLE_BLOCK);

		if (sfMouse_isButtonPressed(sfMouseLeft))
		{
			switch (choiceBlockMapTop)
			{
			case BLOCK_WALL:
				mapTop[mousePos.y][mousePos.x].canBeDestroyed = sfFalse;
				mapTop[mousePos.y][mousePos.x].canUpdate = sfTrue;
				mapTop[mousePos.y][mousePos.x].isSolid = sfTrue;
				break;
			case BLOCK_BRICK:
				mapTop[mousePos.y][mousePos.x].canBeDestroyed = sfTrue;
				mapTop[mousePos.y][mousePos.x].canUpdate = sfTrue;
				mapTop[mousePos.y][mousePos.x].isSolid = sfTrue;
				break;
			case BLOCK_NOTHING_TOP:
				mapTop[mousePos.y][mousePos.x].canBeDestroyed = sfFalse;
				mapTop[mousePos.y][mousePos.x].canUpdate = sfFalse;
				mapTop[mousePos.y][mousePos.x].isSolid = sfFalse;
				break;
			}
			mapTop[mousePos.y][mousePos.x].id = choiceBlockMapTop;
			timer_editeur = 0.0f;
		}



		if (sfKeyboard_isKeyPressed(sfKeyM) && timer_editeur > 0.2f)
		{
			saveMap();
			timer_editeur = 0.0f;
		}

		sfVector2f mouseF = getFloatMousePos(_window->renderWindow);

		sfRectangleShape_setPosition(rct_editeur, mouseF);

}

void displayEditor(Window* _window)
{
	displayMap(_window);
	switch (choiceBlockMapTop)
		{
		case 3:
			sfRectangleShape_setFillColor(rct_editeur, sfColor_fromRGBA(100, 100, 100, 255));
			break;
		case 4:
			sfRectangleShape_setFillColor(rct_editeur,sfYellow);
			break;
		case 5:
			sfRectangleShape_setFillColor(rct_editeur, sfColor_fromRGBA(0, 100, 0, 255));
			break;
		}
		sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_editeur, NULL);
}

void saveMap()
{
	FILE* file = fopen("../Ressources/Save/saveMap.bin", "w");
	if (file == NULL)
	{
		printf("Fichier introuvable pour defaultMap\n");
	}
	else
	{

		//fwrite(map, sizeof(Map_struct), 1, file);
		fwrite(mapTop, sizeof(Map_struct), TAILLE_MAPX * TAILLE_MAPY, file);

		printf("Fichier defaultMap save");
		fclose(file);
	}
}