#pragma once

#include "SFML/Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "dirent.h"

#define TEXTURE_PATH "..\\Ressources\\Textures\\"
#define FONT_PATH "..\\Ressources\\Fonts\\"
#define MAP_PATH "..\\Ressources\\Maps\\"
#define TILESET_PATH "..\\Ressources\\Tilesets\\"

typedef struct vector4f vector4f;
struct vector4f
{
	float r;
	float g;
	float b;
	float a;
};

//-----------------------------------------------------------
//	Fonction d'initialisation des tools
//	� mettre obligatoirement dans votre init 
//	pour utiliser les fonctions de cette biblioth�que
//-----------------------------------------------------------
void initTools();

//-----------------------------------------------------------
//	Fonction getDefaultFont ( )
//  Renvoi la police par d�faut
//-----------------------------------------------------------
sfFont* getDefaultFont();

//-----------------------------------------------------------
//	Fonction vector2f ( float _x, float _y )
//  Renvoi un sfVector2f en partant de 2 float
//	_x float
//	_y float
//-----------------------------------------------------------
sfVector2f vector2f(float _x, float _y);

//-----------------------------------------------------------
//	Fonction vector2i ( int _x, int _y )
//  Renvoi un sfVector2i en partant de 2 int
//	_x int
//	_y int
//-----------------------------------------------------------
sfVector2i vector2i(int _x, int _y);

//-----------------------------------------------------------
//	Fonction vector3f ( float _x, float _y, float _z )
//  Renvoi un sfVector3f en partant de 3 float
//	_x float
//	_y float
//	_z float
//-----------------------------------------------------------
sfVector3f vector3f(float _x, float _y, float _z);

//------------------------------------------------------------------------------
//	Fonction FlRect ( float _left, float _top, float _width, float _height )
//  Renvoi un sfFloatRect en partant de 4 float
//	_left float
//	_top float
//	_width float
//	_height float
//------------------------------------------------------------------------------
sfFloatRect FlRect(float _left, float _top, float _width, float _height);

//-----------------------------------------------------------
//	Fonction vector2i ( int _left, int _top, int _width, int _height )
//  Renvoi un sfIntRect en partant de 4 int
//	_left int
//	_top int
// 	_width int
//	_height int
//-----------------------------------------------------------
sfIntRect IntRect(int _left, int _top, int _width, int _height);

//-----------------------------------------------------------
//	Fonction vector2i ( sfUint8 r, sfUint8 g, sfUint8 b, sfUint8 a )
//  Renvoi un sfColor en partant de 4 int
//	r rouge	: valeur entre 0 et 255
//	g vert	: valeur entre 0 et 255
// 	b bleu	: valeur entre 0 et 255
//	a alpha	: valeur entre 0 et 255
//-----------------------------------------------------------
sfColor color(sfUint8 r, sfUint8 g, sfUint8 b, sfUint8 a);


//-----------------------------------------------------------
//	Fonction lerp ( float )
//	v0 point de d�part
//	v1 destination
//	t valeur entre 0.0f et 1.0f ( seul variable qui varie )
//-----------------------------------------------------------
float lerp(float v0, float v1, float t);

//-----------------------------------------------------------
//	Fonction lerp ( vector2f )
//	v0 point de d�part
//	v1 destination
//	t valeur entre 0.0f et 1.0f ( seul variable qui varie )
//-----------------------------------------------------------
sfVector2f vec2f_lerp(sfVector2f v0, sfVector2f v1, float t);

//-----------------------------------------------------------
//	Fonction lerp ( vector3f )
//	v0 point de d�part
//	v1 destination
//	t valeur entre 0.0f et 1.0f ( seul variable qui varie )
//-----------------------------------------------------------
sfVector3f vec3f_lerp(sfVector3f v0, sfVector3f v1, float t);

//-----------------------------------------------------------
//	Fonction lerp ( vector4f )
//	v0 point de d�part
//	v1 destination
//	t valeur entre 0.0f et 1.0f ( seul variable qui varie )
//-----------------------------------------------------------
vector4f vec4f_lerp(vector4f v0, vector4f v1, float t);

