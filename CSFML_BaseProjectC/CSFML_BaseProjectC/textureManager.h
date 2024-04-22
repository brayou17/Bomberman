#pragma once
#include "ressourcesManager.h"

typedef struct Texture Texture;

Texture* textureBegin;

void Texture_Onload(State);
sfTexture* GetTexture(char* _name);
int GetNbFrame(char* _name);
float GetFrameTime(char* _name);
sfIntRect GetRect(char* _name);
void AddTexture(Texture* _texture);
Texture* RemoveTexture(Texture* _texture);
void RemoveAllTexture();
void RemoveWasteTexture();
void Animator(const char* _name, sfSprite* _sprite, int* _frameX);
void AnimatorUpdate();