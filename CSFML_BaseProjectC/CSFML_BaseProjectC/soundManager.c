#include "soundManager.h"


struct Sound
{
	Sound* pNext;
	char name[30];
	ressourceType type;
	State state;
	sfSoundBuffer* soundBuffer;
	float volume;
	sfBool loop;
	union MyUnion
	{
		sfMusic* music;
		sfSound* sound;
	};

};

float SFXVolume;
float musicVolume;

Sound* soundBegin;

void AddSound(Sound* _sound)
{
	_sound->pNext = soundBegin;
	soundBegin = _sound;
}

void Sound_Onload(State _state)
{
	ressources* tempRessources = ResBegin;
	while (tempRessources != NULL)
	{
		if (tempRessources->type == SOUNDFX)
		{
			if (tempRessources->state == _state)
			{
				Sound* tempSound = (Sound*)calloc(1, sizeof(Sound));
				strcpy(tempSound->name, tempRessources->name);
				tempSound->type = tempRessources->type;
				tempSound->state = tempRessources->state;
				tempSound->sound = sfSound_create();
				if (!(tempSound->soundBuffer = sfSoundBuffer_createFromFile(tempRessources->path)))
					return EXIT_FAILURE;
				tempSound->volume = 1.0f;
				tempSound->loop = sfFalse;
				sfSound_setBuffer(tempSound->sound, tempSound->soundBuffer);
				float vol = SFXVolume * tempSound->volume;
				sfSound_setVolume(tempSound->sound, vol);
				sfMusic_setLoop(tempSound->sound, tempSound->loop);
				AddSound(tempSound);
			}
		}
		else if (tempRessources->type == MUSIC)
		{
			if (tempRessources->state == _state)
			{
				Sound* tempSound = (Sound*)calloc(1, sizeof(Sound));
				strcpy(tempSound->name, tempRessources->name);
				tempSound->type = tempRessources->type;
				tempSound->state = tempRessources->state;
				if (!(tempSound->music = sfMusic_createFromFile(tempRessources->path)))
					return EXIT_FAILURE;
				tempSound->volume = 1.0f;
				tempSound->loop = sfTrue;
				float vol = musicVolume * tempSound->volume;
				sfMusic_setVolume(tempSound->music, vol);
				sfMusic_setLoop(tempSound->music, tempSound->loop);
				AddSound(tempSound);
			}
		}
		tempRessources = tempRessources->pNext;
	}
}



Sound* RemoveSound(Sound* _sound)
{
	if (_sound == soundBegin)
	{
		Sound* tempSound = _sound->pNext;
		soundBegin = tempSound;
		if (_sound->type == SOUNDFX)
		{
			sfSound_destroy(_sound->sound);
			sfSoundBuffer_destroy(_sound->soundBuffer);
		}
		else if (_sound->type == MUSIC)
			sfMusic_destroy(_sound->music);
		free(_sound);
		return tempSound;
	}
	else
	{
		Sound* tempSound = soundBegin;
		while (tempSound->pNext != _sound)
		{
			tempSound = tempSound->pNext;
		}
		tempSound->pNext = _sound->pNext;
		if (_sound->type == SOUNDFX)
		{
			sfSound_destroy(_sound->sound);
			sfSoundBuffer_destroy(_sound->soundBuffer);
		}
		else if (_sound->type == MUSIC)
			sfMusic_destroy(_sound->music);
		free(_sound);
		return tempSound->pNext;
	}
}

void setVolume(Sound* _sound, float _volume)
{
	_sound->volume = _volume;
}

float getVolume(Sound* _sound)
{
	return _sound->volume;
}

void setSoundVolume(float _volume)
{
	Sound* tempSound = soundBegin;
	SFXVolume = _volume;
	while (tempSound != NULL)
	{
		if (tempSound->type == SOUNDFX)
		{
			float vol = SFXVolume * tempSound->volume;
			sfSound_setVolume(tempSound->sound, vol);
		}
		tempSound = tempSound->pNext;
	}
}

void setMusicVolume(float _volume)
{
	Sound* tempSound = soundBegin;
	musicVolume = _volume;
	while (tempSound != NULL)
	{
		if (tempSound->type == MUSIC)
		{
			float vol = musicVolume * tempSound->volume;
			sfMusic_setVolume(tempSound->music, vol);
		}
		tempSound = tempSound->pNext;
	}
}

void playSound(char* _name, sfBool loop)
{
	Sound* tempSound = soundBegin;
	while (tempSound != NULL)
	{
		if (strcmp(_name, tempSound->name) == 0)
		{
			if (tempSound->type == SOUNDFX)
			{
				sfSound_play(tempSound->sound);
			}
			else if (tempSound->type == MUSIC)
			{
				sfMusic_setLoop(tempSound->music, loop);
				sfMusic_play(tempSound->music);
			}
		}
		tempSound = tempSound->pNext;
	}
}

void stopSound(char* _name)
{
	Sound* tempSound = soundBegin;
	while (tempSound != NULL)
	{
		if (strcmp(_name, tempSound->name) == 0)
		{
			if (tempSound->type == SOUNDFX)
			{
				sfSound_stop(tempSound->sound);
			}
			else if (tempSound->type == MUSIC)
			{
				sfMusic_stop(tempSound->music);
			}
		}
		tempSound = tempSound->pNext;
	}
}

void setSoundLoop(char* _name, sfBool _loop)
{
	Sound* tempSound = soundBegin;
	while (tempSound != NULL)
	{
		if (strcmp(_name, tempSound->name) == 0)
		{
			tempSound->loop = _loop;
			if (tempSound->type == SOUNDFX)
			{
				sfSound_setLoop(tempSound->sound, tempSound->loop);
			}
			else if (tempSound->type == MUSIC)
			{
				sfMusic_setLoop(tempSound->music, tempSound->loop);
			}
		}
		tempSound = tempSound->pNext;
	}
}

void RemoveWasteSound()
{
	Sound* tempSound = soundBegin;
	while (tempSound != NULL)
	{
		if (tempSound->state != ALL)
		{
			tempSound = RemoveSound(tempSound);
		}
		else
		{
			tempSound = tempSound->pNext;
		}
	}
}


float getSFXVolume()
{
	return SFXVolume;
}

float getMusicVolume()
{
	return musicVolume;
}

