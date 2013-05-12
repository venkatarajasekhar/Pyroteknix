// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Screen containing a game level
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Util.h"
#include "Screen.h"


// |----------------------------------------------------------------------------|
// |						  Class Definition: LevelScreen						|
// |----------------------------------------------------------------------------|
class LevelScreen : public Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	LevelScreen();
	LevelScreen(const LevelScreen&);
	virtual ~LevelScreen();

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
	// The logic function, which will be called by the main game loop.
	bool virtual Logic();
    
	// The draw function, which will be called by the main game loop.
	bool virtual Render();
    
	// Called when the screen is loaded.
	bool virtual OnLoad();
    
	// Called when switching to a different screen
	bool virtual OnExit();
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|
    
};