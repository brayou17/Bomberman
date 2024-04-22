#include "fontManager.h"

void AddFont(Font* _font)
{
	_font->pNext = fontBegin;
	fontBegin = _font;
}

void Font_OnLoad(State _state)
{
	ressources* tempRessources = ResBegin;
	while (tempRessources != NULL)
	{
		if (tempRessources->type == FONT)
		{
			Font* tempFont = (Font*)calloc(1, sizeof(Font));
			strcpy(tempFont->name, tempRessources->name);
			tempFont->type = tempRessources->type;
			tempFont->font = sfFont_createFromFile(tempRessources->path);
			tempFont->state = tempRessources->state;
			AddFont(tempFont);
		}
		tempRessources = tempRessources->pNext;
	}
}

Font* RemoveFont(Font* _font)
{
	if (_font == fontBegin)
	{
		Font* tempFont = _font->pNext;
		fontBegin = tempFont;
		sfFont_destroy(_font->font);
		free(_font);
		return tempFont;
	}
	else
	{
		Font* tempFont = fontBegin;
		while (tempFont->pNext != _font)
		{
			tempFont = tempFont->pNext;
		}
		tempFont->pNext = _font->pNext;
		sfFont_destroy(_font->font);
		free(_font);
		return tempFont->pNext;
	}
}

void RemoveWasteFont()
{
	Font* tempFont = fontBegin;
	while (tempFont != NULL)
	{
		if (tempFont->state != ALL)
		{
			tempFont = RemoveFont(tempFont);
		}
		else
		{
			tempFont = tempFont->pNext;
		}
	}
}

Font* GetFont(char* _name)
{
	Font* tempFont = fontBegin;
	while (tempFont !=NULL)
	{
		if (strcmp(_name, tempFont->name) == 0)
		{
			return tempFont;
		}
		tempFont = tempFont->pNext;
	}
}

sfText* prepareText(char* _fontName, char* _text, unsigned int _size)
{
	sfText* tmpText = sfText_create();

	sfText_setFont(tmpText, GetFont(_fontName)->font);
	sfText_setString(tmpText, _text);
	sfText_setCharacterSize(tmpText, _size);

	return tmpText;
}
