#include "map.h"

sfRectangleShape* rct_backGround;
sfRectangleShape* rct_Block;

void loadMap()
{
	FILE* file = fopen("../Ressources/Save/saveMap.bin", "r");
	if (file == NULL)
	{
		printf("Fichier introuvable loadMap");
	}
	else
	{
		//fread(map, sizeof(Map_struct), TAILLE_MAPY * TAILLE_MAPX, file);
		fread(mapTop, sizeof(Map_struct), TAILLE_MAPY * TAILLE_MAPX, file);
		fclose(file);
	}
}

void defaultMap()
{
	for (int j = 0; j < TAILLE_MAPY; j++)
	{
		for (int i = 0; i < TAILLE_MAPX; i++)
		{
			//map[j][i].color = sfBlack;
			//map[j][i].isSolid = sfFalse;
			//map[j][i].id = BLOCK_NOTHING;

			mapTop[j][i].color = sfBlack;
			mapTop[j][i].isSolid = sfFalse;
			mapTop[j][i].id = BLOCK_NOTHING_TOP;
		}
	}
	FILE* file = fopen("../Ressources/Save/saveMap.bin", "w");
//	fwrite(map, sizeof(Map_struct), TAILLE_MAPY * TAILLE_MAPX, file);
	fwrite(mapTop, sizeof(Map_struct), TAILLE_MAPY * TAILLE_MAPX, file);
	fclose(file);
}

void initMap()
{
	rct_Block = sfRectangleShape_create();
	sfRectangleShape_setSize(rct_Block, vector2f(TAILLE_BLOCK, TAILLE_BLOCK));

	rct_backGround = sfRectangleShape_create();
	sfRectangleShape_setFillColor(rct_backGround, sfColor_fromRGBA(0, 100, 0, 255));
	sfRectangleShape_setPosition(rct_backGround, vector2f(0.f, 0.f));
	sfRectangleShape_setSize(rct_backGround, vector2f(TAILLE_MAPX * TAILLE_BLOCK, TAILLE_MAPY * TAILLE_BLOCK));
	//defaultMap();
	loadMap();
}

void updateMap()
{

}

void displayMap(Window* _window)
{
	sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_backGround, NULL);

	//for (int j = 0; j < TAILLE_MAPY; j++)
	//{
	//	for (int i = 0; i < TAILLE_MAPX; i++)
	//	{
	//		switch (map[j][i].id) 
	//		{
	//		case BLOCK_BOMBE:
	//			map[j][i].color = sfColor_fromRGBA(175, 175, 175, 255);
	//			break;
	//		case BLOCK_FIRE:
	//			map[j][i].color = sfRed;
	//			break;
	//		case BLOCK_NOTHING:
	//			map[j][i].color = sfBlack;
	//			break;
	//		}
	//		sfRectangleShape_setFillColor(rct_Block, map[j][i].color);
	//		sfRectangleShape_setPosition(rct_Block, vector2f(i * TAILLE_BLOCK, j * TAILLE_BLOCK));
	//		sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_Block, NULL);

	//	}
	//}

	for (int j = 0; j < TAILLE_MAPY; j++)
	{
		for (int i = 0; i < TAILLE_MAPX; i++)
		{
			switch (mapTop[j][i].id)
			{
			case BLOCK_WALL:
				mapTop[j][i].color = sfColor_fromRGBA(100, 100, 100, 255);
				break;
			case BLOCK_BRICK:
				mapTop[j][i].color = sfYellow;
				break;
			case BLOCK_NOTHING_TOP:
				mapTop[j][i].color = sfColor_fromRGBA(0, 100, 0, 255);
				break;
			}
			sfRectangleShape_setFillColor(rct_Block, mapTop[j][i].color);
			sfRectangleShape_setPosition(rct_Block, vector2f(i * TAILLE_BLOCK, j * TAILLE_BLOCK));
			sfRenderWindow_drawRectangleShape(_window->renderWindow, rct_Block, NULL);
		}
	}
}

sfBool isCollision(sfVector2f _pos, Direction _direction)
{
	sfVector2i posMap = vector2i((int)_pos.x / TAILLE_BLOCK,(int) _pos.y / TAILLE_BLOCK);
	switch (_direction)
	{
	case UP:
		if (mapTop[posMap.y-1][posMap.x].isSolid)
			return sfTrue;
		break;
	case DOWN:
		if (mapTop[posMap.y + 1][posMap.x].isSolid)
			return sfTrue;
		break;
	case LEFT:
		if (mapTop[posMap.y][posMap.x - 1].isSolid)
			return sfTrue;
		break;
	case RIGHT:
		if (mapTop[posMap.y - 1][posMap.x + 1].isSolid)
			return sfTrue;
		break;
	}
	return sfFalse;
}
