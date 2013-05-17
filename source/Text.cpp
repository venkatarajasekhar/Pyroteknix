// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Text
//      Text that can be rendered to the screen


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include "Text.h"


// |----------------------------------------------------------------------------|
// |							   Constructor									|
// |----------------------------------------------------------------------------|
Text::Text() :
	m_string(""),
	m_font(0),
	m_fontTexture(0),
	GameObject()
{
	Debug("Text: object instantiated.");
}


// |----------------------------------------------------------------------------|
// |							   Initialize									|
// |----------------------------------------------------------------------------|
bool Text::Initialize() {

	GameObject::Initialize();
	
	// Load default font and fontTexture, if one wasn't already specified
	if (!m_font) m_font = AssetManager::GetSingleton().GetFont("defaultFont");
	if (!m_fontTexture) m_fontTexture = AssetManager::GetSingleton().GetRedAlphaTexture("defaultFont");

	Debug ("Text: object initialized.");
	return true;
}


// |----------------------------------------------------------------------------|
// |						        Render()									|
// |----------------------------------------------------------------------------|
bool Text::Render() {
	Debug ("Text: Render() called.");
	
	if (!m_active) return true;
	
	AssetManager::GetSingleton().LoadTexture(m_fontTexture);
	
	m_font->printfL(m_position.x, m_position.y, 127, 127, 127, 127, m_string.c_str());
	
	return true;
}