// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Screen
//      Abstract class for screens. Contains game objects, executes their game
//      logic.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Screen.h"


// |----------------------------------------------------------------------------|
// |                              Constructor                                   |
// |----------------------------------------------------------------------------|
Screen::Screen() : 
    m_done(0), 
    m_nextScreen(SCREEN_QUIT),
    m_camera(0),
	m_font(0),
	m_fontTexture(0),
	m_frame(0),
	m_fps(0.0f)
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Screen::Initialize() {

	m_font = AssetManager::GetSingleton().GetFont("defaultFont");
	m_fontTexture = AssetManager::GetSingleton().GetRedAlphaTexture("defaultFont");
		
	Debug ("Screen: object initialized.");
    return true;
}


// |----------------------------------------------------------------------------|
// |                                Shutdown                                    |
// |----------------------------------------------------------------------------|
bool Screen::Shutdown() 
{
	Debug ("Screen::Shutdown called.");
    bool result = true;
    
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         delete (*it);
    m_backgroundObjects.clear();
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         delete (*it);
    m_gameObjects.clear();
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         delete (*it);
    m_overlayObjects.clear();

	Debug ("Screen: object shutdown.");
    return result;
}


// |----------------------------------------------------------------------------|
// |                                OnLoad                                      |
// |----------------------------------------------------------------------------|
bool Screen::OnLoad() {

	// Start the timer
	m_timer.PrimeTimer();
		
	m_done = false;
	
    return true;
}


// |----------------------------------------------------------------------------|
// |                                OnExit                                      |
// |----------------------------------------------------------------------------|
bool Screen::OnExit() {

		
    return true;
}


// |----------------------------------------------------------------------------|
// |                                 Logic                                      |
// |----------------------------------------------------------------------------|
bool Screen::Logic() 
{ 
    bool result = true;

    if(m_camera)
		m_camera->Logic();

    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Logic();
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Logic();
	
	// Check for exit state
	if((pad[0].buttons & PAD_START)&&(pad[0].buttons & PAD_SELECT))
	{
		m_done = true;
		m_nextScreen = SCREEN_QUIT;
	}
	
    return result;
}


// |----------------------------------------------------------------------------|
// |                                 Render                                     |
// |----------------------------------------------------------------------------|
bool Screen::Render()
{ 
    bool result = true;

    // Draw Background objects
    for (std::list<GameObject*>::iterator it=m_backgroundObjects.begin(); it != m_backgroundObjects.end(); ++it)
         result = result && (*it)->Render();

    // Draw main objects
    for (std::list<GameObject*>::iterator it=m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
         result = result && (*it)->Render();

    // Draw Overlay
    for (std::list<GameObject*>::iterator it=m_overlayObjects.begin(); it != m_overlayObjects.end(); ++it)
         result = result && (*it)->Render();
		
	if(DEBUG)
	{
		// Draw debug information
		AssetManager::GetSingleton().LoadTexture(m_fontTexture);
			m_font->printfL(  	-300, -240, 127, 127, 127, 127, 
							"Camera Position (x, y, z) = (%3.1f, %3.1f, %3.1f)", 
							CPipeline::GetSingleton().GetCameraX(), CPipeline::GetSingleton().GetCameraY(), CPipeline::GetSingleton().GetCameraZ());
			m_font->printfL(  	-300, -210, 127, 127, 127, 127, 
							"Camera Rotation in Degrees (XRot, YRot) = (%3.1f, %3.1f)", 
							RadToDeg(CPipeline::GetSingleton().GetCameraXRot()), RadToDeg(CPipeline::GetSingleton().GetCameraYRot()));
			m_font->printfC(  200, -240, 127, 127, 127, 127, "Frame: %d\nFPS: %.1f" , m_frame++, m_fps);
		
		//calculate the current frame rate in frames per second	
		m_fps = m_timer.GetFPS();
	}
		
    return result;
}