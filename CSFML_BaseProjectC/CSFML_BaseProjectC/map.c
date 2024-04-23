#include "map.h"
#include "explosion.h"
#include "bonus.h"

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
int countS();
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
	//printf("count %d\n", countS());
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

//sfBool isCollision(sfVector2f _pos, Direction _direction)
//{
//	sfVector2i posMap = vector2i((int)_pos.x / TAILLE_BLOCK,(int) _pos.y / TAILLE_BLOCK);
//	switch (_direction)
//	{
//	case UP:
//		if (mapTop[posMap.y][posMap.x].isSolid)
//			return sfTrue;
//		break;
//	case DOWN:
//		if (mapTop[posMap.y][posMap.x].isSolid)
//			return sfTrue;
//		break;
//	case LEFT:
//		if (mapTop[posMap.y][posMap.x].isSolid)
//			return sfTrue;
//		break;
//	case RIGHT:
//		if (mapTop[posMap.y][posMap.x].isSolid)
//			return sfTrue;
//		break;
//	}
//	return sfFalse;
//}

sfBool collision(sfFloatRect _sprite, Direction _direction, sfVector2f _vitesse)
{
	// Gestions des collisions avec les murs


	sfVector2i fpos;
	sfVector2i fpos2;

	switch (_direction)
	{
		// Gestions des déplacements du personnage en fonction de la direction

	case UP:
		// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
		fpos.y = (_sprite.top - 2 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos.x = (_sprite.left + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.y = (_sprite.top - 2 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.x = (_sprite.width + _sprite.left + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;

		if (mapTop[fpos.y][fpos.x].isSolid || mapTop[fpos2.y][fpos2.x].isSolid)
		{
			return sfTrue;
		}
		else return sfFalse;

		break;
	case DOWN:
		// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
		fpos.y = (_sprite.top + _sprite.height + 2 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos.x = (_sprite.left + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.y = (_sprite.top + _sprite.height + 2 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.x = (_sprite.left + _sprite.width + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;

		if (mapTop[fpos.y][fpos.x].isSolid || mapTop[fpos2.y][fpos2.x].isSolid)
		{
			return sfTrue;
		}
		else return sfFalse;
		break;
	case RIGHT:
		// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer

		fpos.y = (_sprite.top + 10 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos.x = (_sprite.left + _sprite.width + 2 + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.y = (_sprite.top + _sprite.height + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.x = (_sprite.left + _sprite.width + 2 + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;

		if (mapTop[fpos.y][fpos.x].isSolid || mapTop[fpos2.y][fpos2.x].isSolid)
		{
			return sfTrue;
		}
		else return sfFalse;

		break;
	case LEFT:
		// Calcul des coordonnées de la case dans laquelle le personnage va se déplacer
		fpos.y = (_sprite.top + _sprite.height + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos.x = (_sprite.left - 2 + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.y = (_sprite.top + 10 + _vitesse.y * getDeltaTime()) / TAILLE_BLOCK;
		fpos2.x = (_sprite.left - 2 + _vitesse.x * getDeltaTime()) / TAILLE_BLOCK;

		if (mapTop[fpos.y][fpos.x].isSolid || mapTop[fpos2.y][fpos2.x].isSolid)
		{
			return sfTrue;
		}
		else return sfFalse;
		break;
	}

}


int countS()
{
	int countSs = 0;
	for (int j = 0; j < TAILLE_MAPY; j++)
	{
		for (int i = 0; i < TAILLE_MAPX; i++)
		{
			if (mapTop[j][i].isSolid)
				countSs++;
		}
	}
	return countSs;
}

void explosionBombe(sfVector2f _pos,int _numCase)
{
	sfVector2i posExplosion = vector2i(_pos.x / TAILLE_BLOCK, _pos.y / TAILLE_BLOCK);

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;

	addExplosion(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));

	for (int i = 1; i < _numCase+1; i++)
	{
		if (mapTop[posExplosion.y - i][posExplosion.x].id == BLOCK_WALL)
			up = 1;
		if (mapTop[posExplosion.y + i][posExplosion.x].id == BLOCK_WALL)
			down = 1;
		if (mapTop[posExplosion.y][posExplosion.x - i].id == BLOCK_WALL)
			left = 1;
		if (mapTop[posExplosion.y][posExplosion.x + i].id == BLOCK_WALL)
			right = 1;

		if(mapTop[posExplosion.y - i][posExplosion.x].id == BLOCK_NOTHING_TOP  && up == 0)
			addExplosion(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, (posExplosion.y - i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
		if (mapTop[posExplosion.y + i][posExplosion.x].id == BLOCK_NOTHING_TOP && down == 0)
			addExplosion(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, (posExplosion.y + i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
		if (mapTop[posExplosion.y][posExplosion.x - i].id == BLOCK_NOTHING_TOP && left == 0)
			addExplosion(vector2f((posExplosion.x - i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
		if (mapTop[posExplosion.y][posExplosion.x + i].id == BLOCK_NOTHING_TOP && right == 0)
			addExplosion(vector2f((posExplosion.x + i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));

		if (mapTop[posExplosion.y - i][posExplosion.x].id == BLOCK_BRICK && up !=1)
		{
			mapTop[posExplosion.y - i][posExplosion.x].id = BLOCK_NOTHING_TOP;
			mapTop[posExplosion.y - i][posExplosion.x].isSolid = sfFalse;
			addExplosion(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK/2.f, (posExplosion.y - i) * TAILLE_BLOCK + TAILLE_BLOCK/2.f));
			int rands = rand() % 9;
			if (rands <= 4)
				addBonus(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 4.f, (posExplosion.y - i) * TAILLE_BLOCK + TAILLE_BLOCK / 4.f), rands);
			up = 1;
		}
		if (mapTop[posExplosion.y + i][posExplosion.x].id == BLOCK_BRICK && down !=1)
		{
			mapTop[posExplosion.y + i][posExplosion.x].id = BLOCK_NOTHING_TOP;
			mapTop[posExplosion.y + i][posExplosion.x].isSolid = sfFalse;
			addExplosion(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, (posExplosion.y + i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
			int rands = rand() % 9;
			if (rands <= 4)
				addBonus(vector2f(posExplosion.x * TAILLE_BLOCK + TAILLE_BLOCK / 4.f, (posExplosion.y + i) * TAILLE_BLOCK + TAILLE_BLOCK / 4.f), rands);
			down = 1;
		}
		if (mapTop[posExplosion.y][posExplosion.x - i].id == BLOCK_BRICK && left != 1)
		{
			mapTop[posExplosion.y][posExplosion.x - i].id = BLOCK_NOTHING_TOP;
			mapTop[posExplosion.y][posExplosion.x - i].isSolid = sfFalse;
			addExplosion(vector2f( (posExplosion.x - i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
			int rands = rand() % 9;
			if (rands <= 4)
				addBonus(vector2f((posExplosion.x - i) * TAILLE_BLOCK + TAILLE_BLOCK / 4.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 4.f), rands);
			left = 1;
		}
		if (mapTop[posExplosion.y][posExplosion.x + i].id == BLOCK_BRICK && right !=1)
		{
			mapTop[posExplosion.y][posExplosion.x + i].id = BLOCK_NOTHING_TOP;
			mapTop[posExplosion.y][posExplosion.x + i].isSolid = sfFalse;
			addExplosion(vector2f((posExplosion.x + i) * TAILLE_BLOCK + TAILLE_BLOCK / 2.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 2.f));
			int rands = rand() % 9;
			if (rands <= 4)
				addBonus(vector2f((posExplosion.x + i) * TAILLE_BLOCK + TAILLE_BLOCK / 4.f, posExplosion.y * TAILLE_BLOCK + TAILLE_BLOCK / 4.f), rands);
			right = 1;
		}
	}
}