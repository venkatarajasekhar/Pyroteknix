// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameManager
//      Manages game screens and game logic within those screens.
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Screen.h"
#include "TitleScreen.h"
#include "LevelScreen.h"


// |----------------------------------------------------------------------------|
// |                            Class: GameManager                              |
// |----------------------------------------------------------------------------|
class GameManager
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	GameManager();
	GameManager(const GameManager&);
	~GameManager();
    
    // Initialization and shutdown
    bool Initialize();
    void Shutdown();

    // Processes game logic each frame
    bool Logic();

    // Send game objects to be rendered
    bool Render();
    
private:

    //|-------------------------------Private Functions-------------------------|
    
    // Sets the current screen to the supplied screen index.
    int ChangeScreen(SCREEN nextScreen);

private:

    //|-----------------------------Private Data Members------------------------|
    
    // Screens
    Screen* m_currentScreen;
    Screen** m_screens;

};