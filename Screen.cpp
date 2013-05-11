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
    m_camera(0)
{
}


// |----------------------------------------------------------------------------|
// |                              Initialize                                    |
// |----------------------------------------------------------------------------|
bool Screen::Initialize() {

    return true;
}


// |----------------------------------------------------------------------------|
// |                                Shutdown                                    |
// |----------------------------------------------------------------------------|
bool Screen::Shutdown() 
{
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

    return result;
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

    return result;
}