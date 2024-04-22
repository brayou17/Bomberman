#pragma once
#include "tools.h"
#include "SFML/Audio.h"
#include "ressourcesManager.h"

typedef struct Sound Sound;

void Sound_Onload(State _state);
Sound* RemoveSound(Sound* _sound);
void setVolume(Sound* _sound, float _volume);
float getVolume(Sound* _sound);
void setSoundVolume(float _volume);
void setMusicVolume(float _volume);
void playSound(char* _name);
void stopSound(char* _name);
void RemoveWasteSound();
float getSFXVolume();
float getMusicVolume();