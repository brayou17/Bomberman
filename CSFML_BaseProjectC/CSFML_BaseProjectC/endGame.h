#pragma once
#include "tools.h"
#include "windowManager.h"

/// <summary>
/// This function init all elements of the end of game
/// </summary>
void initEndGame();
/// <summary>
/// This function update all elements of the end of game
/// </summary>
/// <param name="_window">The struct Window</param>
void updateEndGame(Window* _window);
/// <summary>
/// This function display the first part of elements of the end of game
/// </summary>
/// <param name="_window">The struct Window</param>
void displayEndGame1(Window* _window);
/// <summary>
/// This function display the second part of elements of the end of game
/// </summary>
/// <param name="_window"></param>
void displayEndGame2(Window* _window);
/// <summary>
/// This function creates a default score in a file
/// </summary>
void defaultScore();
/// <summary>
/// This function reads a score in file
/// </summary>
void readScore();