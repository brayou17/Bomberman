#pragma once
#include "tools.h"
#include "ressourcesManager.h"

typedef struct Font Font;
struct Font
{
	Font* pNext;
	char name[30];
	ressourceType type;
	State state;
	sfFont* font;

};

Font* fontBegin;

void Font_OnLoad(State _state);
Font *RemoveFont(Font* _font);
void RemoveWasteFont();
Font *GetFont(char* _name);
sfText *prepareText(char* _fontName, char* _text, unsigned int _size);