// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// GameManager
//      Manages game screens and game logic within those screens.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "GameManager.h"


// |----------------------------------------------------------------------------|
// |                           Default Constructor                              |
// |----------------------------------------------------------------------------|
GameManager::GameManager() :
    m_screens(0),
    m_currentScreen(0)
{
}


// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
GameManager::GameManager(const GameManager& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
GameManager::~GameManager()
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool GameManager::Initialize()
{
    bool result,RetValue;
    
    // Initialize screens
    m_screens = new Screen* [NUM_SCREENS];
	if(!m_screens)
		exit;
    for (int i = 0 ; i < NUM_SCREENS; ++i) {
        m_screens[i] = NULL;
    }
	Debug ("GameManager::Screen Init.");
    m_screens[SCREEN_TITLE] = new TitleScreen();
    m_screens[SCREEN_TITLE]->Initialize();
    m_screens[SCREEN_LEVEL] = new LevelScreen();
    m_screens[SCREEN_LEVEL]->Initialize();
    m_currentScreen = m_screens[SCREEN_TITLE];
	if(!m_currentScreen)
		exit;
    result = m_currentScreen->OnLoad();
    RetValue = true;
    return RetValue;
}


// |----------------------------------------------------------------------------|
// |                              Shutdown                                      |
// |----------------------------------------------------------------------------|
void GameManager::Shutdown()
{
	Debug ("GameManager::Shutdown called.");

    // Screen Cleanup
    if (m_screens) {
        for (int i = 0 ; i < NUM_SCREENS; ++i) {
			if (m_screens[i])
			{
				m_screens[i]->Shutdown();
				delete m_screens[i];
				m_screens[i]= NULL;
			}
        }
        delete[] m_screens;
        m_screens = NULL;
    }
    m_currentScreen = NULL;

	Debug ("GameManager: Object shut down.");
	
    return;
}


// |----------------------------------------------------------------------------|
// |                               Logic                                        |
// |----------------------------------------------------------------------------|
bool GameManager::Logic()
{
    bool result, Retval;
	if (!m_currentScreen->IsDone())
		exit;
    // Check if we need to change screens
    if (m_currentScreen->IsDone()) {

        // Perform onExit functions for the old screen
        result = m_currentScreen->OnExit();
        if (!result){
		Retval = false;
            return Retval;
	}

        // Check if the screen is telling the game to quit.
        if (m_currentScreen->GetNextScreen() == SCREEN_QUIT) {
            // If so, quit.
		Retval = false;
            return Retval;
        }

        // If the screen is NOT telling the game to quit, load the next screen
        else {
            // Set the new screen as current
            m_currentScreen = m_screens[m_currentScreen->GetNextScreen()];
            // Perform onLoad functions for the new screen
            result = m_currentScreen->OnLoad();
            if(!result){
               Retval = false;
               return Retval;
	    }
        }

    }
    
    // Perform game logic for current screen
    result = m_currentScreen->Logic();
    if (!result){
      Retval = false;
      return Retval;
    }
	Retval = true;
    return Retval ;
}


// |----------------------------------------------------------------------------|
// |                               Render                                       |
// |----------------------------------------------------------------------------|
bool GameManager::Render()
{
    bool result,Retval;
    if(!m_currentScreen)
	    exit;
    // Send game objects in screen to be rendered
    result = m_currentScreen->Render();
    if (!result){
	  Retval = false;
        return Retval;
        }
Retval = true;
    return Retval;
}