//-----------------------------------------------------------
//	Fonction lerp ( sfColor )
//	v0 couleur de d�part
//	v1 couleur de fin
//	t valeur entre 0.0f et 1.0f ( seul variable qui varie )
//-----------------------------------------------------------
sfColor color_lerp(sfColor v0, sfColor v1, float t);

//-----------------------------------------------------------
//	Fonction restartClock()
//	fonction � mettre d�s le d�but de votre update
//	pour g�rer le temps
//-----------------------------------------------------------
void restartClock();

//-----------------------------------------------------------
//	Fonction GetDeltaTime()
//	Renvoi un float du temps pass� entre 2 ticks
//-----------------------------------------------------------
float getDeltaTime();

//-----------------------------------------------------------
//	Fonction CreateSprite(char* _path)
//	Cr�e un sprite � partir d'une texture
//	_path le chemin vers la texture 
// 
//	renvoi un sfSprite*
//-----------------------------------------------------------
sfSprite* CreateSprite(char* _path);

//-----------------------------------------------------------
//	Fonction CreateText(char* _path)
//	Cr�e un texte � partir d'une font
//	_path le chemin vers la font 
// 
//	renoi un sfText*
//-----------------------------------------------------------
sfText* CreateText(char* _path);

//--------------------------------------------------------------------------------------------
//	Circle_Collision(sfVector2f _pos1, sfVector2f _pos2, float _rayon1, float _rayon2)
//	V�rifie si 2 cercles sont en collision
//	_pos1	position du 1er cercle
//	_pos2	position du 2eme cercle
//	_rayon1	rayon du 1er cercle
//	_rayon2	rayon du 2eme cercle
// 
// renvoi un sfBool, sfTrue si il y a collision, sfFalse si il n'y a pas collision
//--------------------------------------------------------------------------------------------
sfBool Circle_Collision(sfVector2f _pos1, sfVector2f _pos2, float _rayon1, float _rayon2);

//--------------------------------------------------------------------------------------------
//	Rectangle_Collision(sfFloatRect _box1, sfFloatRect _box2)
//	V�rifie si 2 rectangles sont en collision
//	_box1	position, largeur et hauteur du 1er rectangle
//	_box2	position, largeur et hauteur du 2eme rectangle
// 
// renvoi un sfBool, sfTrue si il y a collision, sfFalse si il n'y a pas collision
//--------------------------------------------------------------------------------------------
sfBool Rectangle_Collision(sfFloatRect _box1, sfFloatRect _box2);

//-----------------------------------------------------------
//	Fonction iRand ( int _min, int _max )
//	_min valeur minimum de random
//	_max valeur maximum de random
// 
//	si _max < _min, _min sera toujours renvoy�
// 
//	renvoi un int compris entre _min et _max
//-----------------------------------------------------------
int iRand(int _min, int _max);

//-----------------------------------------------------------
//	Fonction rand_int ( int _min, int _max )
//	_min valeur minimum de random
//	_max valeur maximum de random
// 
//	renvoi un int compris entre _min et _max
//-----------------------------------------------------------
int rand_int(int _min, int _max);

//-----------------------------------------------------------
//	Fonction rand_float ( float _min, float _max )
//	_min valeur minimum de random
//	_max valeur maximum de random
// 
//	renvoi un double compris entre _min et _max
//-----------------------------------------------------------
double rand_float(float _min, float _max);

//-----------------------------------------------------------
//	Fonction FrameRate 
//-----------------------------------------------------------
float FrameRate();

//-----------------------------------------------------------
//	Fonction displayFrameRate
//-----------------------------------------------------------
void displayFrameRate(sfRenderWindow* _window, sfText* _text);

//-----------------------------------------------------------
//	Fonction screenshot
//-----------------------------------------------------------
void screenshot(sfRenderWindow* _window);


sfVector2f getFloatMousePos(sfRenderWindow* _window);
