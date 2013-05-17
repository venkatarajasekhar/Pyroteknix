// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Screen
//      Abstract class for screens. Contains game objects, executes their game
//      logic.
#ifndef __SCREEN_H__
#define __SCREEN_H__

// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <list>
#include "Util.h"
#include "GameObject.h"
#include "AssetManager.h"

// |----------------------------------------------------------------------------|
// |						  Class Definition: Screen							|
// |----------------------------------------------------------------------------|
class Screen {

public:
    
    //|-------------------------------Public Functions--------------------------|

	// Constructor
    Screen();

    // Initialization and shutdown
	bool virtual Initialize();
	bool virtual Shutdown();
    
	// The logic function, which will be called by the main game loop.
    bool virtual Logic();
    
	// The render function, which will be called by the main game loop.
	bool virtual Render();
    
	// Called when the screen is loaded.
	bool virtual OnLoad();
    
	// Called when switching to a different screen
	bool virtual OnExit();
    
	// Getter Functions
	SCREEN virtual GetNextScreen()  { return m_nextScreen; }
	bool virtual IsDone() { return m_done; }
    
	// Setetter Functions
	void virtual SetNextScreen(SCREEN new_next) { m_nextScreen = new_next; }
	void virtual SetDone(bool new_done) { m_done = new_done; }
	
protected:
    
    //|------------------------------Protected Functions------------------------|
	
protected:
    
    //|----------------------------Protected Data Members-----------------------|

	bool m_done;
	SCREEN m_nextScreen;

    // GameObject Array
    std::list<GameObject*> m_backgroundObjects;
    std::list<GameObject*> m_gameObjects;
    std::list<GameObject*> m_overlayObjects;

    // Special game objects
    GameObject* m_camera;
	CFont* m_font;
	CTexture* m_fontTexture;
	
	// Debugging info
	CTimer m_timer;
	int m_frame;
	float m_fps;

};

#endif