// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Text
//      Text that can be rendered to the screen
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <string>
#include <math.h>
#include "Util.h"
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |                           Class Definition: Text                           |
// |----------------------------------------------------------------------------|
class Text : public GameObject
{

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	Text();

    // Initialization
	bool virtual Initialize();
	
    // Sends any models associated with the object to the renderer
    bool virtual Render();
	
	// Setters
	void virtual SetFont(CFont* value) {m_font = value;}
	void virtual SetFont(std::string name) {m_font = AssetManager::GetSingleton().GetFont(name);}
	void virtual SetTexture(CTexture* value) {m_fontTexture = value;}
	void virtual SetTexture(std::string name) {m_fontTexture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	
protected:
    
    //|---------------------------Protected Data Members-----------------------|
	
	// Text data
	std::string m_string;
	CFont* m_font;
	CTexture* m_fontTexture;

};