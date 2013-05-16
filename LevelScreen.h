// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// LevelScreen
//      Screen containing a game level
#ifndef __LEVELSCREEN_H__
#define __LEVELSCREEN_H__


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <string>
#include "Util.h"
#include "Screen.h"
#include "FireworkEffect.h"
#include "ParticleSystem.h"
#include "Firework.h"
#include "Image2D.h"
#include "Text.h"


// |----------------------------------------------------------------------------|
// |						  Class Definition: LevelScreen						|
// |----------------------------------------------------------------------------|
class LevelScreen : public Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructors and Destructors
	LevelScreen();
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
	Image2D* m_crosshair;
	float m_aimSpeed;
	GameObject* m_cannon;
	Firework* m_firework;
	
	// Audience and happiness
	GameObject** m_people;
	int* m_happiness;			// Happiness ranges: 0 - leaving; 1 - angry; 2 - meh; 3 - happy
	int m_numPeople;
	float m_peopleIncrementX;
	float m_fireworkRange;
	float m_happinessCooldown;
	float m_happinessTime;
	
	// Cost and budget
	int m_budget;
	int m_costCross;
	float m_cooldown;
	float m_accumulatedTime;
	Text* m_budgetDisplay;
	
	// Score
	int m_score;
	Text* m_scoreDisplay;
	int m_fireworkScore;
	
	// Time
	float m_timeRemaining;
	Text* m_timeDisplay;
	
	// Win/Loss Dialogue
	bool m_gameover;
	bool m_won;
	Text* m_winDialogue;
	Text* m_lossDialogue;
	
	// Audio
	SoundSample m_cannonSound;
	SoundSample m_fireworkSound;
	
	// Screen Flash
	Image2D* m_flash;
    
};

#endif